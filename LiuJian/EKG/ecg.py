import numpy as np
import dicom 
import sys
import struct
from matplotlib import pylab as plt
from scipy.signal import butter, lfilter

LAYOUT = {'3x4_1': [[0, 3, 6, 9],
                        [1, 4, 7, 10],
                        [2, 5, 8, 11],
                        [1]],
              '3x4': [[0, 3, 6, 9],
                      [1, 4, 7, 10],
                      [2, 5, 8, 11]],
              '6x2': [[0, 6],
                      [1, 7],
                      [2, 8],
                      [3, 9],
                      [4, 10],
                      [5, 11]],
              '12x1': [[0],
                       [1],
                       [2],
                       [3],
                       [4],
                       [5],
                       [6],
                       [7],
                       [8],
                       [9],
                       [10],
                       [11]],
              '1': [[0]],
              '2': [[1]],
              '3': [[2]],
              '4': [[3]],
              '5': [[4]],
              '6': [[5]],
              '7': [[6]],
              '8': [[7]],
              '9': [[8]],
              '10': [[9]],
              '11': [[10]],
              '12': [[11]]
                       }
					   
def butter_lowpass(highcut, sampfreq, order):
    """Supporting function.

    Prepare some data and actually call the scipy butter function.
    """

    nyquist_freq = 0.5 * sampfreq
    high = highcut / nyquist_freq
    num, denom = butter(order, high, btype='lowpass')
    return num, denom


def butter_lowpass_filter(data, highcut, sampfreq, order):
    """Apply the Butterworth lowpass filter to the DICOM waveform.

    @param data: the waveform data.
    @param highcut: the frequencies from which apply the cut.
    @param sampfreq: the sampling frequency.
    @param order: the filter order.
    """

    num, denom = butter_lowpass(highcut, sampfreq, order=order)
    return lfilter(num, denom, data)

