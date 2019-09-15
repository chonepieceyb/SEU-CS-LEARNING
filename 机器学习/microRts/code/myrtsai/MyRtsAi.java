/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


package myrtsai;

import ai.abstraction.AbstractAction;
import ai.abstraction.AbstractionLayerAI;
import ai.abstraction.Attack;
import ai.abstraction.Harvest;
import ai.abstraction.LightRush;
import ai.abstraction.pathfinding.AStarPathFinding;
import ai.abstraction.pathfinding.PathFinding;
import ai.core.AI;
import ai.core.AIWithComputationBudget;
import ai.core.ParameterSpecification;
import static java.lang.Integer.min;
import static java.lang.Math.abs;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import rts.GameState;
import rts.PhysicalGameState;
import rts.Player;
import rts.PlayerAction;
import rts.units.UnitTypeTable;
import rts.units.Unit;
import rts.units.UnitType;
import myrtsai.Qlearning;
/**
 *
 * @author msi-
 */
public class MyRtsAi extends AbstractionLayerAI{
    //内置类
    private class UnitsState{
       //属性,为了方便全部弄成public
        public Unit base = null;    //基地
        public Unit bArrackes = null;   //兵营
        //兵力数
        public int workerNum =0;
        public int lightNum=0;
        public int rangedNum =0;
        public int heavyNum = 0;
        public int unitNum =0; //包含兵营和基地的所有单位的数目
        public int[] averagePos = new int[2];   //单位的平均位置，除了基地外的所有单位横纵坐标的平均值
        //构造函数
        public UnitsState(){
               resetToZero();
        }
        //更新 参数是所有单位(我方单位还是地方单位要手动区分（包括基地和未分配的单位）
        void update( List<Unit> Units){
            resetToZero();
            int allNums =0;
            int allX =0;
            int allY=0;
            for(Unit u: Units){
                if(u!=null){
                    allNums++;
                    allX+=u.getX();
                    allY+=u.getY();
                    if(u.getType()==baseType){
                        base= u;
                    }else if(u.getType()==barracksType){
                        bArrackes=u;
                    }else if(u.getType() == workerType){
                        workerNum++;
                    }else if(u.getType() == lightType){
                        lightNum++;
                    }else if(u.getType()==rangedType){
                        rangedNum++;
                    }
                    else if(u.getType()== heavyType){
                        heavyNum++;
                    }
                 }
            }
            averagePos[0] = (int)allX/allNums;
            averagePos[1]= (int)allY/allNums;
            unitNum = allNums;
        }
        public void resetToZero(){
            base = null; 
            bArrackes = null;
            workerNum =0;
            lightNum=0;
            rangedNum =0;
            heavyNum = 0;
            unitNum =0;
            averagePos[0]=-1;
            averagePos[1]=-1;
        }
    }
    //内置类 训练版本,以及和Qlearning有关的参数
    private class QTrainInformation{
        public int version=2 ; //训练版本,目前有 0 8*8左上 1 8*8 右下 2 16*16左上  3 16*16右下,目前有 0 8*8左上 1 8*8 右下 2 16*16左上  3 16*16右下
        public double alpha= 0.4;
        public double alphaR = 0.4;
        public double Gamma = 0.5;
        public String QMatrixFileName= null;
        public String rewardMatrixFileName = null;
        public int actionNum=8;
        public int stateNum=3600;
        public int timeStep=550;
        public int writeStep =5;  //writeStep次训练写一次数据;
        public QTrainInformation(int version,double alpha,double alphaR, double Gamma, int actions, int states, int timeSteps,int writeStep){   
            setTrainParameter(alpha,alphaR, Gamma);
            setMatrixSize( actions,states);
            setTimeStep(timeStep);
            setWriteStep(writeStep);
            QMatrixFileName = "FinalQMatrix_V" + Integer.toString(version)+".txt";
            rewardMatrixFileName = "FinalrewardMatrix_V" + Integer.toString(version)+".txt";
            
        }
        public QTrainInformation(int version){
            //默认值
            setTrainParameter(0.4,0.4, 0.5);
            setMatrixSize( 8,3600);
            setTimeStep(550);
            QMatrixFileName = "FinalQMatrix_V" + Integer.toString(version)+".txt";
            rewardMatrixFileName = "FinalRewardMatrix_V" + Integer.toString(version)+".txt";
        }
        //方法,设定能够运行时改变的训练参数
        public void setTrainParameter(double a, double a2,double r){
            alpha =a;
            alphaR =a2;
            Gamma =r;
        }
        public void setMatrixSize( int actions, int states){
             actionNum = actions;
             stateNum = states;
        }
        public void setTimeStep(int step){
            timeStep = step;
        }
        public void setWriteStep(int step){
            writeStep = step;
        }
    }
    
    //内置类，上一次的学习状态
    private class LastLearningState{
          public int lastAction;        //上一次的action值
          public int lastState;         //上一次的state值
          public int lastSituation;      //上一次的战场局势
          public int lastEnermyA_D;      //上一次敌军的攻守状态
          public int lastOurA_D    ;      //上一次我军的攻守状态
          public int lastEnermyMajor;    //上一次敌军的主力兵种
          public int lastOurMajor;      //上一次我军的主力兵种
          public int lastCombatLevel=0; //上一个决策状态的等级，初始化为0
          public int lastTime=0;      //上一次决策的时间
          //构造函数
          public LastLearningState(){
              lastTime=0;
              lastCombatLevel=0;
          }
          //更新函数
          public void update(int args[])throws ArrayIndexOutOfBoundsException{
              try{
                  lastAction = args[0];
                  lastState = args[1];
                  lastSituation = args[2];
                  lastEnermyA_D = args[3];
                  lastOurA_D= args[4];
                  lastEnermyMajor = args[5];
                  lastOurMajor= args[6];
                  lastCombatLevel = args[7];
                  lastTime=args[8];
              }catch(Exception e){
                  throw new ArrayIndexOutOfBoundsException();
              }
          }
    }
     
    //AI版本，根据不同的地图大小以及不同的出生点位置选择不同的版本,目前有 0 8*8左上 1 8*8 右下 2 16*16左上  3 16*16右下,目前有 0 8*8左上 1 8*8 右下 2 16*16左上  3 16*16右下
     int version=2;  
     UnitTypeTable m_utt = null;
     UnitType workerType;
     UnitType baseType;
     UnitType barracksType;
     UnitType lightType;
     UnitType heavyType;
     UnitType rangedType;
     int lastRealTime=0;   
     int maxBuildWorkersNum=1;
     int maxHarvestWorkersNum=2; //最多有两个农民用于采矿
     int leastWorkersNum =3;    //最少worker的数目
     int maxOffendWorkersNum=6; //rush农民数目 -1表示无限制
     int maxHeavyNum=-1; // 重甲兵的最大数目
     int maxLightNum=-1;  //轻甲兵的最大数目
     int maxRangedNum=-1; //远程兵的最大数目
     List<Unit> harvestWorkers = new ArrayList<>();
     List<Unit> buildWorkers = new ArrayList<>();
    // Unit my_Base = null;
    // Unit my_Barracks = null;
     //保存的上一次的单位状态
     UnitsState ourUnitsState = new UnitsState();   //我方的
     UnitsState enermyUnitsState = new UnitsState();   //地方的
     //基地的坐标
     int baseX;
     int baseY;
     //一些矩阵
     int m_battleWeight[][] ={    //战斗权系数矩阵,(单兵战斗力对比一致性矩阵)
        {1 ,-3,-5,-4},{3 ,1, 2, -2},{ 5 ,-2, 1, 2},{4 ,2, -2 ,1}};
     int m_AD_weight_V1[][]={      //我方在左上角的时候..
         { 4,2},{2,1}
     };
     int m_AD_weight_V2[][]={      //我方在右下角的时候..
         { 1,2},{2,4}
     };
     //权衡当前reward和reward矩阵的因子，reward = rewardNow* rewardNowWeight+(1-rewardNowWeight)*R[][]
     double rewardNowWeight = 0.5;
    //和getState有关的数组
    // 0-50： 大劣势-大优势
   // int offsetSituation[] = {0,10,20,30,40};
    int offsetSituation[] = new int[9];
    // 0 防守 5 进攻
    int offsetEnermyD_A[]={0,200};
    int offsetOurD_A[]={0,100} ;  
    // 0-4 worker light ranged hearv 混合
    //int offsetMajor[]={0,1,2,3,4};
    int offsetEnermyMajor[]={0,10,20,30,40,50,60,70,80,90};
    int offsetOurMajor[]={0,1,2,3,4,5,6,7,8,9};
    //和action 有关的数组
    int actionA_D[]={4,4,4,4,0,0,0,0};
    String actionMajor[]={"Worker","Light","Ranged","Light","Worker","Light","Ranged","Heavy"};
    
