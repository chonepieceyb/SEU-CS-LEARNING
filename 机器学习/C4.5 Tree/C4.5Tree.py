# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import os
import numpy as np
import math
PROJECT_DIR = os.path.dirname(__file__)
#项目根目录
DATA_DIR = os.path.join(PROJECT_DIR,'Data')

class DataObject(object):
    def __init__(self,line):
        line= line.strip()
        strList = line.split(' ')
        #第一个为key的值即关键码的值
        self.attributes=[]
        #把属性值添加进去
        for str in strList:
            self.attributes.append(str)
    def printDataObject(self):
        print(self.attributes)
    def getAttribute(self):
        return self.attributes

class DataSet(object):
    def __init__(self,fileDir):
        #文件组织详见DataSet里的readme
        with open(fileDir) as f:
            lines = f.readlines();
            #读取首行
            line0= lines[0];
            line0.strip()
            #读取属性的信息，考虑用两个列表来保存，方便和属性值一一对应，根据文件的组织，应该是一一对应的，第一行是属性的信息
            self.attributeName=[]
            self.attributeInfo=[]
            self.dataObjects = []
            for str in line0.split(' '):
                if len(str.split(":"))!=2:
                    continue
                key,value =str.split(":")
                self.attributeInfo.append(value)
                self.attributeName.append(key)
            #逐行读取属性值
            for line in lines[1:]:
                if len(line)<=0:
                    continue
                self.dataObjects.append(DataObject(line))
    def printDataSet(self):
        print(self.attributeName)
        print(self.attributeInfo)
        for dobject in self.dataObjects:
             dobject.printDataObject();
             