class ECG(object):
    """The class representing the ECG object
    """
	
    def __init__(self,filename):
        """The ECG class constructor"""
        if not filename.endswith('DCM'):
            print("Please input a dcm file")
            sys.exit()
        self.dicom = dicom.read_file(filename)
        sequence_item = self.dicom.WaveformSequence[0]

        assert (sequence_item.WaveformSampleInterpretation == 'SS')
        assert (sequence_item.WaveformBitsAllocated == 16)
        self.paper_w, self.paper_h = 297.0, 210.0

        # Dimensions in mm of plot area
        self.width = 297.0
        # height = 175.0
        self.height = 175.0
        self.margin_left = self.margin_right = 0.1 * (self.paper_w - self.width)
        self.margin_bottom = 10.0

        # Normalized in [0, 1]
        self.left = self.margin_left / self.paper_w
        self.right = self.left + self.width / self.paper_w
        self.bottom = self.margin_bottom / self.paper_h
        self.top = self.bottom + self.height / self.paper_h
        self.channel_definitions = sequence_item.ChannelDefinitionSequence
        self.wavewform_data = sequence_item.WaveformData
        self.channels_no = sequence_item.NumberOfWaveformChannels
        self.samples = sequence_item.NumberOfWaveformSamples
        self.sampling_frequency = sequence_item.SamplingFrequency
        self.duration = self.samples / self.sampling_frequency
        self.mm_s = self.width / self.duration
        self.signals = self._signals()


    def __del__(self):
        """
        Figures created through the pyplot interface
        (`matplotlib.pyplot.figure`) are retained until explicitly
        closed and may consume too much memory.
        """
        pass
        #plt.cla()
        #plt.clf()
        #plt.close()

    def create_figure(self):
        """Prepare figure and axes"""

        # Init figure and axes
        fig = plt.figure(tight_layout=False)
        axes = fig.add_subplot(1, 1, 1)

        fig.subplots_adjust(left=self.left, right=self.right, top=self.top,
                            bottom=self.bottom)

        axes.set_ylim([0, self.height])

        # We want to plot N points, where N=number of samples
        axes.set_xlim([0, self.samples - 1])
        return fig, axes

    def _signals(self):
        """
        Retrieve the signals from the DICOM WaveformData object.

        sequence_item := dicom.dataset.FileDataset.WaveformData[n]

        @return: a list of signals.
        @rtype: C{list}
        """

        factor = np.zeros(self.channels_no) + 1
        baseln = np.zeros(self.channels_no)
        units = []
        for idx in range(self.channels_no):
            definition = self.channel_definitions[idx]

            assert (definition.WaveformBitsStored == 16)

            if definition.get('ChannelSensitivity'):
                factor[idx] = (
                    float(definition.ChannelSensitivity) *
                    float(definition.ChannelSensitivityCorrectionFactor)
                )

            if definition.get('ChannelBaseline'):
                baseln[idx] = float(definition.get('ChannelBaseline'))

            units.append(
                definition.ChannelSensitivityUnitsSequence[0].CodeValue
            )

        unpack_fmt = '<%dh' % (len(self.wavewform_data) / 2)
        unpacked_waveform_data = struct.unpack(unpack_fmt, self.wavewform_data)
        signals = np.asarray(
            unpacked_waveform_data,
            dtype=np.float32).reshape(
            self.samples,
            self.channels_no).transpose()

        for channel in range(self.channels_no):
            signals[channel] = (
                (signals[channel] + baseln[channel]) * factor[channel]
            )

        high = 40.0

        # conversion factor to obtain millivolts values
        millivolts = {'uV': 1000.0, 'mV': 1.0}

        for i, signal in enumerate(signals):
            signals[i] = butter_lowpass_filter(
                np.asarray(signal),
                high,
                self.sampling_frequency,
                order=2
            ) / millivolts[units[i]]

        return signals

    def draw_grid(self, minor_axis):
        """Draw the grid in the ecg plotting area."""

        if minor_axis:
            self.axis.xaxis.set_minor_locator(
                plt.LinearLocator(self.width + 1)
            )
            self.axis.yaxis.set_minor_locator(
                plt.LinearLocator(self.height + 1)
            )

        self.axis.xaxis.set_major_locator(
            plt.LinearLocator(self.width / 5 + 1)
        )
        self.axis.yaxis.set_major_locator(
            plt.LinearLocator(self.height / 5 + 1)
        )

        color = {'minor': '#ff5333', 'major': '#d43d1a'}
        linewidth = {'minor': .5, 'major': .8}

        for axe in 'x', 'y':
            for which in 'major', 'minor':
                self.axis.grid(
                    which=which,
                    axis=axe,
                    linestyle='-',
                    linewidth=linewidth[which],
                    color=color[which]
                )

                self.axis.tick_params(
                    which=which,
                    axis=axe,
                    color=color[which],
                    bottom='off',
                    top='off',
                    left='off',
                    right='off'
                )

        self.axis.set_xticklabels([])
        self.axis.set_yticklabels([])

    
    def plot(self, layoutid, mm_mv):
        """Plot the ecg signals inside the plotting area.
        Possible layout choice are:
        * 12x1 (one signal per line)
        * 6x2 (6 rows 2 columns)
        * 3x4 (4 signal chunk per line)
        * 3x4_1 (4 signal chunk per line. on the last line
        is drawn a complete signal)
        * ... and much much more

        The general rule is that the layout list is formed
        by as much lists as the number of lines we want to draw into the
        plotting area, each one containing the number of the signal chunk
        we want to plot in that line.

        @param layoutid: the desired layout
        @type layoutid: C{list} of C{list}
        """

        self.mm_mv = mm_mv

        layout = LAYOUT[layoutid]
        rows = len(layout)

        for numrow, row in enumerate(layout):

            columns = len(row)
            row_height = self.height / rows

            # Horizontal shift for lead labels and separators
            h_delta = self.samples / columns

            # Vertical shift of the origin
            v_delta = round(
                self.height * (1.0 - 1.0 / (rows * 2)) -
                numrow * (self.height / rows)
            )

            # Let's shift the origin on a multiple of 5 mm
            v_delta = (v_delta + 2.5) - (v_delta + 2.5) % 5

            # Lenght of a signal chunk
            chunk_size = int(self.samples / len(row))
            for numcol, signum in enumerate(row):
                left = numcol * chunk_size
                right = (1 + numcol) * chunk_size

                # The signal chunk, vertical shifted and
                # scaled by mm/mV factor
                signal = v_delta + mm_mv * self.signals[signum][left:right]
                self.axis.plot(
                    list(range(left, right)),
                    signal,
                    clip_on=False,
                    linewidth=1.2,
                    color='black',
                    zorder=10)

                cseq = self.channel_definitions[signum].ChannelSourceSequence
                meaning = cseq[0].CodeMeaning.replace(
                    'Lead', '').replace('(Einthoven)', '')

                h = h_delta * numcol
                v = v_delta + row_height / 2.6
                plt.plot(
                    [h, h],
                    [v - 3, v],
                    lw=.6,
                    color='black',
                    zorder=50
                )

                self.axis.text(
                    h + 40,
                    v_delta + row_height / 3,
                    meaning,
                    zorder=50,
                    fontsize=8
                )

        # A4 size in inches
        self.fig.set_size_inches(11.69, 8.37)


        

    def draw(self, layoutid, mm_mv=10.0, minor_axis=False, interpretation=False):
        """Draw grid, info and signals"""
        self.fig, self.axis = self.create_figure()
        self.draw_grid(minor_axis)
        self.plot(layoutid, mm_mv)
        self.axis.set_title("EKG_Viewer")
        plt.savefig('{0}.png'.format(layoutid))