    //和Qlearning 有关的参数 ,Qlearning 在构造函数中构造，而Information 在getAction中生成
    Qlearning myQlearning = null;
    //训练次数，用来控制是否向3文件中写数据
    int trainTime=0;
    QTrainInformation trainInformation = null;
    
    //过去的状态
    LastLearningState lastState = new LastLearningState();

    
    public MyRtsAi(UnitTypeTable a_utt) {
       this(a_utt, new AStarPathFinding());
    }
    public MyRtsAi(UnitTypeTable a_utt,PathFinding a_pf) {
        super(a_pf);
        reset(a_utt);
    }
    
    public AI clone() {
        return new MyRtsAi(m_utt,pf);
    }
    public void reset() {
          super.reset();
     }
    public void reset(UnitTypeTable a_utt) {
     
        m_utt=a_utt;
        workerType = m_utt.getUnitType("Worker");
        baseType = m_utt.getUnitType("Base");
        barracksType = m_utt.getUnitType("Barracks");
        lightType = m_utt.getUnitType("Light");
        heavyType =m_utt.getUnitType("Heavy");
        rangedType=m_utt.getUnitType("Ranged");
        for(int i=0;i<9;i++){
            offsetSituation[i]=i*400;
        }

    }

    public PlayerAction getAction(int player, GameState gs) {
        //变量的声明
        PhysicalGameState pgs = gs.getPhysicalGameState();
        Player p = gs.getPlayer(player);
        //敌方的ID
        List<Unit> warriorUnits = new ArrayList<>();
        List<Unit> enermyUnits = new ArrayList<>();
        List<Unit> enermyNormalUnits = new ArrayList<>();
        List<Unit> ourNormalUnits = new ArrayList<>();  //用于评估的我方单位
        List<Unit> ourUnits = new ArrayList<>();
        Unit my_Base=ourUnitsState.base=null;
        Unit my_Barracks = ourUnitsState.bArrackes;
        Unit enermy_Base = enermyUnitsState.base=null;
        Unit enermy_Barracks=enermyUnitsState.bArrackes=null;
        int lastTrainTime=lastState.lastTime;
        int action=lastState.lastAction;
        int state = lastState.lastState;
        int situation = lastState.lastSituation;
        int enermyA_D = lastState.lastEnermyA_D;
        int ourA_D = lastState.lastOurA_D;
        int enermyMajor = lastState.lastEnermyMajor;
        int ourMajor = lastState.lastOurMajor;
        int combatLevel = lastState.lastCombatLevel;
        int workersNum =0;
        int bX;   //兵营坐标
        int bY;
        //基地坐标
        boolean isTrain = false;  //本轮是否学习了
        if(player==0){
            bX=-1;
            bY=5;
            baseX=4;
            baseY=5;
        }else{
            bX=12;
            bY=16;
             baseX=11;
            baseY=13;
        }
        //创建Qlearning 
        if(gs.getTime()==0){
        createQlearning(pgs,player);
        }
        //获取战场的信息
        if(my_Base!=null &&my_Base.getHitPoints()<=0){
            my_Base = null;
        }
        if( my_Barracks  !=null && my_Barracks .getHitPoints()<=0){
            my_Barracks  = null;
        }
        
        int harvestNum=0;//
        //统计当前harvestWorkers数组里实际能工作的农民数
        for(Unit u : harvestWorkers){
            if(u!=null && u.getHitPoints()>0){
                harvestNum++;
            }
        }
     
       int buildWorkersNum = 0 ;
       boolean isBuild ;
       if(gs.getTime()>=50){
           isBuild = true;}
       else{
           isBuild=false;
       }
         if(my_Barracks!=null){
            isBuild = false;
            buildWorkers.clear();
        }
      //统计农民的数目，农民数目至少为3个
        //统计buildWorkers数据
        for(Unit u :buildWorkers){
            if(u!=null && u.getHitPoints()>0){
                buildWorkersNum++;
            }
        }
     
        //对战场所有单位进行分类
        for(Unit u: pgs.getUnits()){
            if(u!=null ){
                  if(u.getPlayer()==player){
                      if(u.getType() == baseType){   // 基地
                          my_Base = u;
                      }else if(u.getType()== barracksType){   //兵营
                          my_Barracks = u; 
                      }else{    //非基地和非兵营单位
                          ourNormalUnits.add(u);
                          if(gs.getActionAssignment(u)==null ) { //非分配工作的单位
                              if(u.getType() == workerType){
                                   workersNum++;
                                   if(!harvestWorkers.contains(u) && !buildWorkers.contains(u)){
                                   //优先build
                                        if( isBuild && my_Barracks==null && buildWorkersNum<maxBuildWorkersNum){
                                             buildWorkers.add(u);
                                              buildWorkersNum++;
                                        }else if(harvestNum< maxHarvestWorkersNum){
                                              harvestWorkers.add(u);
                                              harvestNum++;
                                        }else{
                                                warriorUnits.add(u);
                                        }
                                   }
                              }else if(u.getType().canAttack){     //可作战单位
                                      warriorUnits.add(u);
                               }
                          }
                      }
                  }else if(u.getPlayer()!= player){   //敌方的
                      if(u.getType() == baseType){
                           enermy_Base =u ;
                       }else if(u.getType()==barracksType){
                            enermy_Barracks= u;
                       }else if(u.getType().canAttack){
                           enermyNormalUnits.add(u);
                       }
                  }
            }
                      
         }

        enermyUnits.add(enermy_Barracks);
        enermyUnits.add(enermy_Base);
        enermyUnits.addAll(enermyNormalUnits);
        ourUnits.add(my_Barracks);
        ourUnits.add(my_Base);
        ourUnits.addAll(ourNormalUnits);
        int battleState[]=this.evaluateState(my_Base,ourNormalUnits, enermy_Base, enermyNormalUnits, 0.4f ,2);
        int enermyMajorUnitType[] = this.evaluateEnermyMajorUnit(pgs, p, 6, 3);
        int ourMajorUnitType[]= this.evaluateOurMajorUnits(pgs, p, 6, 3);
        enermyA_D=this.evaluate_AD_TacticsOfEnermy(pgs, p,1.2f );
        ourA_D=this.evalueate_AD_TacticsOfOur(pgs, p,1.2f );
        situation = battleState[0];
        //开始Q-learning 
        //获取majorUnitType
        enermyMajor = getMajorType(enermyMajorUnitType);
        ourMajor = getMajorType(ourMajorUnitType);
        //获取state
        state = getState(situation ,enermyA_D,ourA_D, enermyMajor,ourMajor);
        //开局设一个单独的状态

        if(gs.getTime()==501||gs.getTime()-lastTrainTime>=trainInformation.timeStep){
             lastTrainTime = gs.getTime();
            if(gs.getTime()>=500){

               System.out.println("进入训练和决策模块当前时间为:"+lastTrainTime);
                 System.out.println("打印决策前的训练信息：");
 
                System.out.println("局势等级为："+situation);
                 this.printTrainInformation();
                 //获取reward
                 UnitsState ourUnitsStateNow = new UnitsState();
                  UnitsState enermyUnitsStateNow = new UnitsState();
                  ourUnitsStateNow.update(ourUnits);
                  enermyUnitsStateNow .update(enermyUnits);
                 int reward;
                if(gs.getTime()>=510){
                    reward = (int)(this.calReward(pgs, enermyMajor, this.lastState.lastAction, situation,  ourUnitsStateNow,enermyUnitsStateNow,enermyA_D)*this.rewardNowWeight +(1-this.rewardNowWeight)*this.myQlearning.getRewardByR());
                }else{
                    reward = (int)((battleState[0]-this.lastState.lastCombatLevel)*10*this.rewardNowWeight);
                }
                /*
                if(battleState[1]!=-1000){
                     action=myQlearning.learningQ(state,battleState[1]-combatValue, true,false,true);
                }else{
                     action=myQlearning.learningQ(state,battleState[1], true,false,true);
                }*/
                isTrain=true;
                //两个null 是因为游戏快结束了
                if(trainTime>this.trainInformation.writeStep || my_Base==null || enermy_Base==null){
                    trainTime=0;
                    action=myQlearning.learningQR(state,reward, true,true,true);
                }else{
                      trainTime++;
                     action=myQlearning.learningQR(state,reward,false,false,true);
                }
            }
            //将当前战斗力存储下来
            combatLevel=battleState[0];
        }else if( gs.getTime()<=500){
            this.workersBehavior(harvestWorkers,buildWorkers, p, pgs,isBuild,1,bX,bY);
            if(enermy_Barracks!=null){
               // System.out.println("我方有兵营，训练light");
                   if(player==0){
                       if(gs.getTime()<=400)
                       action=5;
                       else{
                           action=1;
                       }
                   }else{
                    action=5;
                   }
            }else {
          //  System.out.println("敌方没有兵营，建造worker");
             action=0;
            }
        }
        //获取生产的兵种 和相应的攻防
        String ourMajorTatics=actionMajor[action];
        int ourA_DTatics=this.actionA_D[action];
        
        if(gs.getTime()>=150 ){
             this.baseBehavior(my_Base, p, gs, 3,0);
        }else{
             this.baseBehavior(my_Base, p, gs, 4,2);   
        }
        // 使用战略
       if(gs.getTime()>=150){
            if(ourMajorTatics!="Worker" ){
                 this.workersBehavior(harvestWorkers,buildWorkers, p, pgs, isBuild,1,bX,bY);
                this.rushTactics(gs, player, ourMajorTatics, my_Barracks, warriorUnits, enermyUnits, 2,ourA_DTatics);
            }else{
                 this.workersBehavior(harvestWorkers,buildWorkers, p, pgs, isBuild,1,bX,bY);
                 this.rushTactics(gs, player, ourMajorTatics, my_Base, warriorUnits, enermyUnits, 2,ourA_DTatics);
            }
       }
       
       //只有在训练的时候才会更新信息
       if(isTrain){
            //更新信息
             int args[]={        
             action,
             state ,
             situation,
             enermyA_D ,
             ourA_D,
             enermyMajor ,
             ourMajor,
             combatLevel,
             lastTrainTime,
             };
             try{
                 lastState.update(args);
             }catch(Exception e){
                 System.out.println("更新参数时数组越界");
             }
             ourUnitsState.update(ourUnits);
             enermyUnitsState.update(enermyUnits);
             //根据更新后的信息计算新的timeStep：
             this.trainInformation.setTimeStep(this.calTimeStep(pgs, 100, action,enermyA_D));
             System.out.println("打印战场信息");
            this.printGameState();
             System.out.println("打印决策后的训练信息");
           this.printTrainInformation();
       }
       /*
        //辅助信息
        switch(majorUnitType[0]){
            case 0:  System.out.println("以Worker为主");break;
            case 1:    System.out.println("以Light为主");break;
            case 2:   System.out.println("以Ranged为主");break;
            case 3:    System.out.println("以Heavy为主");break;
            case 4:    System.out.println("混合兵种");break;
            default:  System.out.println("判断主要兵种出错");
        }
        switch(enermyA_D){
            case 1:  System.out.println("敌方进攻");break;
            case 0:  System.out.println("敌方防守");break;
            default:  System.out.println("判断攻守失败");
        }
        //System.out.println("###");
        //System.out.println(enermyUnits.size());
        //农民建筑和收获
     
        
        switch(battleState[0]){
            case 0: System.out.println("我方大劣势");break;
            case 1: System.out.println("我方劣势");break;
            case 2: System.out.println("局势平衡");break;
            case 3: System.out.println("我方优势");break;
            case 4: System.out.println("我方大优势");break;
            default: System.out.println("评估出错");
        }
       */
         //  System.out.println("getActionOver\n");
        return translateActions(player, gs);
       
    }
    //打印训练信息
    private void printTrainInformation(){
        System.out.println("训练信息：");
        System.out.println("上一次的训练的时间为："+this.lastState.lastTime);
        System.out.println("timeStep为"+this.trainInformation.timeStep);
    }
    /*
    将战场状态打印出来的函数
    */
    public void printGameState(){
        System.out.println("敌方的状态");
        //打印 威胁等级，攻防，和主要兵种
        int level= this.lastState.lastCombatLevel;
        System.out.println("局势等级:"+level);
        int enermyAD=this.lastState.lastEnermyA_D;
        if(enermyAD==0){
            System.out.println("敌方防守");
        }else if(enermyAD==1){
            System.out.println("敌方进攻");
        }else{
            System.out.println("攻防判断错误");
        }
        int enermyMajor = this.lastState.lastEnermyMajor;
        switch(enermyMajor){
            case 0: System.out.println("敌方主要兵种为Worker");break;
            case 1: System.out.println("敌方主要兵种为Light");break;
            case 2: System.out.println("敌方主要兵种为Ranged");break;
            case 3: System.out.println("敌方主要兵种为Heavy");break;
            case 4: System.out.println("敌方主要兵种为Worker+Light");break;
            case 5: System.out.println("敌方主要兵种为Worker+Ranged");break;
            case 6: System.out.println("敌方主要兵种为Worker+Heavy");break;
            case 7: System.out.println("敌方主要兵种为Light+Ranged");break;
            case 8: System.out.println("敌方主要兵种为Light+Heavy");break;
            case 9: System.out.println("敌方主要兵种为Heavy+Ranged");break;
            default: System.out.println("敌方主要兵种判断失败");break;
        }
        System.out.println("敌方的平均位置:"+"["+this.enermyUnitsState.averagePos[0]+","+this.enermyUnitsState.averagePos[1]+"]");
        int[] enermyUnit = {this.enermyUnitsState.workerNum,this.enermyUnitsState.lightNum,this.enermyUnitsState.rangedNum,this.enermyUnitsState.heavyNum };
        System.out.println("敌方的兵种数目"+enermyUnit[0]+" , "+enermyUnit[1]+" , "+enermyUnit[2]+" , "+enermyUnit[3]+" , ");
        System.out.println("\n我方的战场信息:");
        int ourAD=this.lastState.lastOurA_D;
        if( ourAD==0){
            System.out.println("我方防守");
        }else if( ourAD==1){
            System.out.println("我方进攻");
        }else{
            System.out.println("攻防判断错误");
        }
        int ourMajor = this.lastState.lastOurMajor;
        switch(ourMajor){
            case 0: System.out.println("我方主要兵种为Worker");break;
            case 1: System.out.println("我方主要兵种为Light");break;
            case 2: System.out.println("我方主要兵种为Ranged");break;
            case 3: System.out.println("我方主要兵种为Heavy");break;
            case 4: System.out.println("我方主要兵种为Worker+Light");break;
            case 5: System.out.println("我方主要兵种为Worker+Ranged");break;
            case 6: System.out.println("我方主要兵种为Worker+Heavy");break;
            case 7: System.out.println("我方主要兵种为Light+Ranged");break;
            case 8: System.out.println("我方主要兵种为Light+Heavy");break;
            case 9: System.out.println("我方主要兵种为Heavy+Ranged");break;
            default: System.out.println("我方主要兵种判断失败");break;
        }
        System.out.println("我方的平均位置"+this.ourUnitsState.averagePos[0]+","+this.ourUnitsState.averagePos[1]+"]");
        int[] ourUnit = {this.ourUnitsState.workerNum,this.ourUnitsState.lightNum,this.ourUnitsState.rangedNum,this.ourUnitsState.heavyNum };
       System.out.println("我方的兵种数目"+ourUnit[0]+" , "+ourUnit[1]+" , "+ourUnit[2]+" , "+ourUnit[3]+" , ");
    }
    /*
       获取下一步的timeStep的函数：
       这个函数根据不同的状态获取下一步学习时的不同的timeStep
           1 交战的时候 ： tiemStep = 建造一个兵的时间 + 兵移动到战场中部的时间
           2  非交战的时候，timeStep = 固定的值 
    input: fixTimeStep:固定的timeStep
    output:返回timeStep
    */
    private int calTimeStep(PhysicalGameState pgs, int fixTimeStep,int action,int enermyA_D ){
        int maxD = pgs.getHeight()+pgs.getWidth();   //战场的总长度， 宽+高
        //敌我双方的单位平均距离之差
        int[] ourPos = this.ourUnitsState.averagePos;
        int[] enermyPos = this.enermyUnitsState.averagePos;
        int distance = Math.abs(ourPos[0]- enermyPos[0])+Math.abs(ourPos[1]- enermyPos[1]);
        if(distance>(maxD/3)&&enermyA_D==0){
            return fixTimeStep;
        }
        else{ //如果是交战状态,或者地方防守
            int timeStep=fixTimeStep;
            UnitType buildType = null;
            switch(action%4){
                case 0: buildType = workerType; break;
                case 1: buildType = lightType; break;
                case 2: buildType = rangedType; break;
                case 3: buildType = heavyType; break;
                default: buildType =null;
            }
            if(buildType!=null){
                //暂定
                Random r= new Random();
                //这里的是 生产时间+移动时间 +随机的攻击时间 （随机的攻击时间是 随机0-5个attackTime)
                timeStep = ( buildType.produceTime + (int)distance/buildType.moveTime + (0+r.nextInt()%6)*buildType.attackTime);
            }else{
                timeStep = fixTimeStep;
            }
            return timeStep;
        }
        
    }
    //计算reward的函数
    private int calReward(PhysicalGameState pgs,int enermyMajor, int action,int level,UnitsState ourState,UnitsState enermyState,int A_DNow){
         int maxD = pgs.getHeight()+pgs.getWidth();   //战场的总长度， 宽+高
        //敌我双方的单位平均距离之差
        int ourLastPos[] = this.ourUnitsState.averagePos;
        int enermyLastPos[] = this.enermyUnitsState.averagePos;
         int ourNowPos[] = ourState.averagePos;
        int enermyNowPos[] = enermyState.averagePos;
        int worker[] ={0,-90,-90,-90,-90,-90,-90,-90,-90,-90};
        int light[]={50,90,0,90,90,0,90,90,90,90};
        int ranged[]={100,0,90,80,0,90,90,90,0,90};
        int hearvy[]={-40,-40,-40,-40,-40,-40,-40,-40,-40,-40};
        int battle[][] ={{0,-90,-90,-90,-90,-90,-90,-90,-90,-90},{90,90,0,90,90,0,90,90,90,90},{100,0,90,90,0,90,90,90,0,90},{-10,-10,-10,-10,-10,-10,-10,-10,-10,-10}};
        int i,j;
        for(i =0;i<4;i++){
            for(j=0;j<10;j++){
                battle[i][j]=(int)battle[i][j]/6;
            }
        }
        int distanceLast = Math.abs(ourLastPos[0]- enermyLastPos[0])+Math.abs(ourLastPos[1]- enermyLastPos[1]);
        int distanceNow = Math.abs(ourNowPos[0]- enermyNowPos[0])+Math.abs(ourNowPos[1]- enermyNowPos[1]);
        if(distanceLast>(maxD/3)&& distanceNow>(maxD/3) &&A_DNow==0) { //如果前后两个过程都是防守状态的话,并且当前敌方的AI处于防守
            System.out.println("采用防守的reward");
           return battle[(int)(action%4)][enermyMajor];
        }else{
             System.out.println("采用攻击的reward");
             return (int)((level-this.lastState.lastCombatLevel)*10*this.rewardNowWeight +(1-this.rewardNowWeight)*this.myQlearning.getRewardByR()); 
            
        }
    }
    //一些游戏过程的函数
    private void createQlearning(PhysicalGameState pgs, int player){
        int sizeOffset[] ={0,2,4,6};
        int playerOffset[]={0,1};
        int sizeIndex= (pgs.getWidth() /8)-1;
        int playerIndex = player;
        version = sizeOffset[sizeIndex]+ playerOffset[playerIndex];
        trainInformation = new QTrainInformation(version);
        int actionNum = trainInformation.actionNum;
        int stateNum = trainInformation.stateNum;
        String QMatrixFileName = trainInformation.QMatrixFileName;
        String rewardMatrixFileName = trainInformation.rewardMatrixFileName;
        double alpha = trainInformation.alpha;
        double r =trainInformation.Gamma;
        double alohaR = trainInformation.alphaR;
        myQlearning=new Qlearning(actionNum,stateNum,alpha,r,alohaR,".\\"+QMatrixFileName,".\\"+rewardMatrixFileName);

    }
    private int getMajorType(int[] majorUnitType){
        int majorUnit=-1;
        if(majorUnitType[0]==4){
            majorUnit=3+majorUnitType[1];
        }else{
            majorUnit=majorUnitType[0];
        }
        return majorUnit;
    }
    private int  getState(int situation, int enermyA_D, int ourA_D,int enermyMajor,int ourMajor){
        int state=0;
        if( enermyMajor==-1 || situation==-1||  enermyA_D==-1 || ourA_D==-1 || ourMajor==-1){
            state=1800;
        }else{
           state =  this.offsetSituation[situation] + this.offsetEnermyD_A[ enermyA_D] +this.offsetOurD_A[ourA_D]+this.offsetEnermyMajor[enermyMajor]+this.offsetOurMajor[ourMajor];
        }
        return state;
    }
    /*
    判断对面是攻击还是防守的函数
    返回值 0：敌方防守 1：敌方进攻 : -1不正常
    input: gs 同之前，
           p: 我方的player！
    NumThrehold,决定是攻还是守的阈值 如果 结果<NumThrehold 结果是防守， 结果》=NumThrehold 结果是攻击
    */
    public int evaluate_AD_TacticsOfEnermy(PhysicalGameState pgs, Player p, float NumThrehold ){
      int width = pgs.getWidth();
      int height = pgs.getHeight();
      int center[] = {width/2,height/2};
      int AD_weight[][] = new int[2][2];
      switch(p.getID()){              // ID是 0 基地在左上方 1基地在右下方
          case 0: AD_weight = m_AD_weight_V1; break;//左上方的时候选择V1矩阵 
          case 1: AD_weight=m_AD_weight_V2;break;
          default: return -1;
      }
      int i=0;
      int j=0;
      //将整个战场分成4块，统计敌方的兵力在4块所占的比例，然后* AD_weight 根据最后的结果与阈值比较得出攻守结论
      float percentOfUnits[][] = new float[2][2];  //初始化
      int UnitsNum=0;
      for(i=0;i<2;i++){
          for(j=0;j<2;j++){
              percentOfUnits[i][j] =0 ;
          }
      }
      for(Unit u :pgs.getUnits()){
            if(u!=null && u.getPlayer()>=0 && u.getPlayer()!=p.getID() && u.getType().canAttack){
               
                int tempX=u.getX(); int tempY=u.getY();   //获取坐标
                if(tempX>=0 && tempX<center[0] && tempY>=0 && tempY<center[1]){   //左上
                    percentOfUnits[0][0]++; 
                    UnitsNum++;  //总数目+1
                 }else if (tempX>=center[0] && tempX<=width && tempY>=0 && tempY<center[1]) {   //右上
                    percentOfUnits[0][1]++;
                     UnitsNum++;  //总数目+1
                 }else if (tempX>=0 && tempX<center[0] && tempY>=center[1] && tempY<=height){   //左下
                    percentOfUnits[1][0]++;
                     UnitsNum++;  //总数目+1
                 }else if (tempX>=center[0] && tempX<=width && tempY>=center[1] && tempY<=height){  //右下
                     percentOfUnits[1][1]++;
                     UnitsNum++;
                 }
            }
      }
      //计算概率
      if(UnitsNum==0){
          return -1;
      }
       for(i=0;i<2;i++){
          for(j=0;j<2;j++){
              percentOfUnits[i][j] /= UnitsNum ;
          }
      }
       //和权矩阵相乘
       float AD_Value =0;
        for(i=0;i<2;i++){
          for(j=0;j<2;j++){
             AD_Value+= percentOfUnits[i][j] * AD_weight[i][j] ;
          }
      }
       if(AD_Value>=0 && AD_Value< NumThrehold){
           return 0;   //防守
       }else if(AD_Value >=NumThrehold){
           return 1;   //进攻
       }else{
           return -1;  //出错
       }
    }
    
    
    /*判断我方是攻击还是防守的函数
        返回值 0：敌方防守 1：敌方进攻 : -1不正常
    input: gs 同之前，
           p: 我方的Player！
    NumThrehold,决定是攻还是守的阈值 如果 结果<NumThrehold 结果是防守， 结果》=NumThrehold 结果是攻击
    */
    public int evalueate_AD_TacticsOfOur(PhysicalGameState pgs, Player p, float NumThrehold ){
        //获取敌方方的player
        Player enermy=null;
        for(Player player: pgs.getPlayers()){
            if(player.getID()!= p.getID()){
                enermy = player;
                break;
            }
        }
        return this.evaluate_AD_TacticsOfEnermy(pgs, enermy, NumThrehold);
    }
    /*
    判断对面的主力兵种的函数，（主要是Light,Ranged,Heavy,Worker,混合兵种（没有一个兵种的数目占绝对优势的时候）) 其中 light heavy ranged的数量比例都是 1：1 ,而worker不然
    参数说明： Player p, 我方
               PhysicalGameState  pgs 战场的信息
               workerValue:将农民折换成 light heavy ranged  折换后的Num= 原本Num/workerValue
               NumThreshold: 确定是否有主力兵种的阈值，如果 maxNum-second<NumThreshoud(不包括NumThreshoud) 认为这时候对面是混合兵种。
    output: 一个int数组，int[0] 0:主力是worker 1主力是light 2主力是ranged 3主力是 heavy 4 混合兵种  int[1]:如果不是混合兵种的话，该值为0，否则该值为混合的类型 1： WL 2: WR 3： WH 4：LR 5 LH 6 RH ,如果有任意一个值为-1的话说明返回值有问题
    */
    public int[] evaluateEnermyMajorUnit(PhysicalGameState pgs, Player p,int workerValue, int NumThreshold){
        //统计战场上敌方兵种的数目
        //分量 0 农民数目，1 light 2 ranged 3hearvy
       int MajorUnitType[]= new int[2];
       MajorUnitType[0]=-1;MajorUnitType[1]=-1;
       int UnitNum[]=new int[4];
       //初始化
       int i=0;
       for(i=0;i<4;i++){
           UnitNum[i]=0;
       }
       //数目最多的兵种和第二多的兵种 ，-1表示尚未统计，而 0表示农民 1:light 2:ranged 3:hearvt
       int largestUnitID=-1;
       int secondUnitID=-1;
       //统计数目
       for(Unit u : pgs.getUnits()){
          if(u!=null && u.getPlayer()>=0 && u.getPlayer()!=p.getID() && u.getType().canAttack){
              if(u.getType()==workerType){
                  UnitNum[0]++;
              }else if(u.getType()==lightType){
                  UnitNum[1]++;
              }else if(u.getType()==rangedType){
                  UnitNum[2]++;
              }else if(u.getType()==heavyType){
                  UnitNum[3]++;
              }
          }
       }
       //折换worker的数目
       UnitNum[0]/=workerValue;
       int maxNum=0;
       int secondNum=0;
       //数量小直接暴力统计了..
       for(i=0;i<4;i++){
           if(largestUnitID!=-1 && UnitNum[i]>maxNum){
               largestUnitID=i;
               maxNum=UnitNum[i];
           }else if(largestUnitID==-1){
               largestUnitID=i;
               maxNum=UnitNum[i];
           }
       }
       for(i=0;i<4;i++){
           if(i!=largestUnitID){
               if(secondUnitID!=-1 && UnitNum[i]>secondNum){
               secondUnitID=i;
               secondNum=UnitNum[i];
                }else if(secondUnitID==-1){
                    secondUnitID=i;
                    secondNum=UnitNum[i];
                }  
           }
       }
          
       //判断主力兵种
       //output: 一个int数组，int[0] 0:主力是worker 1主力是light 2主力是ranged 3主力是 heavy 4混合兵种  int[1]:如果不是混合兵种的话，该值为0，否则该值为混合的类型 1： WL 2: WR 3:WH  4：LR 5 LH 6 RH ,如果有任意一个值为-1的话说明返回值有问题
       if(largestUnitID==-1 || secondUnitID==-1){
            MajorUnitType[0]=-1;
           MajorUnitType[1]=-1;
           System.out.println("判断主力兵种出错1");
           return MajorUnitType;
       }
       if(secondNum==0 && maxNum!=0){
           MajorUnitType[0]=largestUnitID;
           MajorUnitType[1]=0;
       }
       else if(maxNum-secondNum >NumThreshold ){
           MajorUnitType[0]=largestUnitID;
           MajorUnitType[1]=0;
       }else{
          MajorUnitType[0]=4;
          int tempFlag = (largestUnitID+1)*(secondUnitID+1); //加以相乘，主要为了方便判断, 由上面largestUnitID!=secondUnitID
                switch(tempFlag){
                    case 2 :   MajorUnitType[1]=1;break;  //WL
                    case 3 :   MajorUnitType[1]=2;break;  //WR
                    case 4 :   MajorUnitType[1]=3;break;  //WH
                    case 6 :   MajorUnitType[1]=4;break;  //LR
                    case 8 :   MajorUnitType[1]=5;break;  //LH
                    case 12 :  MajorUnitType[1]=6;break;  //RH
                    default : MajorUnitType[1]=-1;
                }
          }
        return MajorUnitType;
    }
   /*
   判断我方的主力兵种的函数，（主要是Light,Ranged,Heavy,Worker,混合兵种（没有一个兵种的数目占绝对优势的时候）) 其中 light heavy ranged的数量比例都是 1：1 ,而worker不然
    参数说明： Player p, 我方
               PhysicalGameState  pgs 战场的信息
               workerValue:将农民折换成 light heavy ranged  折换后的Num= 原本Num/workerValue
               NumThreshold: 确定是否有主力兵种的阈值，如果 maxNum-second<NumThreshoud(不包括NumThreshoud) 认为这时候对面是混合兵种。
    output: 一个int数组，int[0] 0:主力是worker 1主力是light 2主力是ranged 3主力是 heavy 4 混合兵种  int[1]:如果不是混合兵种的话，该值为0，否则该值为混合的类型 1： WL 2: WR 3： WH 4：LR 5 LH 6 RH ,如果有任意一个值为-1的话说明返回值有问题
    */
    public int[] evaluateOurMajorUnits(PhysicalGameState pgs,Player p,int workerValue,int NumThreshold){
        //获取敌方方的player
        Player enermy=null;
        for(Player player: pgs.getPlayers()){
            if(player.getID()!= p.getID()){
                enermy = player;
                break;
            }
        }
        return this.evaluateEnermyMajorUnit(pgs,enermy, workerValue, NumThreshold);
    }
    /* 
    分析战场形势的函数：从两个方面进行评估（1 敌我双方各个单位数目的差值（一定考虑） 2 敌我双方单位和对方基地的距离的插值（可选择考虑的程度）暂时不考虑兵营
    output: 一个 int[0] 范围从 0 - 4  0:我方大劣势 1：我方劣势 2：双方均等 3：我方优势 4 我方大优势 , int[1]真实的战斗力
    input: gs同之前 , 
           ourUnits(我方单位）和enermyUnits(敌方单位）是评估的对象， 
           myBase 我方基地   enermyBase 敌方基地
           distanceLevel ： 敌我双方距离的影响因子，即是否将敌我双方距离对方基地的距离也纳入评估的范围  范围从 0 到 1 0是不考虑距离，1 考虑距离且程度最大
           scoreStep : 评价阈值的步长
    */
    public int[] evaluateState(Unit my_Base,List<Unit> ourUnits,Unit enermy_Base, List<Unit> enermyUnits,float distanceLevel, int scoreStep){
        /* 
        
        battleMatrix战斗矩阵 行、列（0:代表 worker, 1:light 2:range 3:heavy)
        battleMatrix[i][j] 表示 我方的i兵种战斗力之和 - 敌方的 j兵种战斗力之和
        单个兵种的战斗力公式 1+(maxd/d)*distanceLevel 注：这里没有考虑兵种的差异，而实考虑数目和距离，兵种的差异体现在之后还有一个 矩阵 maxd表示地图最大距离，而d 表示本兵种距离对方基地的距离
        */
        //输出
        int output[]={0,0};
        int battleWeight[][] = m_battleWeight;//战斗权系数矩阵,(单兵战斗力对比一致性矩阵)
        if(my_Base==null && enermy_Base!=null){    //我方没基地了 大劣势
            System.out.println("我方没基地了");
            output[0]=0;
            output[1]=-1000;
            return output;
        }
        if(enermy_Base == null && my_Base!=null){   //敌方没基地了 大优势
            System.out.println("敌方没基地了");
            output[0]=4;
            output[1]=1000;
            return output;
        }
        if(my_Base == null && enermy_Base == null){    //敌我双方都没有基地，不考虑距离因素
            System.out.println("都没基地了");
            distanceLevel=0;
        }
        float ourCombat[] = new float[4];  //我方战力
        float enermyCombat[]= new float[4]; //敌方战力
        //战力初始化
        int i,j;
        for(i=0;i<4;i++){
            ourCombat[i]=0;
            enermyCombat[i]=0;
        }
        int maxD;
        //获取地图最大距离
        if(distanceLevel==0){
            maxD=0;
        }else{
            maxD= Math.abs( my_Base.getX()- enermy_Base.getX())+ Math.abs( my_Base.getY()- enermy_Base.getY());
        }
        //开始统计我方战斗数组
        for(Unit u1: ourUnits){
             
           if(u1!=null && u1.getType().canAttack){  //如果不为空且能够进攻
                float combatValue=0;
                if(enermy_Base!=null){   //敌方基地存在才能计算距离
                       int d = Math.abs( u1.getX()- enermy_Base.getX())+ Math.abs(u1.getY()- enermy_Base.getY());
                       combatValue = maxD+(maxD/d)*distanceLevel;
                }else{
                    combatValue =maxD;
                }
                UnitType uType =u1.getType();
                if(uType == workerType){
                    ourCombat[0]+=combatValue;
                }else if(uType == lightType){
                    ourCombat[1]+=combatValue;
                }else if(uType== rangedType){
                    ourCombat[2]+=combatValue;
                }else if(uType == heavyType){
                    ourCombat[3]+=combatValue;
                }
           }
        }
       
        //统计敌方战斗数组
        for(Unit u2: enermyUnits){
               if(u2!=null && u2.getType().canAttack){  //如果不为空且能够进攻
                    float combatValue=0;
                    if(my_Base!=null){   //我方基地存在才能计算距离R
                           int d = Math.abs( u2.getX()- my_Base.getX())+ Math.abs(u2.getY()- my_Base.getY());
                           combatValue = maxD+(maxD/d)*distanceLevel;
                    }else{
                        combatValue =maxD ;
                    }
                    UnitType uType =u2.getType();
                    if(uType == workerType){
                        enermyCombat[0]+=combatValue;
                    }else if(uType == lightType){
                        enermyCombat[1]+=combatValue;
                    }else if(uType== rangedType){
                        enermyCombat[2]+=combatValue;
                    }else if(uType == heavyType){
                        enermyCombat[3]+=combatValue;
                    }
               }
            }
          //计算 myCombatAll
          float myCombatAll=0;
          int enermyNoZero=0;
          for(i=0;i<4;i++){
              if(enermyCombat[i]!=0){
                enermyNoZero++;
              }
          }   
          if(enermyNoZero==0){
              output[0]=4;
              output[1]=1000;
              return output;
          }
          for(i=0;i<4;i++){
              float myCombatI=0;
              if(ourCombat[i]!=0){
                for(j=0;j<4;j++){
                    if(enermyCombat[j]!=0){
                        if(battleWeight[i][j]>0){
                           myCombatI+=(ourCombat[i]*battleWeight[i][j]-enermyCombat[j]);
                        }else{
                             myCombatI+=(ourCombat[i]+enermyCombat[j]*battleWeight[i][j]);
                        }
                    }
                }
                myCombatAll+= myCombatI/ enermyNoZero;
              }
          }
         //更新output
         output[1]=(int)myCombatAll;
         scoreStep*=maxD;
         //评估威胁

         double   absMyCombatAll = Math.abs(myCombatAll);
         int level = 0;
         //等级为 0 - 4
         if( (int)absMyCombatAll/scoreStep<4){
             level = (int)absMyCombatAll/scoreStep;
         }else{
             level =4;
         }
         //output[0]: 0-18 
         if(myCombatAll>0){
             output[0]=4+level;
         }else{
             output[0]=4-level;
         }
         /*
         if(myCombatAll> -scoreStep && myCombatAll< scoreStep  ){
             output[0]=2;
            // return 2;
         }else if(myCombatAll>=scoreStep&& myCombatAll<3*scoreStep){
             output[0]=3;
           //  return 3;
         }else if(myCombatAll>=3*scoreStep){
             output[0]=4;
           //  return 4;
         }else if(myCombatAll<=-scoreStep&& myCombatAll> -3*scoreStep){
             output[0]=1;
           //  return 1;
         }else if(myCombatAll<=-3*scoreStep){
             output[0]=0;
           //  return 0;
         }else{
             System.out.println("评估出现问题,认为战力相同");
           //  return 2;
         }
          */
         return output;
    }

