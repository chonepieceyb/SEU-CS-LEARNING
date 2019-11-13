import numpy as np
import os
from tensorflow.examples.tutorials.mnist import input_data
import tensorflow as tf

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
mnist = input_data.read_data_sets(os.path.join(BASE_DIR,"MNIST"), one_hot=True)

# 模型配置
class Config(object):
    def __init__(self):
        self.BATCH_SIZE = 30
        self.LEARN_RATE= 0.01
        self.DROP_OUT = 0.25
        self.IMG_WIDTH= 28
        self.IMG_HIGHT = 28
        self.CHANNEL =1
config = Config()
regularizer ={}
kernal_regularizer =None
# 网络层
def auto_encoder(scope,noise_input,gt,end_points,kernal=[28,28,1],mode = "pre_train",regularizer,activation=tf.nn.relu,config=config):
    assert(mode in ["pre_train","fine_tune"])
    with tf.get_variable_scope(scope,reuse=True):
        noise_input = tf.reshape(noise_input,[-1,config.IMG_HIGHT,config.IMG_WIDTH],config.CHANNEL)  # reshape to (batch,H,W,C)
        code_result = tf.layers.conv2d(noise_input,config.CHANNEL,kernal,name="coder_conv2D",activation=activation)
        end_points[scope+'AD_coder_act_result']  =  code_result
        if mode == 'pre_train':
            pre_train = True
        else:
            pre_train= False
        output=tf.cond(pre_train,
                lambda cr:  tf.layers.conv2d(cr,config.CHANNEL,kernal,name="decoder_conv2D",activation=activation),
                lambda cr:cr ,
                name = "AD_COND"
        )
        end_points[scope+'AD_result'] = output
        return output

