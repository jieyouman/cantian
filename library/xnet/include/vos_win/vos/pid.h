/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : pid.h
  �� �� ��   : ����

  ��������   : 2008��6��16��
  ����޸�   :
  ��������   : ����ϵͳ������PID
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��16��

    �޸�����   : �����ļ�

  2.��    ��   : 2008��11��12��

    �޸�����   : ɾ��_PID_��
******************************************************************************/

#ifndef __PID_H__
#define __PID_H__

/*ģ��ID����*/
/* ϵͳ���������Ϊ1024��PID����ЧֵΪ1--1023 */
/* ���е�PID�����Ķ���ƽ̨�Ӻ���ǰ���ӣ���Ʒ��ǰ�������� */
typedef enum tagPID_E
{ 
    PID_OSP_NULL = 0,           /*��Чֵ*/
    PID_OSP_DEBUG = 1,
    PID_RESOURCE = 2,
    PID_MODULE_INTERFACE = 3,
    PID_IBC = 4,
    PID_MML = 5,                /* MML */
    
    /* Begin s2600��� */
    PID_PRODUCT = 6,
    /* End s2600��� */
    
    PID_DRV_BIOS = 7,    /*BIOS����ģ��*/
    PID_DRV_API = 8,     /*�����ӿڲ�*/

    PID_FC_EVENT = 9,           /* Ϊ�������� */
    
    PID_TSDK = 10,
    PID_TSDK_FRONT = 11,
    PID_TSDK_INI   = 12,        /*TSDK ������*/
    PID_TGT_MIDDLE = 13,        /*Ŀ����*/
    PID_SCSI    = 14,           /* SCSI��*/
    PID_SAS_INI = 15,           /* SAS ������*/
    PID_IBS_SENDER   = 16,      /* ���ͨ��ģ��*/
    PID_IBS_RECEIVER = 17,
    PID_SAS_TGT = 18,           /*SASĿ����helinzhi59137*/
    PID_IBS_MAN = 19,           /* IBS����ģ��lixuhui 65736, 20070709*/

    PID_HMP    = 20,            /* ������·��*/
    PID_4KPOOL = 21,            /* 4K��ģ��*/
    PID_CACHE  = 22,            /* CACHEģ��*/

    /* Begin s2600��� */
    PID_APPCM  = 23,            /*����ҵ������ģ��*/
    /* End s2600��� */

    PID_RAID_CONTROL = 25,          /*RAID ����*/
    PID_RP_CACHE_INTERFACE = 26,    /*Cache�ӿ�ģ��*/
    PID_RP_DISK_INTERFACE  = 27,    /*Ӳ�̽ӿ�ģ��*/
    PID_RP_READ  = 28,              /*CACHE��ģ��*/
    PID_RP_WRITE = 29,              /*CACHEдģ��*/
    PID_RP_RECONSTRUCT = 30,        /*�ع�ģ��*/
    PID_RP_COPYBACK    = 31,        /*Copybackģ��*/
    PID_RP_LUN_FORMAT  = 32,        /* LUN��ʽ��ģ��*/
    PID_RP_XOR     = 33,            /* XORģ��*/
    PID_RP_MAP     = 34,            /* Mapģ��*/
    PID_RP_MUTEX   = 35,            /* ����ģ��*/
    PID_RP_LUN_VERIFY =36,

    PID_RP_PRIOSCHED = 37,      /* RAID���ȼ�����ģ�� */
    PID_RP_PS = 38 ,            /* RAID��������ģ�� */
    PID_DMP = 39,

    PID_DB = 40,
    PID_ISCSI   = 41,           /* ISCSI*/
    PID_SAFEBOX_CACHE = 42,     /* ������*/
    PID_SAFEBOX_ALARM = 43,     /* ������*/
    PID_SAFEBOX_DB = 44,        /* ������*/

    PID_WEB = 45,            
    OSP_CLI = 46,
    OSP_SYS = 47,       /* ϵͳ����ģ��*/

    OSP_DEV = 48,       /* ��Ʒ���豸�������Ϊʵ��������������Ҫʹ��ԭ���豸�����PID*/

    OSP_ALM = 49,       /* �澯��־*/

    OSP_USR   = 50,     /* �û���Ȩ*/
    OSP_MLIB  = 51,     /* ͨ����Ϣ����*/
    OSP_AGENT = 52,     /* SNMP AGENT*/
    PID_AGENT_CTRL = 53, /* SNMP AGENT ����ģ�� */

    OSP_BSP = 55,
    OSP_OS  = 56,
    OSP_MT  = 57,

    /* Begin s2600��� */
    PID_POWERSAVE_CONTROL = 58,
    PID_SAFEBOX_OS = 59,                   /*OS ������*/
    PID_RAMDISK = 60,                      /*װ������*/
    /* End s2600��� */

    PID_NET = 61,                      /*װ������*/

    PID_DCM_PRE = 62,       /* DCM��Ԥ���� */
    PID_DCM_CMD = 63,       /* DCM��������� */
    PID_DCM_ROUTINE = 64,   /* DCM������ */

    PID_SATA_DRV = 65,     /* sata���� */
    PID_PCIE_CARD = 66,	/* PCIe���� */

    PID_TOE = 67,         /* ������TOE */  
    PID_IWARP = 68,       /* ������IWARP */


    PID_ISCSI_INI = 70,         /* ISCSI������ */
                                
    PID_IB = 71,         /* ������IB */  
    PID_ACC = 72,       /* ������ACC */

    PID_VAULT = 75,             /* ������ */
    PID_INBAND_AGENT = 76,      /* ���ڹ������ж� */

    PID_VAULT_NVRAM = 77,                  /* VAULT NVRAMģ�� */ 

    /* ��ֵ����begin */
    PID_RSS = 80,               /* Replication Service Subsystem(��ֵ������ϵͳ) */
    PID_RSF = 81,                    /* Replication Service Frame ����ֵ���Կ�ܣ� */
    PID_RPR = 82,                    /* Replication Public Resource (��ֵ���Թ�����Դ) */
    PID_BGR = 83,                    /* Background Replication (��̨����) */
    PID_CLN = 84,                    /* ���Ѿ��� */
    PID_ECP = 85,                    /* ��չ����ģ�� */
    PID_LM = 86,                     /* LUNǨ��ģ�� */
    PID_RM = 87,                     /* Զ�̾��� */
    PID_CPY = 88,                    /* LUN���� */
    PID_SNAP = 89,                 /* ������� */
    PID_TB = 90,         /* ������ */
    PID_TP = 91,         /* Thin Provisioning(�Զ���������) */ 
    PID_TP_ASYNC_IBS = 92,  /* �첽IBS*/
    PID_RSS_UTILITY = 93,    /* ��ֵ���Թ���ģ��*/
    PID_LMR = 94,             /* ���� */

    PID_SBU_BACKUP = 95,	/*һ�廯����*/

    PID_RIM = 96,                   /*����IO�н�ģ��*/
    PID_DCL = 97,                   /*����DCLģ��*/
    PID_IO_CTRL = 98,               /*����IO_CTRLģ��*/
    PID_REP_IO_UTILITY = 99,        /*����IO����ģ��*/
    
    /* ��ֵ����end */

    PID_RP_LUN_EXPAND = 100,        /* LUN��չģ�� */
    PID_RP_DYNAMIC = 101,           /* ��̬����ģ�� */
    PID_RP_COMMSRV = 102,           /* RAID�������� */
    PID_RP_RAID6ALGORITHM = 103,    /* RAID6�㷨 */
    PID_RP_IBC_PROXY = 104,         /* �첽IBC���� */

    OSP_LICENSE = 105,
    PID_EPL = 110,                  /* �ⲿ���� external path&Lun  */
    PID_IMP = 111,                  /* �ڲ�I/Oת�� */
    PID_EBS_SENDER = 112,           /*EBS����ģ��*/
    PID_EBS_RECEIVER = 113,         /*EBS����ģ��*/
    PID_EBS_MAN = 114,              /*EBS����ģ��*/
    PID_TESTMACHINE = 115,          /* ����ģʽPID */
    
    PID_EA = 116,                   /* ͳһ�汾��Ʒ����� */
    PID_UG = 117,                   /* ͳһ�汾��Ʒ���� */
    PID_MT = 118,                   /* ͳһ�汾��Ʒ���� */
    PID_ET = 119,                   /* ͳһ�汾��Ʒװ������ */
    PID_DISKFAULT = 120,            /* �����޸� */
    PID_WS_BUSM = 121,    /* Wushanҵ�����ģ�� */
    PID_WS_MDS = 122,    /* Wushan MDSģ�� */
    PID_WS_OSN = 123,    /* Wushan OSNģ�� */
    PID_WS_PERF = 124,   /* Wushan���ܲɼ�ģ�� */
    PID_WS_UPGRADE = 125,   /* Wushan����ģ�� */
    PID_WS_DEV = 126,      /* Wushan�豸����ģ�� */
    PID_WS_DEPLOY = 127,      /* Wushan�Զ�����ģ�� */
    
    PID_AUTO_DISCOVERY = 128,       /* ���ֲ���ģ�飬�����Զ����֣�OMMʹ�� */

    /* VIS Start */
    PID_SF_REXE_SERV = 130,         /* VIS SF SSHD ����� */
    PID_SF_REXE_CLIENT = 131,       /* VIS SF SSHD �ͻ��� */
    /* VIS end */
    PID_BST = 132,        /* ������ */
    PID_DHA_VAULT = 133,  /* DHA������ģ�� */
    
    /* CR: xxxxxx SmartCache liangshangdong 00002039 20100506 add begin */
    PID_SSDC = 134,       /* Smart Cache */
    /* CR: xxxxxx SmartCache liangshangdong 00002039 20100506 add end */

    /*���OS������������512M  BootData�ռ�added by z90003978  20101117 begin*/
    PID_BOOTDATA_VAULT = 135,
    /*���OS������������512M  BootData�ռ�added by z90003978  20101117 end*/

    PID_UPGRADE_C99 = 136, /* c99����ģ�� */
    PID_VSTORE = 137,      /* ���⻧ģ�� */


    PID_DETECT_SLOWDISK = 138, /* �������̼��ģ��*/


    PID_OSP_BUTT,         /* ��Ʒ�ڴ�֮ǰ���� */
    
    PID_ST  = 140,         /* ���ұ�ģ�� */
    PID_CMM = 21,          /* Cache Memory Managementģ�� */
    PID_IO_SCHED = 142,    /* IO���ȿ��ģ�� */
    PID_IO_PERF = 143,     /* IO����ͳ��ģ�� */

    PID_PCIE_IBS = 144,
    PID_PCIE_HP = 145,
    PID_PCIE_BASE = 146,
    PID_DDEV = 147,
    PID_DIO = 148,

    /*Claire Zhong*/
    PID_QUOTA = 149,
    PID_PAGEPOOL = 150,
    PID_BDM = 151,    
    PID_BDM_SD = 152,
    PID_BDM_LD = 153,   
    PID_BDM_HDM = 154,   
    PID_BDM_MP = 155,
    PID_BDM_SCHED = 156,
    PID_BDM_SIO = 157,
    PID_BDM_BA = 158,	
	PID_OVERLOAD_CTRL = 199,     /*���ؿ���ģ��id*/
    PID_DEV_LUN = 200,           /* DEV LUN */
    PID_QOS = 201,               /* Qos */
    PID_PAIR = 202,              /* ��ֵPair */
    PID_VOLUME = 203,            /* Volume */
    PID_EXTENT = 204,            /* Extent */
    PID_CKG_IOF = 205,           /* CKG_IOF IO��� */
    PID_CKG_BST = 206,           /* CKG_BST ������ */
    PID_CKG_DISKLOG = 207,       /* CKG_DISKLOG Ӳ����־ */
    PID_CKG_RESTORE = 208,       /* CKG_RESTORE �����޸� */
    PID_CKG_RAID10 = 209,        /* RAID10 raid10�㷨 */
    PID_CKG_RAID5 = 210,         /* RAID5 raid5�㷨 */
    PID_CKG_RAID6 = 211,         /* RAID6 raid6�㷨 */
    PID_CKG_WRITEHOLE = 212,     /* WRITEHOLE writehole���� */
    PID_BACKSCAN = 213,          /* BACKSCAN ��̨ɨ�� */
    PID_SPA_NODEMGR = 214,       /* SPA_NODEMGR spa�ڵ���� */
    PID_SPA_LAYOUT = 215,        /* SPA_LAYOUT spa���ֹ��� */
    PID_SPA_SPACEMGR = 216,      /* SPA_SPACEMGR spa�ռ���� */
    PID_SPA_TXMGR = 217,         /* SPA_TXMGR spa������� */
    PID_DISK_SELECT = 218,       /* DISK_SELECT ѡ���㷨 */
    PID_SPACEMAP = 219,          /* SPACE_MAP �ռ�ͼ�㷨 */
    PID_BTREE = 220,             /* BTREE b+tree�㷨 */
    PID_RECON = 221,             /* RECON �ع�ģ�� */
    PID_LEVELING = 222,          /* LEVELING ����ģ�� */
    PID_DST_MONITOR = 223,       /* DST_MONITOR dst i/o��� */
    PID_DST_ANALYSE = 224,       /* DST_ANALYSE dst�Ų����� */
    PID_DST_PREDICTION = 225,    /* DST_PREDICT dst����Ԥ�� */
    PID_DST_MIGRATION = 226,     /* DST_MIGRATE dst����Ǩ�� */
    PID_PMGR = 227,              /* PMGR pool����ģ�� */
    PID_XNET = 228,
    PID_XRB  = 229,
    PID_EXTENT_INIT = 230,
    PID_DSCP = 231,
    PID_XNET_ETH = 232,
    PID_XNET_PCIE = 233,
    PID_CLS_MSG_FILTER = 234,
    PID_UPGRADE_ATOM = 240,     /* ����ԭ�� */
    PID_LINK_CFG = 241,         /* ��ֵ����·����ģ�� */
    PID_SYS_EVENT = 242,        /* ϵͳ�¼�����ģ�� */
    PID_HEAL = 243,             /* ������� */
    PID_SPA_BACKUP = 244,       /* Ԫ���ݱ���*/
    PID_DIF = 250,              /* DIF����ģ�� */
    PID_DISTR_TX_FRAME = 251,   /* �ֲ�ʽ������ */
    PID_LOGZONE = 252,          /* ��־��ģ�� */
    PID_CKG_TSF_UNDER = 253,    /* CKG IOת��(StripCache֮��) */
    PID_CKG_TSF_ABOVE = 254,    /* CKG IOת��(StripCache֮��) */
    PID_USER_POOL =255,           /* UserPoolMgr */

    PID_CLM = 256,               /* ��Ⱥ�ֲ�ʽ��ģ��id */
    PID_THROUGH_WRITEHOLE = 257, /* ͸дwriteholeģ��id */
    
    PID_VOLUME_CACHE = 258,      /* һ��Cacheģ�� */
    PID_STRIPE_CACHE = 259,      /* ����Cacheģ�� */
	
    PID_SPA_MCACHE = 260,       /* SPA_MCACHE spaԪ����cache */

    PID_UPDA = 261,     /* ����ģ�� Agent �Ķ��� */
    PID_CLIADAPTER = 262,     /* CLI������ */
    PID_CKG_DISK = 263, /* CKG DISK IO����ʽ�� */

    PID_SPACE = 300,                /* space��ϵͳ 300 ~ 349 */
    PID_SPACE_PAL = 301,            /* PALģ��id */
    PID_SPACE_CONTROL = 302,        /* Space Controlģ��id */
    PID_SPACE_IO = 303,             /* Space IOģ��id */
    PID_SPACE_TX = 304,
    PID_SPACE_SNAP = 305,  /* �ļ�ϵͳ����ģ��id*/
    PID_CONTEXT = 306,              /* Contextģ��id */
    PID_KVDB = 307,                 /*KV DBģ��id */
    PID_SPACE_NOTIFY = 308,         /* Notifyģ��id */
    PID_SPACE_FILE_COUNT = 309,
    

    PID_GRAIN = 310,                /* �䳤������ģ��id */

    PID_SNAS = 311,                 /* �ļ�ϵͳЭ��ģ��id */
    PID_SPACE_SCHED = 312,          /* �ļ�ϵͳ��̨ͳһ���� */
    PID_PAL_FORWORD = 313,

    PID_SPACE_FLOW_CTRL = 314,   /* �ļ�ϵͳ���ؿ���ģ��id*/
    PID_SPACE_RAL = 315,         /* �ļ�ϵͳRALģ��id*/
	PID_FS_AV = 316,
    PID_SPACE_UB  = 317,         /* �ļ�ϵͳUBģ��id*/

    PID_SPACE_ERR_3 = 347,          /* Space������ר��id */
    PID_SPACE_ERR_2 = 348,          /* Space������ר��id */
    PID_SPACE_ERR_1 = 349,          /* Space������ר��id����������ʹ�� */
	
	PID_DDP = 350,  /* ��ɾѹ��ģ��id */
	PID_CROSS_CLS = 599,  /* ��վ�㼯Ⱥ����id */
    
   	/* ��Ⱥ����ģ�� */
	PID_CLUSTER_MSG_FRAMEWORK = 600, /*��Ϣ���䡢��Ϣ���*/
	PID_CLUSTER_CAB = 601,    /*��Ⱥԭ��ͨ��*/
	PID_CLUSTER_DLM = 602,    /*�ֲ�ʽ������*/
	PID_CLUSTER_CCDB_SERVER = 603, /*CCDB�����*/
	PID_CLUSTER_CCDB_CLIENT = 604, /*CCDB�ͻ���*/
	PID_CLUSTER_PAXOS = 605,    /*��ȺPaxos*/
	PID_CLUSTER_RPM = 606,		/*RPM��Ϣ����*/
	PID_CLUSTER_EVENT = 607,    /*��Ⱥ�¼����ģ������û�̬��*/
	PID_CLUSTER_LIB = 608, 		/*��Ⱥ������*/
	PID_CLUSTER_CNM = 609,		/*��Ⱥ�ڵ����*/
	PID_CLUSTER_MSG_BNET = 610,  /*��Ⱥͨ�ŷ�װģ��*/

    /* ��������ģ��[630~649] */
    PID_TCP_LINK = 630,       /* ��EPL�ṩ����TCPIP��˽�д���Э���ͨ����· */
	PID_CPS = 631,           /* ˫���ٲ�ģ��*/
	PID_REP_HC = 632,        /* ˫�����Կ���ģ��*/
	PID_VMG = 633,        /* �⻧Ǩ�ƿ���ģ��*/
	PID_REPRM = 634,        /* �ļ�Զ�̸��ƿ���ģ��*/
	PID_REPTMP = 635,      /* ����ģ�� */
    PID_REPSVC = 636,        /* ���Ʒ������ģ��*/
    PID_REPRPC = 637,        /* ����RPC����ģ��*/
    PID_SDD = 638,           /* ����ѹ��ģ��*/
    PID_ARB = 639,           /* ˫���ٲ�ģ��*/
    PID_ARB_AGENT = 640,     /* ˫���ٲ��û�̬ģ��PID */
    
	/* Э������ģ��650~699 */
	PID_PROTO_OMAGENT = 650,	/*NASЭ����Ϣ����*/
	PID_PROTO_SYSCTRL = 651,  /*NASЭ��ϵͳ����ģ��*/
	
	
	
    /* PID 700-799���η�����̹�ƽ̨����ģ�� begin*/
    PID_SAS_INI_SAL = 705,	/*12g sas*/
    PID_FC_UNF = 710,		/*16G FC*/
    PID_BSPA = 715,             /*BSP�����*/
    PID_DSWA = 720,             /*�����������*/
    PID_ISCSI_TRANS_SW = 750, /*����iSCSI�����ģ��*/
    PID_FCOE = 770,

    PID_DMI = 730,              /*PANGEA�豸������*/


    /* PID 700-799���η�����̹�ƽ̨����ģ�� end*/
    
    /* ��ֲC3ģ��PID */
    PID_MSG_ADAPTER = 806,       /* ��Ϣ����ģ�� */
    PID_TRANSFER_DEBUG = 807,    /* ��Ϣ����ģ�� */

    PID_HAB = 808,               /*  heart beat */
    PID_MEMP = 809,               /*����豸������Ϣת��*/
    PID_FTDS = 900,         /* FTDSģ�� */

    /* ƽ̨�����PID */
    PID_LOG_CBB = 948,
    PID_MSG_CHECK = 949,
    PID_UTOP_BEGIN = 950,
	
    PID_PERF_SAMPLE = PID_UTOP_BEGIN,   /* ����ͳ�Ʋ����� */
    PID_PERF_MANAGE = 951,   /* ����ͳ�ƹ���� */

    PID_LOCK  = 952,       /* ȫ����ģ�� */
    PID_LOCK_CLIENT = 953, /* ȫ����ģ�� */
    PID_DAB  = 954,        /* ����ԭ�ӹ㲥ģ�� */
    PID_MAST = 955,        /*���������û�̬*/
    PID_DHA_SCHED = 956,   /* DHA������ */
    PID_SIMULATOR = 957, /* ���� */
    PID_DHA_COLLECTOR = 958, /* DHA �����ɼ��� */
    PID_SCM = 959,           /* SCM ������ */
    PID_SCM_KRN = 960,       /* SCM �ں˳��� */
    PID_AA_KERNEL = 961,    /* AUTH �ں˳��� */
    PID_OM_SYNC = 962,         /* SYNC ������ */
    PID_VMMS_KERNEL = 963,    /* VMMS�ں˴��� */
    PID_VMMS = 964,
    PID_ILOCK = 965,        /* IO��Χ�� */
    PID_ASYNC_LOCK = 966,   /* �첽�� */
    
    PID_VOS = 997,          /*vos*/
    PID_OS_TOOL = 998,      /* OS TOOL */
    PID_MC  = 999,          /* ��Ϣ������ת�� */
    PID_MSG = 1000,
    PID_MSG_SERVER = 1001,
    PID_MSG_CLIENT = 1002,

    PID_MMT = 1003,         /* ������Ϣ�ַ�ģ�� */
    PID_MMT_KERNEL = 1004,  /* ������Ϣ�ַ�ģ���ں�̬ */
    PID_MMT_NOTIFY  = 1005, /* �����ϱ�ģ�� */

    PID_AA = 1006,

    PID_LIC_KERNEL = 1007,  /* Licenseģ���ں�̬ */

    PID_LIB_STD = 1008,     /* ��׼�� */

    PID_UPGRADE = 1009,     /* ����ģ��Ķ��� */

    PID_PERF_KERNEL = 1010, /* ����ͳ���ں�̬ */
    PID_PERF_USER = 1011,   /* ����ͳ���û�̬ */
    PID_DCM = 1012,         /* ����ͨ��ģ�� */
    PID_EVENT = 1013,       /* �¼�����ģ�� */
    PID_UPGRADE_KERNEL = 1014,
    PID_OS_SYNC_DISK = 1015, /*os ������ͬ��ʹ��*/
    PID_OS_FIRE_HDD = 1016,  /* usb������Ӳ��ʹ�� */
    PID_OS_TEST = 1017,      /* OSģ��ϵͳ���ϸ�λ */
    PID_OS_DEBUG = 1018,     /* OS Debug */
    PID_ECONF = 1019,        /* ����չ�������ļ�ģ�� */
    PID_EML = 1020,          /* ����pid */
    PID_GEM = 1021,
    PID_VERSION = 1022,    /* ���ڲ鿴����ģ��汾�ŵ�MML���� */
    PID_DEBUG = 1023,       /* ƽ̨DBGģ�� */


    PID_UTOP_BUTT = 1024    /* ���PID */
} PID_E;


#ifndef INVALID_PID
#define INVALID_PID 0
#endif

#define MAX_PID_NUM 1024


#endif