    /*
    gs 和 Player同之前
    input :
    rushType:进攻策略 ，有 worker rush, heavy rush , light rush 和 range rush
    Unit trainBuilding 用来训练的单位,如果是worker rush就选择 base ,如果是 非worker rush 就选择 兵营，如果不选择训练 就 null
    ourUnits:我方的目前可用的单位(不包括农民，目前的设想是，这些单位是用于进攻的单位）
    enermyUnits: 敌方的单位
    rushTarget: 进攻目标 1是进攻基地，2进攻非采矿单位
    rushLevel : 进攻程度 0：防守   1：少许进攻  2：半数进攻（选 0.5倍兵力进攻） 3：强势进攻（选0.75倍兵力进攻） 4：全力进攻（所有的兵力都进攻）
    */
    public void rushTactics(GameState gs, int player, String rushType,Unit trainBuilding,List<Unit>ourUnits, List<Unit> enermyUnits, int rushTarget, int rushLevel)
    {   
        PhysicalGameState pgs=gs.getPhysicalGameState();
        Player p=gs.getPlayer(player);
        List<Unit> warriorUnits = new ArrayList<>(); //主进攻单位
        List<Unit> defendUnits = new ArrayList<>(); //防御单位
        List<Unit> otherAttackUnits = new ArrayList<>(); //非主进攻单位
        int warriorNum=0;    //当前进攻数目
        int maxWarriorNum;  //最大进攻数目，由rushlevel决定
        if(rushLevel==0)
            maxWarriorNum=0;
        else
            maxWarriorNum=ourUnits.size();
        //根据rushType训练相应的单位,以及挑选相应的主进攻队伍,次进攻队伍,以及防御队伍
        for(Unit u:ourUnits){
           if(u.getType() == m_utt.getUnitType(rushType)){
                //有rushlevel决定，如果数目达到进攻上限，剩下的队伍转为防守
                if(warriorNum <maxWarriorNum){    
                    warriorUnits.add(u);
                    warriorNum++;
                 }
                else{
                     defendUnits.add(u);
                }
                
            }
            else{
                if(warriorNum<maxWarriorNum){
                    otherAttackUnits.add(u);
                    warriorNum++;
                }
                else{
                    defendUnits.add(u);
                }
            }
        }
         //训练相应的rush单位
         if(trainBuilding!=null){
             if(trainBuilding.getType()==baseType){
                 this.baseBehavior(trainBuilding, p, gs, 2,0);
             }else if(trainBuilding.getType()==barracksType){
                 this.barracksBehavior(trainBuilding, p, gs, rushType);
             }
         }
         //对敌方单位进行分类
         Unit enermyBase=null;
         List<Unit> e_NoBaseUnits=new ArrayList<>();
         for(Unit u: enermyUnits){
             if(u!=null){
                 if(u.getType()==m_utt.getUnitType("Base")){
                     enermyBase=u;
                 }
                 else {
                     e_NoBaseUnits.add(u);
                 }
             }
         }
         List<Unit> targetUnits= new ArrayList<>();
         if(rushTarget==1 && enermyBase!=null){
             targetUnits.add(enermyBase);
         }else if(rushTarget==2 && e_NoBaseUnits.size()>=3){
              // System.out.println("##");
              //System.out.println(e_NoBaseUnits.size());
              for(Unit target:e_NoBaseUnits){
                  targetUnits.add(target);
              }
         }else{
             targetUnits=enermyUnits;
         }
         
         //主进攻部队进攻
         for(Unit warrior:warriorUnits){
             attackBehavior(warrior,p,gs); 
         }
         //次进攻部队进攻
         for(Unit warrior:otherAttackUnits){
             attackBehavior(warrior,p,gs);
         }
         for(Unit warrior:defendUnits ){
             if(gs.getTime()<=2500){
                  defenceBehavior(warrior,p,gs);
             }else{
                  attackBehavior(warrior,p,gs);
             }
         }
    }