class ECG_Data_Reader(object):
    """The class to read ECG rawdata from DICOM File"""

    def __init__(self,filename):
        """The ECG_Data_Reader class constructor"""
        if not filename.endswith('DCM'):
            print("Please input a dcm file")
            sys.exit()
        
        self.dicom = dicom.read_file(filename)
        sequence_item = self.dicom.WaveformSequence[0]
        assert (sequence_item.WaveformSampleInterpretation == 'SS')
        assert (sequence_item.WaveformBitsAllocated == 16)
        self.channel_definitions = sequence_item.ChannelDefinitionSequence
        self.wavewform_data = sequence_item.WaveformData
        self.channels_no = sequence_item.NumberOfWaveformChannels
        self.samples = sequence_item.NumberOfWaveformSamples
        self.sampling_frequency = sequence_item.SamplingFrequency
        self.duration = self.samples / self.sampling_frequency
        self.signals = self._signals()
    
    def _signals(self):
        """
        Retrieve the signals from the DICOM WaveformData object.

        sequence_item := dicom.dataset.FileDataset.WaveformData[n]

        @return: a list of signals.
        @rtype: C{list}
        """

        factor = np.zeros(self.channels_no) + 1
        baseln = np.zeros(self.channels_no)
        units = []
        for idx in range(self.channels_no):
            definition = self.channel_definitions[idx]

            assert (definition.WaveformBitsStored == 16)

            if definition.get('ChannelSensitivity'):
                factor[idx] = (
                    float(definition.ChannelSensitivity) *
                    float(definition.ChannelSensitivityCorrectionFactor)
                )

            if definition.get('ChannelBaseline'):
                baseln[idx] = float(definition.get('ChannelBaseline'))

            units.append(
                definition.ChannelSensitivityUnitsSequence[0].CodeValue
            )

        unpack_fmt = '<%dh' % (len(self.wavewform_data) / 2)
        unpacked_waveform_data = struct.unpack(unpack_fmt, self.wavewform_data)
        signals = np.asarray(
            unpacked_waveform_data,
            dtype=np.float32).reshape(
            self.samples,
            self.channels_no).transpose()

        for channel in range(self.channels_no):
            signals[channel] = (
                (signals[channel] + baseln[channel]) * factor[channel]
            )
        return signals
    
if __name__ == '__main__':
#    a = ECG('9.DCM')
#    a.draw('1')
#    a.draw('2')
#    a.draw('3')
#    a.draw('4')
#    a.draw('5')
#    a.draw('6')
#    a.draw('7')
#    a.draw('8')
#    a.draw('9')
#    a.draw('10')
#    a.draw('11')
#    a.draw('12')
    b = ECG('6.DCM')
    b.draw('6x2')
    #B = ECG_Data_Reader('./2.DCM')
    #print(B.signals.shape)
