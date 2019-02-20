# -*- coding: utf-8 -*-
"""
Created on Fri Dec 21 15:48:35 2018

@author: robot
"""
import numpy as np
import tensorflow as tf

'''
3                                       # 这个 0 阶张量就是标量，shape=[]
[1., 2., 3.]                            # 这个 1 阶张量就是向量，shape=[3]
[[1., 2., 3.], [4., 5., 6.]]            # 这个 2 阶张量就是二维数组，shape=[2, 3]
[[[1., 2., 3.]], [[7., 8., 9.]]]        # 这个 3 阶张量就是三维数组，shape=[2, 1, 3]
# 创建一个整型常量，即 0 阶 Tensor
t0 = tf.constant(3, dtype=tf.int32)
# 创建一个浮点数的一维数组，即 1 阶 Tensor
t1 = tf.constant([3., 4.1, 5.2], dtype=tf.float32)
# 创建一个字符串的2x2数组，即 2 阶 Tensor
t2 = tf.constant([['Apple', 'Orange'], ['Potato', 'Tomato']], dtype=tf.string)
# 创建一个 2x3x1 数组，即 3 阶张量，数据类型默认为整型
t3 = tf.constant([[[5], [6], [7]], [[4], [3], [2]]])

线性模型 y=W×x+b
'''

# 创建变量 W 和 b 节点，并设置初始值
W = tf.Variable([.1], dtype=tf.float32)
b = tf.Variable([-.1], dtype=tf.float32)
# 创建 x 节点，用来输入实验中的输入数据
x = tf.placeholder(tf.float32)
# 创建线性模型
linear_model = W*x + b

# 创建 y 节点，用来输入实验中得到的输出数据，用于损失模型计算
y = tf.placeholder(tf.float32)
# 创建损失模型
loss = tf.reduce_sum(tf.square(linear_model - y))

# 创建 Session 用来计算模型
sess = tf.Session()

# 初始化变量
init = tf.global_variables_initializer()
sess.run(init)
# Test_1
print(sess.run(linear_model, {x: [1, 2, 3, 6, 8]}))
# Test_2运行一下损失模型
print(sess.run(loss, {x: [1, 2, 3, 6, 8], y: [4.8, 8.5, 10.4, 21.0, 25.3]}))

# Test_3用tf.assign()对W和b变量重新赋值再检验一下：
# 给 W 和 b 赋新值
fixW = tf.assign(W, [2.])
fixb = tf.assign(b, [1.])
# run 之后新值才会生效
sess.run([fixW, fixb])
# 重新验证损失值
print(sess.run(loss, {x: [1, 2, 3, 6, 8], y: [4.8, 8.5, 10.4, 21.0, 25.3]}))

# Test_4 梯度下降(Gradient Descent)算法:通过不断的改变模型中变量的值，来找到最小损失值
# 创建一个梯度下降优化器，学习率为0.001
optimizer = tf.train.GradientDescentOptimizer(0.001)
train = optimizer.minimize(loss)

# 用两个数组保存训练数据
x_train = [1, 2, 3, 6, 8]
y_train = [4.8, 8.5, 10.4, 21.0, 25.3]

# 训练10000次
for i in range(10000):
    sess.run(train, {x: x_train, y: y_train})

# 打印一下训练后的结果 得到一个自认为损失最小的最优模型y=2.98x+2.07
print('W: %s b: %s loss: %s' % (sess.run(W), sess.run(b), sess.run(loss, {x: x_train , y: y_train})))


#使用LinearRegressor

# 创建一个特征向量列表，该特征列表里只有一个特征向量，
# 该特征向量为实数向量，只有一个元素的数组，且该元素名称为 x，
# 我们还可以创建其他更加复杂的特征列表
feature_columns = [tf.feature_column.numeric_column("x", shape=[1])]

# 创建一个LinearRegressor训练器，并传入特征向量列表
estimator = tf.estimator.LinearRegressor(feature_columns=feature_columns)

# 保存训练用的数据
x_train = np.array([1., 2., 3., 6., 8.])
y_train = np.array([4.8, 8.5, 10.4, 21.0, 25.3])

# 保存评估用的数据
x_eavl = np.array([2., 5., 7., 9.])
y_eavl = np.array([7.6, 17.2, 23.6, 28.8])

# 用训练数据创建一个输入模型，用来进行后面的模型训练
# 第一个参数用来作为线性回归模型的输入数据
# 第二个参数用来作为线性回归模型损失模型的输入
# 第三个参数batch_size表示每批训练数据的个数
# 第四个参数num_epochs为epoch的次数，将训练集的所有数据都训练一遍为1次epoch
# 第五个参数shuffle为取训练数据是顺序取还是随机取
train_input_fn = tf.estimator.inputs.numpy_input_fn(
    {"x": x_train}, y_train, batch_size=2, num_epochs=None, shuffle=True)

# 再用训练数据创建一个输入模型，用来进行后面的模型评估
train_input_fn_2 = tf.estimator.inputs.numpy_input_fn(
    {"x": x_train}, y_train, batch_size=2, num_epochs=1000, shuffle=False)

# 用评估数据创建一个输入模型，用来进行后面的模型评估
eval_input_fn = tf.estimator.inputs.numpy_input_fn(
    {"x": x_eavl}, y_eavl, batch_size=2, num_epochs=1000, shuffle=False)

# 使用训练数据训练1000次
estimator.train(input_fn=train_input_fn, steps=1000)

# 使用原来训练数据评估一下模型，目的是查看训练的结果
train_metrics = estimator.evaluate(input_fn=train_input_fn_2)
print("train metrics: %r" % train_metrics)

# 使用评估数据评估一下模型，目的是验证模型的泛化性能
eval_metrics = estimator.evaluate(input_fn=eval_input_fn)
print("eval metrics: %s" % eval_metrics)