    /*
    intput : trainType : 1 根据maxharvestWorkersNum 训练用来收获的农民
                         2 根据maxOffendWorkersNum 训练用来防御的农民
                        3 根据leastWorkersNum 维持农民数量
                        4 任意数目，数目由另外一个参数给定，只有在trainType为4的时候才有效
    */
    public void baseBehavior(Unit u, Player p, GameState gs,int trainType,int trainNum) {
         //先统计目前战场上的农民的数目
        PhysicalGameState pgs=gs.getPhysicalGameState();
        int allWorkers=0;
        int harvestWorkers = 0; 
        int offendWorkers =0;
        for (Unit u2:selectUnitsAround(gs, p.getID(), "Worker", 0, 0, pgs.getWidth(), pgs.getHeight(), -1, false)) {
            //说明，这里我不知道怎么确定自己的农民现在正在干啥。
            if(u2!=null){
                AbstractAction aa = getAbstractAction(u2);
                if (aa instanceof Harvest) {
                      allWorkers++;
                    harvestWorkers++;
                }else if(aa instanceof Attack){
                      allWorkers++;
                    offendWorkers++;
                }else{
                    allWorkers++;
                }
            }
        }
        switch(trainType){
            case 1:        //训练用来收获的农民
                if(maxHarvestWorkersNum == -1 && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }else if(harvestWorkers<maxHarvestWorkersNum && p.getResources()>=workerType.cost){
                     train(u,workerType);
                }
                break;
            case 2:     //训练用来rush的农民
                if(maxOffendWorkersNum==-1 && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }else if(offendWorkers< maxOffendWorkersNum && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }
                break;
            case 3:
                /*
                if(maxHarvestWorkersNum == -1 && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }else if(harvestWorkers<maxHarvestWorkersNum && p.getResources()>=workerType.cost){
                     train(u,workerType);
                }
                if(maxOffendWorkersNum==-1 && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }else if(offendWorkers< maxOffendWorkersNum && p.getResources()>=workerType.cost){
                    train(u,workerType);
                }*/
                if(allWorkers<leastWorkersNum){
                    train(u,workerType);
                }
                break;
            case 4:
                if(allWorkers<trainNum){
                    train(u,workerType);
                }
                break;
            default:
                break;
                
        }
    }
     