class C45Tree(object):
    #用上面定义的数据集对象来进行初始化
    def __init__(self,data, t_alpha=0.5):
        #属性
        '''
        input: data 数据集对象
        t_alpha PEP剪枝算法中的惩罚因子，默认为0.5
        '''
        def getData(ds):
            x=  len(ds.dataObjects)
            y=  len(ds.dataObjects[0].attributes)
            #初始化 类型为浮点数，如果数据集不符合要求应该先进行转化
            dataSet =[] 
            for i in range(0,x):
                dataSet.append([x for x in ds.dataObjects[i].attributes]) 
 
            return dataSet
        self.dataSet = getData(data)
        self.featureName=data.attributeName
        self.testFeatureName = self.featureName[1:]
        self.featureInfo =data.attributeInfo
        self.alpha =  t_alpha
         # 在这个代码中 树的数据结构是采用字典 tree = {subtree1:{subsubTree1:{} ....}, subtree2:{},subtree3:{}} 递归建树,叶节点是 class值 叶节点格式 {class :None} None作为终止标识符
        self.tree = self.createTree(self.dataSet,self.featureName) 
        #计算最常出现的值
        classValues =[item[0] for item in self.dataSet]
        self.maxClassValue = classValues[0];
        for currentValue in set(classValues):
                if classValues.count(currentValue) > classValues.count(self.maxClassValue):
                    self.maxClassValue = currentValue
        #剪枝操作
        self.purningByPEP(self.dataSet,self.tree,self.featureName)
    #将数据集分裂
  
    def splitDataSet(self,dataSet,axis,value):
        '''
            input:dataset 代分裂的样本集是一个numpy数组
                  axis 分裂的维度（即根据哪个属性进行分裂)
                  value 分裂的值  (根据分裂属性的取值进行分裂)
            output: 分裂之后新的样本集合
        '''
        #分裂后的数据集
        reDataSet = []
        for item in dataSet:  #遍历每一行
            if  item[axis]== value:  #如果满足分裂条件
                reItem = item[:axis]
                reItem.extend(item[axis+1:])
                reDataSet.append(reItem)
        return reDataSet

    def calInfoEnt(self,dataSet):
        '''
            计算信息熵函数
            input:数据集
            output:信息熵
        '''
        classCount ={}  #统计各个类别出现的次数
        sampleNum = len(dataSet)
        for item in dataSet:
            currentClass= item[0] #当前的类别
            if currentClass not in classCount.keys():
                classCount[currentClass]=0   #如果不在里面置0
            classCount[currentClass] +=1     #数目加1已经包括一开始不在里面的情况
        infoEnt = 0.0
        for currentClass in classCount.keys():
            prob= classCount[currentClass] / sampleNum #统计概率
            infoEnt += -(prob *math.log(prob,2))       # 逐项加和计算信息熵
        return infoEnt
    
    #计算信息增益
    def calInfoGain(self,dataSet,axis):
        '''
           input: dataSet 数据集
                  axis 分裂的属性
           output: infoGain
        '''
        sampleNum = len(dataSet) #样本数
        valueCount = {}  
        #统计属性A 的各个值的个数
        infoEnt = self.calInfoEnt(dataSet)
        for item in dataSet:
            currentValue = item[axis]
            if currentValue not in valueCount.keys():
                valueCount[currentValue] = 0
            valueCount[currentValue]+=1     
       #逐项计算信息增益
        infoEntAxis = 0.0
        for currentValue in valueCount.keys():
            prob = valueCount[currentValue] / sampleNum  #权重，currentValue所占的比例
            infoEntAxis += -prob*self.calInfoEnt(self.splitDataSet(dataSet,axis,currentValue))
        return infoEnt - infoEntAxis    #信息增益的公式
    #计算分裂信息的函数
    def calSplitInfo(self,dataSet,axis):
        '''
             input: dataSet 数据集
                  axis 分裂的属性
             output: splitInfo
        '''
        
        sampleNum = len(dataSet) #样本数
        valueCount = {}  
        #统计属性A 的各个值的个数
        for item in dataSet:
            currentValue = item[axis]
            if currentValue not in valueCount.keys():
                valueCount[currentValue] = 0
            valueCount[currentValue]+=1 
        if(len(valueCount)<=1):
            return 0.00001
        assert(len(valueCount)>1)
        #逐项计算信息增益
        splitInfo = 0.0
        for currentValue in valueCount.keys():
            prob = valueCount[currentValue] / sampleNum  #prob 是 |Si| / |S|
            splitInfo -= prob*math.log(prob,2)     
        assert(splitInfo!=0)
        return splitInfo
    #计算信息增一律
    def calInfoGainRate(self,dataSet,axis):
        return self.calInfoGain(dataSet,axis)/self.calSplitInfo(dataSet,axis)
    
    #根据C45算法选择最佳分裂属性
    def chooseBestSplitFeature(self,dataSet,featureNameTable):
        '''
            input:dataSet 数据集
                  featureNameTable 属性名称（包括class和属性）和dataSet的列下标一一对应
            output: bestAxis,bestFeature 最佳分裂的属性的列值和名称
        '''
        #当只剩下一个属性的时候就不用选择了
        if len(featureNameTable)==2 : #2是因为还包括class
            return 1,featureNameTable[1]
        #初始值,选择属性 1 
        for i in range(1,len(featureNameTable)):    #从第二个属性开始
            if i==1:
                maxInfoGainRate = self.calInfoGainRate(dataSet,i)
                bestAxis=i
                break;
            currentInfoGainRate = self.calInfoGainRate(dataSet,i)
            if currentInfoGainRate > maxInfoGainRate:
                maxInfoGainRate = currentInfoGainRate
                bestAxis = i
        return bestAxis , featureNameTable[bestAxis]
    #建C45树
    def createTree(self,dataSet,featureNameTable):
        '''
            建树的函数，采用递归建树的策略
            input: 
                   dataSet :数据集 是一个List
                   classNameTable dataSet里属性名称的列表(同时包含类别和属性），classNameTable 和 dataSet的列下标 一一对应
            output : a C45Tree
        '''
        classValues =[item[0] for item in dataSet] #取第一列，也就是所有类别的值
        #边界条件
        #如果数据集为空
        if len(dataSet)<=0:
            return    #啥都不返回
        #如果属性列表(只剩下class那一列）为空，返回dataSet多数类
        if len(featureNameTable)<=1:
            #统计多数类
            maxClassValue = classValues[0];  #初值
            for currentValue in classValues:
                if currentValue != maxClassValue and classValues.count(currentValue) > classValues.count(maxClassValue):
                    maxClassValue = currentValue
            return {maxClassValue :None}  #返回类型值
        #如果均为同一个类别的class
        if classValues.count(classValues[0]) == len(classValues)  :       
            return {classValues[0]:None}
        #开始递归建树
        C45Tree ={}  #定义空树
        #选择最佳分裂属性
        bestAxis, bestFeature=self.chooseBestSplitFeature(dataSet,featureNameTable)
        #根据最佳分裂属性分裂，建树
        #首先确定根节点,子树为空
        C45Tree[bestFeature]={}   
        #统计该属性下出现的值的类型数目,转化为集合即可，因为集合的元素不会重复出现，取bestFeature列
        valueSet = set([item[bestAxis] for item in dataSet])
        #更改featureNameTable，删除bestAxis列
        newFeatureNameTable = featureNameTable[:bestAxis]
        newFeatureNameTable.extend(featureNameTable[bestAxis+1:])
        #分裂，并递归建立子树
        for value in valueSet:
            C45Tree[bestFeature][value] = self.createTree(self.splitDataSet(dataSet,bestAxis,value),newFeatureNameTable)
        return C45Tree;
        
    #决策函数,批量决策
    def makeDecision(self,testDataSet,tree,featureNameTable):
        '''
            input:testDataSet:测试集（不包括类别）
                  tree :决策使用的决策树
                  featureNameTable: 名称和下标对应，不包括类型
                  output: 决策结果 n*1 列表的值是分类得到的类别
            注:这里默认每一个属性都是有值的      
        '''
        testResult=[]; #测试结果集
       
        assert(len(testDataSet)>0)
        for i in range(len(testDataSet)):
            testItem = testDataSet[i]
            result =self.makeDesicionByOne(testItem,tree,featureNameTable)
            if result!=None:   #有结果
                testResult.append(result)
            else:   #如果找不到，就赋值整个训练集中最长出现的类
                testResult.append(self.maxClassValue)
            
        return testResult
    #采用递归决策
    def makeDesicionByOne(self, testItem,tree,featureNameTable):  #决策单个数据样本
        '''
            input:testItem 单个样本
                  tree 决策树
                  featureNameTable :名称和下标对应，不包括类型
        '''
          #如果tree是叶子节点
        if len(tree)==1 :
            for classValue in tree.keys():
                if tree[classValue] == None:
                    return classValue
        assert(len(tree)>0)
        #如果tree不是叶子节点
        #获取决策的属性，即根节点
        decidingFeature = []
        for feature in tree.keys():
            decidingFeature.append(feature)
        assert(len(decidingFeature)==1)   #根据数据结构的定义 tree的key应该只有一个
        decidingFeature = decidingFeature[0]
        decidingAxis = featureNameTable.index(decidingFeature)
        #获取该属性对应的值
        value = testItem[decidingAxis]
        #递归决策
        #如果子树存在的话
        #删除 decidingAxis列
        newFeatureNameTable = featureNameTable[:decidingAxis]
        newFeatureNameTable.extend(featureNameTable[decidingAxis+1:])
        
        newTestItem = testItem[:decidingAxis]
        newTestItem.extend(testItem[decidingAxis+1:])
        if value in tree[decidingFeature].keys():  
            return self.makeDesicionByOne( newTestItem ,tree[decidingFeature][value], newFeatureNameTable)
        else:
            return None
        #如果子树不存在，意味着无法到达叶节点 返回空
    
    #计算叶子节点个数的函数
    def calLeaveNum(self,tree):
        '''
            input:tree 树
            output: 叶子节点的个数
        '''
        leaveNum=0
        #边界
        #如果tree是叶子节点
        if len(tree)==1 :
            for classValue in tree.keys():
                if tree[classValue] == None:
                    return 1
        
        for value in tree.values():
            for key in value.keys():
                leaveNum += self.calLeaveNum(value[key]);
        return leaveNum

    #计算子树的误判率,方便剪枝条
    def calErrorRatio(self,dataSet,tree,testFeatureTable):
        '''
            input: tree子树
                   dataSet:训练集合（包含有class的）
            output errorRatio
        '''
        #根据训练集得到测试集
        testDataSet = [item[1:] for item in dataSet]
        #获取训练集的class value
        classValue = [item[0] for item in dataSet]
        #将测试集进行决策 得到结果
        testResult = self.makeDecision(testDataSet,tree,testFeatureTable)
        #对比测试结果和标准结果，计算误差率
        assert(len(testResult)==len(classValue))  #测试结果个数和标准结果的个数应该相同
        errorNum=0
        for i in range(len(testResult)):
            if testResult[i] != classValue[i]:
                errorNum +=1
        errorRatio = 0.0
        errorRatio= (errorNum + self.alpha * self.calLeaveNum(tree)) / len(dataSet)  #根据公式 errorRatio = errorNum*L/N L是叶子节点的个数， N是样本总数
        return  errorRatio

    #剪枝函数 递归建枝,采用PEP算法
    def purningByPEP(self,dataSet,tree,featureNameTable):
        """
            input:dataSet tree classNameTable 同之前
        """
        #如果是tree是叶子节点不剪
        if len(tree)==1 :
            for classValue in tree.keys():
                if tree[classValue] == None:
                    return 1

        #不是叶子
        sampleNum = len(dataSet)
        #得到误差率
        errorRatioForTree  = self.calErrorRatio(dataSet,tree,featureNameTable[1:]);
        #剪枝前的数学期望,概率分布为伯努利分布
        errorMeanForTree = errorRatioForTree *sampleNum
        errorSTDForTree = math.sqrt(errorRatioForTree*(1-errorRatioForTree)*sampleNum)
        
        #在样本中找到种类最多的类型
        classValues =[item[0] for item in self.dataSet]
        maxClassValue = classValues[0];
        for currentValue in set(classValues):
                if classValues.count(currentValue) > classValues.count(maxClassValue):
                    maxClassValue = currentValue
        #替换为叶节点之后的错误率            
        errorRatioForLeave = (sampleNum - classValue.count( maxClassValue) + self.alpha)/sampleNum
        errirNeanForLeave = errorRatioForLeave* sampleNum
        #判断是否满足简直条件
        print(errorMeanForTree + errorSTDForTree,errirNeanForLeave)
        if(errorMeanForTree + errorSTDForTree >= errirNeanForLeave):   #决定剪枝条
            #生成叶节点,根据python的特性（python函数参数传递的是对象）所以直接对原始的tree进行操作，不能采用 = 必须用 append 特别小心
            print("剪枝了",tree)
            tree.clear();
            tree[ maxClassValue] = None
            print(tree)
        else:  #递归剪枝，对子树进行剪枝，自上而下
             #找到根节点
             root = []
             for feature in tree.keys():
                 root.append(feature)
             assert(len(root)==1)   #根据数据结构的定义 tree的key应该只有一个
             root = root[0]
             rootAxis = featureNameTable.index(root)
             #递归剪枝
             #取值
             valueSet= set([item[rootAxis] for item in dataSet])
             newFeatureNameTable = featureNameTable[:rootAxis]
             newFeatureNameTable.extend(featureNameTable[rootAxis+1:])
             for value in valueSet:
                 self.purningByPEP(self.splitDataSet(dataSet,rootAxis,value),tree[root][value],newFeatureNameTable)



#测试代码
FILE_NAME =os.path.join(DATA_DIR,'data.txt')
D= DataSet(FILE_NAME)
print(D)
c = C45Tree(D)
print(c.tree)
dataSet = c.dataSet;
testDataSet = [item[1:] for item in dataSet]
print(c.makeDecision(testDataSet,c.tree,c.testFeatureName))
print(c.calLeaveNum(c.tree))
print(c.calErrorRatio(c.dataSet,c.tree,c.testFeatureName))