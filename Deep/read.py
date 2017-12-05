# -*- coding: utf-8 -*-
"""
Created on Tue Nov 28 15:24:19 2017

@author: Alex Wang
"""
import tensorflow as tf
from sklearn.decomposition import PCA

ekg_data = []
ekg_label = []
ekg_train_data = []
ekg_train_label = []
ekg_test_data = []
ekg_test_label = []



# prepare the ekg data 
with open(r'C:\Users\Administrator\Desktop\Deep\EKG.txt','r') as f:
    data = f.read().split("\n")[0:-1]
    for sub_data in data:
        ekg_asrow = []
        point = sub_data.split(" ")
        for sub_point in point[0:-1]:
            ekg_asrow.append(float(sub_point))
        ekg_data.append(ekg_asrow)
    
#PCA
    pca = PCA(n_components=20)
    project = pca.fit_transform(ekg_data)
    back_project = pca.inverse_transform(project)    
    ekg_train_data = back_project[0:len(back_project)-40]
    ekg_test_data = back_project[len(back_project)-40:-1]



    
        
#prepare the ekg label
for j in range(len(ekg_test_data)):
        test_label = []
        test_label.insert(j % 10, 1)
        for i in range(10):
            if( (j % 10) != i):
                test_label.insert(i, 0)
        ekg_test_label.append(test_label)

        
    
for j in range(len(ekg_train_data)):
        train_label = []
        train_label.insert(j % 10, 1)
        for i in range(10):
            if( (j % 10) != i):
                train_label.insert(i, 0)
        ekg_train_label.append(train_label)




#neural network
INPUT_NODE = 60000  # 1 row, 60000 cols
OUTPUT_NODE = 10    # number of result 
LAYER1_NODE = 100   # hidden layer nodes

LEARNING_RATE_BASE = 0.8
LEARNING_RATE_DECAY = 0.99
REGULARIZATION_RATE = 0.0001
TRAINING_STEPS = 30000
MOVING_AVERAGE_DECAY = 0.99


def inference(input_tensor, avg_class, weights1, biases1, weights2, biases2):
    if avg_class == None:
        layer1 = tf.nn.tanh(tf.matmul(input_tensor,weights1) + biases1)
        return tf.matmul(layer1, weights2) + biases2
    else:
        layer1 = tf.nn.tanh(tf.matmul(input_tensor, avg_class.average(weights1)) + biases1)
        return tf.matmul(layer1, avg_class.average(weights2) + biases2)

def train():
    x= tf.placeholder(tf.float32, [None, INPUT_NODE], name = "x")
    y_ = tf.placeholder(tf.float32,[None,OUTPUT_NODE], name = "y_")
    weights1 = tf.Variable(tf.truncated_normal([INPUT_NODE, LAYER1_NODE], stddev = 0.5))
    biases1 = tf.Variable(tf.constant(0.5, shape = [LAYER1_NODE]))
    weights2 = tf.Variable(tf.truncated_normal([LAYER1_NODE, OUTPUT_NODE], stddev= 0.5))
    biases2 = tf.Variable(tf.constant(0.5, shape = [OUTPUT_NODE]))
    y = inference(x, None, weights1, biases1, weights2, biases2)
    
    global_step = tf.Variable(0, trainable = False)
    variable_average = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY,global_step)
    variable_average_op = variable_average.apply(tf.trainable_variables())
    
    average_y = inference(x, variable_average, weights1, biases1, weights2, biases2)
    
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits = y, labels = tf.argmax(y_, 1))
    cross_entroy_mean = tf.reduce_mean(cross_entropy)
    
    regularizer = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    regularization = regularizer(weights1) + regularizer(weights2)
    
    loss = cross_entroy_mean + regularization
    
    learning_rate = tf.train.exponential_decay(LEARNING_RATE_BASE, global_step, 
                                               len(ekg_data), LEARNING_RATE_DECAY)
    
    train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss, global_step = global_step)    
    with tf.control_dependencies([train_step, variable_average_op]):
        train_op = tf.no_op(name = 'train')
    correct_prediction = tf.equal(tf.argmax(average_y, 1), tf.argmax(y_, 1))
    accurary = tf.reduce_mean(tf.cast(correct_prediction,tf.float32))

    with tf.Session() as sess:
        init = tf.global_variables_initializer()
        sess.run(init)
        test_feed = {x:ekg_test_data, y_:ekg_test_label}
        for i in range(TRAINING_STEPS):
            if(i % 1000 == 0):
                sess.run(train_op, feed_dict = {x:ekg_train_data, y_:ekg_train_label})
                test_acc = sess.run(accurary, feed_dict = test_feed)
                print("After %d training step(s), test accuracy using average model is %g %%" 
                      %(i,test_acc*100)) 


           
def main(argv = None):
    train()

if __name__ == '__main__':
    tf.app.run()
 