    /*
     兵营的行为，参数说明：最后一个参数 String type (训练的类型）
     */
    public void barracksBehavior(Unit u, Player p, GameState gs, String type) {
        PhysicalGameState pgs=gs.getPhysicalGameState();
        if(type=="Light"){
            int Lights=0;
            for(Unit u2: selectUnitsAround(gs, p.getID(), "Light", 0, 0, pgs.getWidth(), pgs.getHeight(), -1, false) ){
                if(u2.getType().canAttack){
                    Lights++;
                }
            }
            if(maxLightNum == -1 && p.getResources()>=lightType.cost){
                    train(u,lightType);
             }else if( Lights<maxLightNum  && p.getResources()>=lightType.cost){
                     train(u,lightType);
             }
        }else if(type=="Heavy"){
            int Heavys=0;
            for(Unit u2: selectUnitsAround(gs, p.getID(), "Heavy", 0, 0, pgs.getWidth(), pgs.getHeight(), -1, false) ){
                if(u2.getType().canAttack){
                    Heavys++;
                }
            }
            if(maxLightNum == -1 && p.getResources()>=heavyType.cost){
                    train(u,heavyType);
             }else if( Heavys<maxLightNum  && p.getResources()>=heavyType.cost){
                     train(u,heavyType);
             }
         }else if(type=="Ranged"){
            int rangeds=0;
            for(Unit u2: selectUnitsAround(gs, p.getID(), "Ranged", 0, 0, pgs.getWidth(), pgs.getHeight(), -1, false) ){
                if(u2.getType().canAttack){
                    rangeds++;
                }
            }
            if(maxRangedNum == -1 && p.getResources()>=rangedType.cost){
                    train(u,rangedType);
             }else if( rangeds<maxRangedNum  && p.getResources()>=rangedType.cost){
                     train(u,rangedType);
             }
         }
    }
    
