/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myrtsai;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import static java.lang.Math.random;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 *
 * @author msi-
 */
public class Qlearning {
    //属性：
    int actionNum;
    int stateNum;
    String QMatrixFileName;
    String rewardFileName;
    File QMatrixFile = null;
    File rewardFile=null;
    double alphaR;         //R矩阵的学习率
    double alpha;          //Q矩阵的学习率
    double r;    //远见率
    double rewardMatrix[][]=null;
    double QMatrix[][]=null;    //Q矩阵
    int actionLast;        //上一步的决策 即 a_n-1
    int stateLast;         //上一步的状态 即 s_n-1
    int learningTime;  //学习次数
    double QChangeRate;
    double AllQChangeRate;
    double RChangeRate;
    double AllRChangedRate;
 //方法
    /*
    构造函数
    input: a:action 数目
           s:state数目
           a1: alpha的值
           r1：r的值
           QFile： 文件名，从文件中，读取Q矩阵
           rFile:     文件名，从文件中读取reward矩阵
           
    */
    Qlearning(int a,int s,double a1,double r1, String QFile,String rFile){
        //数据的初始化
        actionNum=a; stateNum=s; alpha=a1; r=r1; learningTime=0;
        QMatrixFileName=QFile;
        rewardFileName =  rFile;
        rewardMatrix=new double[actionNum][stateNum];
        QMatrix= new double[actionNum][stateNum];
        actionLast=-1;
        stateLast=-1;
        try{
            QMatrixFile = new File(QMatrixFileName);
            rewardFile = new File(rewardFileName);
            //检查文件是否存在,如果不存在新建文件，并且对两个矩阵的数据进行初始化
            if(!QMatrixFile.exists()&&!rewardFile.exists()){
                  System.out.println("创建数据");
                  QMatrixFile.createNewFile();
                  rewardFile.createNewFile();
                  //初始化Q和R矩阵
                  int i,j;
                  for(i=0;i<actionNum;i++){
                      for(j=0;j<stateNum;j++){
                          QMatrix[i][j] = 0;
                      }
                  }
                  //电脑写reward
                  //这里是按章19个state 进行赋值，具体情况要有所改动
                  for(i=0;i<actionNum;i++){
                      for(j=0;j<stateNum;j++){
                        // rewardMatrix[i][j] = (int)((j/20)-4)*10;
                         rewardMatrix[i][j]=0;
                      }
                  }
                  //写入数据
                  writeToFile(true);
            }else{
                //从文件中读取数据  
                System.out.println("读取数据");
                readFromFile();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    //构造函数的重载
    Qlearning(int a,int s, double a1,double r1, double a2,String QFile ,String rFile){
        this(a,s,a1,r1,QFile,rFile);
        alphaR=a2;
     }
    public void reset(int a,int s,double a1,double r1, String QFile,String rFile){
        actionNum=a; stateNum=s; alpha=a1; r=r1;  learningTime=0;
        QMatrixFileName=QFile;
        rewardFileName =  rFile;
        rewardMatrix=new double[actionNum][stateNum];
        QMatrix= new double[actionNum][stateNum];
        actionLast=-1;
        stateLast=-1;
        try{
            QMatrixFile = new File(QMatrixFileName);
            rewardFile = new File(rewardFileName);
            //检查文件是否存在,如果不存在新建文件，并且对两个矩阵的数据进行初始化
            if(!QMatrixFile.exists()&&!rewardFile.exists()){
                  System.out.println("创建数据");
                  QMatrixFile.createNewFile();
                  rewardFile.createNewFile();
                  //初始化Q和R矩阵
                  int i,j;
                  for(i=0;i<actionNum;i++){
                      for(j=0;j<stateNum;j++){
                          QMatrix[i][j] = 0;
                      }
                  }
                  //电脑写reward
                  //这里是按章380个state 进行赋值，具体情况要有所改动
                  for(i=0;i<actionNum;i++){
                      for(j=0;j<stateNum;j++){
                         //rewardMatrix[i][j] = (int)((j/20)-4)*10;
                         rewardMatrix[i][j]=0;
                      }
                  }
                  //写入数据
                  writeToFile(true);
            }else{
                //从文件中读取数据  
                System.out.println("读取数据");
                readFromFile();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    // reset函数的重载增加了对R学习率的初始化
    public void reset(int a,int s, double a1,double r1,double a2,String QFile ,String rFile){
        alphaR=a2;
        this.reset(a, s, a1, r1, QFile, rFile);
    }
    //文件读取和写入的函数
    private void readFromFile(){
        //采用字符流
        try{
            //创建流对象
            InputStreamReader QReader = new InputStreamReader(new FileInputStream(QMatrixFile));
            InputStreamReader R_Reader= new InputStreamReader(new FileInputStream(rewardFile));
            BufferedReader QBuffer = new BufferedReader(QReader);
            BufferedReader R_Buffer= new BufferedReader(R_Reader);
            //开始读数据
            String Qline="";   
            String Rline="";
            //有bug:不是actionNum
            String Q_DoubleString[] = new String[stateNum]; //用来存放Q数据的字符串数组
            String R_DoubleString[] = new String[stateNum]; //用来存放R数据的字符串数组
            //一行一行地读数据
            int i;
            for(i = 0;i<actionNum;i++){
                Qline=QBuffer.readLine();
                Rline = R_Buffer.readLine();
                if(Qline!=null && Rline!=null){
                    //将数据切割（文本文件中数据按照空格隔开
                    Q_DoubleString = Qline.split(" ");
                    R_DoubleString = Rline.split(" ");
                    //赋值
                    int j;
                    for(j=0;j<stateNum;j++){
                        QMatrix[i][j]=Double.parseDouble(Q_DoubleString[j]);
                        rewardMatrix[i][j]= Double.parseDouble(R_DoubleString[j]);
                    }
                }
            }
            //关闭流
            QBuffer.close();
            R_Buffer.close();
             QReader.close();
             R_Reader.close();
        }catch(Exception e){
            e.printStackTrace();
        }
 
    }
    
    //input： bool 是否写reward矩阵
    private void writeToFile(boolean isWriteReward){
      //保留两位有效小鼠
     DecimalFormat f = new DecimalFormat("#.00");
      System.out.println("开始写Q矩阵");
      try{
          BufferedWriter QWriter = new BufferedWriter(new FileWriter(QMatrixFile));
          //开始写Q矩阵
          int i,j;
          for(i=0;i<actionNum;i++){
              for(j=0;j<stateNum;j++){
                  //写Q
                  QWriter.write( f.format(QMatrix[i][j]));
                  QWriter.write(" ");
              }
              //换行
              QWriter.newLine();
          }
          //将流压入文件
          QWriter.flush();
          //关闭流
          QWriter.close();
          //开始写R矩阵
          if(isWriteReward){
             BufferedWriter RWriter = new BufferedWriter(new FileWriter(rewardFile));
             for(i=0;i<actionNum;i++){
                for(j=0;j<stateNum;j++){
                    //写R
                    RWriter.write(f.format(rewardMatrix[i][j]));
                    RWriter.write(" ");
                }
                //换行
                RWriter.newLine();
              }
              //将流压入文件
              RWriter.flush();
               //关闭流
              RWriter.close();
          }  
      }catch(Exception e){
          e.printStackTrace();
      }
        
    }
    
    /*
    决策函数
    input : state : 当前状态
    output : int 返回需要采取的行动, -1表示决策出错
    */
    public int makeDecision(int state){
        List<Integer> maxNumPoses = new ArrayList<>();
        double maxNum=0;
        if(state>=stateNum || state<0){
            return -1;
        }
        int i;
        int action=-1;
        for(i=0;i<actionNum;i++){    //如果有多个Q值相同的话取第一个
           if(i==0){
               maxNum  = QMatrix[i][state];
           }else{
               if(QMatrix[i][state]> maxNum ){
                  maxNum  = QMatrix[i][state];
               }
           }
        }
        for(i=0;i<actionNum;i++){
            if(QMatrix[i][state]==maxNum){
                maxNumPoses.add(i);
            }
        }
        //从相同的值随机选一个
        Random r = new Random();
        System.out.println(maxNumPoses.size());
        int maxPos = 0+r.nextInt(maxNumPoses.size());
        return maxNumPoses.get(maxPos);
    }
    /*
    这个函数 根据 statelast actionlast 和当前的state来更新QMatrix
    input: state 当前的状态
    */
    public void updateQMatrix(int state){
        //根据当前state获取上一步在state下决策的最佳action
        int action=-1;
        //注意这时候的QMatrix是 Q_n-1
        action=makeDecision(state);
        //将Q_n-1 更新成为 Q_n
        if(action!=-1){    //决策有效
            QMatrix[actionLast][stateLast] =(1-alpha)*QMatrix[actionLast][stateLast]+ alpha*( rewardMatrix[actionLast][stateLast]+ r* QMatrix[action][state]); 
            System.out.println("更新训练"+actionLast+" "+stateLast+" "+ QMatrix[actionLast][stateLast] );
        }
    }
    
    //update函数重载，采用动态的方式获取reward,但是reward需要从外部给
    public void updateQMatrix(int state,int reward){
        //根据当前state获取上一步在state下决策的最佳action
        int action=-1;
        //注意这时候的QMatrix是 Q_n-1
        action=makeDecision(state);
        //将Q_n-1 更新成为 Q_n
        if(action!=-1){    //决策有效
            QMatrix[actionLast][stateLast] =(1-alpha)*QMatrix[actionLast][stateLast]+ alpha*(  reward+ r* QMatrix[action][state]); 
            System.out.println("更新训练"+actionLast+" "+stateLast+" "+ QMatrix[actionLast][stateLast] );
        }
    }
    /*
        更新R矩阵的函数,这是对上一步的reward进行更新
        input: reward 当前的reward
   */
    public void updateRMatrix(int reward){
       if(actionLast!=-1){//如果决策是有效的
           this.rewardMatrix[actionLast][stateLast]  = this.rewardMatrix[actionLast][stateLast]*(1-alphaR) + alphaR*reward;
       }
    }

       
    /*
    Qlearning 学习函数
    inputt : state 当前的状态
             isWriteQ : 是否将更新后的Q矩阵写入到文件中 
             isWriteR :  是否将更新后的R矩阵写入文件中
              boolean isPrintLog:是否打印log
    output: 在当前状态下采取的action
    */
    public int learningQ( int state,boolean isWriteQ,boolean isWriteR,boolean isPrintLog){
    //先根据当前的state更新上一步决策 的Q矩阵
    // 如果不是第一次 ，由于第一次决策没有上一次，所以不进行更新
       int[] logState = new int[2]; int[] logAction = new int[2]; double logReward=-1; double[] logR = new double[2]; double[] logQ = new double[2];
       int actionNow=-1;  //当前状态下的最佳决策
       if(actionLast!=-1 && stateLast!=-1){
           //先更新
           learningTime++;   //学习次数+1
           if(isPrintLog){
               //搜集更新前的信息
               logState[0]= this.stateLast;                
               logAction[0]= this.actionLast;
               logReward = rewardMatrix[actionLast][stateLast];
               logR[0]= this.rewardMatrix[actionLast][stateLast];
               logQ[0]= this.QMatrix[actionLast][stateLast];
           }
           updateQMatrix(state);
        }else{

           //否则直接决策
           actionNow= makeDecision(state);
           //将当前的状态和决策保存下来，以便于下一次决策前进行Q矩阵的更新
           actionLast=actionNow;
           stateLast=state;
           if(isWriteQ){
                writeToFile(isWriteR);
           }
           return actionNow;
       }
       //更新之后进行决策
       actionNow =  makeDecision(state);
       actionLast=actionNow;
       stateLast=state;
       if(isPrintLog){
           //搜集之后的信息
           logAction[1] = actionNow;
           logState[1]= state;
           //这两个是更新Q R  也就是update之后的信息
           logR[1]= this.rewardMatrix[actionLast][stateLast];
           logQ[1]= this.QMatrix[actionLast][stateLast];
           //打印log
           this.printLog(logState, logAction, logReward, logR, logQ);
       }
       //根据参数决定是否写入文件
       if(isWriteQ){
           writeToFile(isWriteR);
       }
       //返回action
       return actionNow;
    }
    

   
    //对learning 函数的重载，采用外部的reward而不是内部的reward矩阵进行学习
    /*
    Qlearning 学习函数
    inputt : state 当前的状态
             reward 外部的r
             isWriteQ : 是否将更新后的Q矩阵写入到文件中 
             isWriteR: 是否将R矩阵写入文件中
             isPrintLog:是否打印log
    output: 在当前状态下采取的action
    */
    public int learningQ( int state,int reward,boolean isWriteQ ,boolean isWriteR,boolean isPrintLog){
    //先根据当前的state更新上一步决策 的Q矩阵
    // 如果不是第一次 ，由于第一次决策没有上一次，所以不进行更新
       int[] logState = new int[2]; int[] logAction = new int[2]; double logReward=-1; double[] logR = new double[2]; double[] logQ = new double[2];
       int actionNow=-1;  //当前状态下的最佳决策
       if(actionLast!=-1 && stateLast!=-1){
           //先更新
            learningTime++;   //学习次数+1
            if(isPrintLog){
               //搜集更新前的信息
               logState[0]= this.stateLast;                
               logAction[0]= this.actionLast;
               logReward = reward;
               logR[0]= this.rewardMatrix[actionLast][stateLast];
               logQ[0]= this.QMatrix[actionLast][stateLast];
           }
           updateQMatrix(state,reward);
        }else{
           //否则直接决策
           actionNow= makeDecision(state);
           //将当前的状态和决策保存下来，以便于下一次决策前进行Q矩阵的更新
           actionLast=actionNow;
           stateLast=state;
           if(isWriteQ){
                writeToFile(isWriteR); //这个是不是有问题啊？
           }
           return actionNow;
       }
       //更新之后进行决策
       actionNow =  makeDecision(state);

       
       if(isPrintLog){
           //搜集之后的信息
           logAction[1] = actionNow;
           logState[1]= state;
           //这两个是更新Q R  也就是update之后的信息
           logR[1]= this.rewardMatrix[actionLast][stateLast];
           logQ[1]= this.QMatrix[actionLast][stateLast];
           //打印log
           this.printLog(logState, logAction, logReward, logR, logQ);
       }
       //根据参数决定是否写入文件
       if(isWriteQ){
           writeToFile(isWriteR);
       }
       actionLast=actionNow;
       stateLast=state;
       //返回action
       return actionNow;
    }
    /*
    learning 函数的重载，学习Q矩阵的同时，学习R矩阵，同时用到R矩阵的结果，reward包括即时的reward和R矩阵的reward
         input: 
             state 当前的状态
             reward 外部的r
             isWriteQ : 是否将更新后的Q矩阵写入到文件中 
     i       isWriteR:是否写入R矩阵
    isPrintLog :是否打印log
    output: 在当前状态下采取的action
    */
   public int learningQR(int state,int reward,boolean isWriteQ, boolean isWriteR,boolean isPrintLog){
       //先更新，更新reward矩阵，更新的是上一个state 和action的reward
       //如果不是初始状态
        if(actionLast!=-1 && stateLast!=-1){//更新reward,学习R矩阵
             if(isPrintLog){
                System.out.println("进入同时学习Q和R的函数,在更新R的模块前：");
                 System.out.println("R矩阵更新前的值为："+this.rewardMatrix[actionLast][stateLast]);
            }
            this.updateRMatrix(reward);
            //学习Q矩阵
            return this.learningQ(state, reward, isWriteQ,isWriteR,isPrintLog);
        }else{
            //如果是初始状态不更新R矩阵（因为没有上一个状态)
            return this.learningQ(state, reward, isWriteQ,isWriteR,isPrintLog);
        }
  }

   //打印R矩阵的函数
   public void printRewardMatrix(){
       if(rewardMatrix==null){
           System.out.println("R矩阵还未创建");
       }
       int i,j;
       for(i=0;i<actionNum;i++){
           for(j=0;j<stateNum;j++){
               System.out.print(rewardMatrix[i][j]+" ");
           }
           System.out.print("\n");
       }
   }
   public void printLastS_A(){
       System.out.println("lastState"+ stateLast);
         System.out.println("lastAction"+ actionLast);
   }
   //返回上一个状态reward矩阵的值
   public double getRewardByR(){
       return rewardMatrix[actionLast][stateLast];
   }
      //打印Q矩阵的函数
   public void printQMatrix(){
       if(QMatrix==null){
           System.out.println("Q矩阵还未创建");
       }
       int i,j;
       for(i=0;i<actionNum;i++){
           for(j=0;j<stateNum;j++){
               System.out.print(QMatrix[i][j]+" ");
           }
           System.out.print("\n");
       }
   }
   //打印学习日志的函数
   /*
   都是数组形式
   0 表示上一次的
   1 表示这一次的
   */
   public void printLog(int[] state, int[] action,double reward,double R[], double Q[] ){
       //打印训练日志
       System.out.println("第 "+this.learningTime+" 轮学习");
       System.out.println("step1:更新");
       System.out.println("更新前的状态");
       System.out.println("lastState:"+ state[0]+"\tlastAction"+action[0]+"\tlastR"+R[0]+"\tlastQ"+Q[0]);
       this.QChangeRate = Math.abs(Q[1]-Q[0])/Math.abs(Q[0]);
       this.AllQChangeRate += this.QChangeRate;
       double averageQ = AllQChangeRate/this.learningTime;
      
       this.RChangeRate =  Math.abs(R[1]-R[0])/Math.abs(R[0]);
       this.AllRChangedRate+= this.RChangeRate;
        double averageR= AllRChangedRate/learningTime;
       System.out.println("更新Q值和R值的reward值为："+reward+"\tlastState，lastAction的Q值和R值更新为:Q  "+Q[1]+"\tR："+R[1]);
       System.out.println("单次Q矩阵变化率为: "+this.QChangeRate+"\tQ矩阵的平均变化率为："+averageQ 
       +"\t单次R矩阵变化率为："+this.RChangeRate+"\tR矩阵平均变化率为："+averageR);
       System.out.println("step2:决策");
       System.out.println("当前的State为："+state[1]+"做出的决策为："+action[1]+"对应的Q值为"+QMatrix[action[1]][state[1]]);
       System.out.println("Qlearning 结束");
   }
   
    //测试主函数
   public static void main(String[] agrs){
         Qlearning myQ= new Qlearning(10,380,0.5,0.3,".\\QMatrix_V2.txt",".\\rewardMatrix.txt");
         myQ.printRewardMatrix();
         //myQ.printRewardMatrix();
    }
}