    /* 
    农民的行为,建筑+收获， 也就是说参数 workers应该是掉实现分开的用来收获的农民（加建筑）
    附加参数 ： isBuild 是否增加建筑命令，true建建筑 ,false 不建
    baseNum :我方允许的基地数目
    barracksNum :我方允许的兵营的数目
    barrack_x,barrack_y:兵营坐标
    input: 
    */
    public void workersBehavior(List<Unit>harvestWorkers,List<Unit> builderWorkers, Player p, PhysicalGameState pgs,boolean isBuild,int barracksNum,int barrack_x,int barrack_y) {
        int nbarracks = 0;

        int resourcesUsed = 0;
        List<Unit> freeWorkers = new LinkedList<Unit>();
        List<Unit> workers = new LinkedList<Unit>();
        freeWorkers.addAll(harvestWorkers);
        workers.addAll(builderWorkers);

        for (Unit u2 : pgs.getUnits()) {
            if (u2.getType() == barracksType
                    && u2.getPlayer() == p.getID()) {
                nbarracks++;
            }
        }

        List<Integer> reservedPositions = new LinkedList<Integer>();
     //    if(!isBuild){
       //      System.out.println("不允许建造兵营");
       //  }
        if(isBuild &&!workers.isEmpty()){
              if (nbarracks < barracksNum ) {
                // build a barracks:
                if (p.getResources() >= barracksType.cost + resourcesUsed ) {
                    Unit u = workers.remove(0);
                  //  move(u,barrack_x,barrack_y);
                    buildIfNotAlreadyBuilding(u,barracksType,barrack_x,barrack_y,reservedPositions,p,pgs);
                    resourcesUsed += barracksType.cost;
                }else{  //否则让建筑工人去采矿
                   // if(p.getResources() < barracksType.cost + resourcesUsed ){
                    //}
                    
                    for(Unit u: workers){
                        if(u!=null){
                            freeWorkers.add(u);
                        }
                    }
                }
            }
        }

        // harvest with all the free workers:
        for (Unit u : freeWorkers) {
            Unit closestBase = null;
            Unit closestResource = null;
            int closestDistance = 0;
            for (Unit u2 : pgs.getUnits()) {
                if (u2.getType().isResource) {
                    int d = Math.abs(u2.getX() - u.getX()) + Math.abs(u2.getY() - u.getY());
                    if (closestResource == null || d < closestDistance) {
                        closestResource = u2;
                        closestDistance = d;
                    }
                }
            }
            closestDistance = 0;
            for (Unit u2 : pgs.getUnits()) {
                if (u2.getType().isStockpile && u2.getPlayer()==p.getID()) {
                    int d = Math.abs(u2.getX() - u.getX()) + Math.abs(u2.getY() - u.getY());
                    if (closestBase == null || d < closestDistance) {
                        closestBase = u2;
                        closestDistance = d;
                    }
                }
            }
            if (closestResource != null && closestBase != null) {
                AbstractAction aa = getAbstractAction(u);
                if (aa instanceof Harvest) {
                    Harvest h_aa = (Harvest)aa;
                    if (h_aa.getTarget() != closestResource || h_aa.getBase()!=closestBase) harvest(u, closestResource, closestBase);
                } else {
                    harvest(u, closestResource, closestBase);
                }
            }
        }
    }
    //进攻
    public void attackBehavior(Unit u,Player p,GameState gs)
    {
        PhysicalGameState pgs = gs.getPhysicalGameState();
        Unit closestEnemy = null;
        int closestDistance = 0;  
        if(gs.getActionAssignment(u)==null && u.getType().canAttack)
        {
            for(Unit u2:pgs.getUnits()) 
            {
                if (u2.getPlayer()>=0 && u2.getPlayer()!=p.getID()) 
                { 
                    int d = Math.abs(u2.getX() - u.getX()) + Math.abs(u2.getY() - u.getY());
                    if (closestEnemy==null || closestDistance==0|| d<closestDistance) 
                    {
                        closestEnemy = u2;
                        closestDistance = d;
                    }
                }
            }
            attack(u,closestEnemy);
        }
    }    
    public void defenceBehavior(Unit u, Player p, GameState gs) {
        PhysicalGameState pgs = gs.getPhysicalGameState();
        Unit closestEnemy = null;
        Unit closestMeleeEnemy = null;
        int closestDistance = 0;
        int enemyDistance = 0;
        int mybase = 0;
        for(Unit u2:pgs.getUnits()) {
            if (u2.getPlayer()>=0 && u2.getPlayer()!=p.getID()) { 
                int d = Math.abs(u2.getX() - u.getX()) + Math.abs(u2.getY() - u.getY());
                if (closestEnemy==null || d<closestDistance) {
                    closestEnemy = u2;
                    closestDistance = d;
                }
            }
            else if(u2.getPlayer()==p.getID() && u2.getType() == m_utt.getUnitType("Base"))
            {
                mybase = Math.abs(u2.getX() - u.getX()) + Math.abs(u2.getY() - u.getY());
            }
        }
        if (closestEnemy!=null && (closestDistance < pgs.getHeight()/3 || mybase < pgs.getHeight()/3)) {
            attack(u,closestEnemy);
        }
        else
        {
            //如果附近没有敌人，返回基地
            //attack(u, null);
            Random r= new Random();
            int randX =(int)(-pgs.getHeight()/6+(r.nextInt())%(pgs.getHeight()/6)) ;
             int randY = (int)(-pgs.getHeight()/6+(r.nextInt())%(pgs.getHeight()/6));
             if(baseX+randX<0 || baseX+randX>pgs.getWidth()){
                 randX=0;
             }
             if(baseY+randY<0 || baseY+randY>pgs.getWidth()){
                 randY=0;
             }
            move(u,baseX+ randX ,baseY+randY);
        }
        
    }
    //框选一定范围内的单位，参数：gs, 单位名称，左上角坐标，长，宽, 单位数目（如果为-1则框选全部单位），是否只框选没有行动的单位(没有行动，而不是没有赋与行动（默认所有都框选，如果为true就只框选没有行动的单位）
    public List<Unit> selectUnitsAround(GameState gs,int player,String unitName ,int x,int y, int width,int height,int num, boolean  noAction){
        PhysicalGameState pgs= gs.getPhysicalGameState();
        int tempNum=0;
        List<Unit> selectUnits=new ArrayList<>();
        for(int i=x;i<x+width;i++){
            for(int j=y;j<y+height;j++){
                Unit tempUnit;
                tempUnit=pgs.getUnitAt(i, j);
                if( !( tempUnit == null || tempUnit.getType()!=m_utt.getUnitType(unitName)|| tempUnit.getPlayer()!=player)){
                    //如果是所有的单位都选中的话
                    if(!noAction){
                        selectUnits.add(tempUnit);
                        tempNum++;
                    }
                    else{
                        if(gs.getActionAssignment(tempUnit)==null){
                            selectUnits.add(tempUnit);
                            tempNum++;
                        }
                    }
                }
            }
            if(num!=-1){
                if(tempNum>=num){
                    return selectUnits;
                }
            }
        }
        return selectUnits;
    }
    
    /*获取八个方向的偏移量偏移大小为d
        输入  i:偏移方向 0到7 0表示正上方，然后顺时针旋转
             d:偏移大小
        输出：偏移数组 （x,y)
    
    */
    public int[] getOffset(int i,int d){
        int offset[] =new int[2];
        switch(i){
            case 0: offset[0]=-d; offset[1]=0; return offset;
            case 1: offset[0]=-d; offset[1]=d; return offset;
            case 2: offset[0]=0; offset[1]=d; return offset;
            case 3: offset[0]=d; offset[1]=d; return offset;
            case 4: offset[0]=d; offset[1]=0; return offset;
            case 5: offset[0]=d; offset[1]=-d; return offset;
            case 6: offset[0]=0; offset[1]=-d; return offset;
            case 7: offset[0]=-d; offset[1]=-d; return offset;
            default:  offset[0]=0; offset[1]=0; return offset;
        }
    }
    public List<ParameterSpecification> getParameters()
    {
        return new ArrayList<>();
    }
 
    
}