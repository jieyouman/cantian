/******************************************************************************
     ��Ȩ���� (C) 2010 - 2010  ��Ϊ�������˿Ƽ����޹�˾
*******************************************************************************
* �� �� ��: ����
* ��������: 2011��7��28��
* ��������: ϵͳȫ��REQ/SGL�ṹ����
* ��    ע:
* �޸ļ�¼:
*         1)ʱ��    :
*          �޸���  :
*          �޸�����:
******************************************************************************/
#ifndef _REQ_SGL_H
#define _REQ_SGL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "lvos.h"
#define INVALID_VOLUME_ID 0xffffffffffffffff
#define INVALID_CKG_ID 0xffffffff
typedef uint64_t volumeid_t;

/** \addtogroup objpub  ҵ����󹫹�����
    \section intro_sec ˵��
    @{
*/

/** \brief ����REQ������ */
typedef enum
{
    OP_NOP          = 0,              /* do nothing */
    OP_WRITE        = 0x13218000,
    OP_READ         = 0x00128001,
    OP_WRITE_ALLOC  = 4,              /* Ŀ��������ռ������д���� */

    OP_FORMAT       = 6,              /* ��ʽ�������� */
    OP_VERIFY       = 7,              /* У�� */
    OP_RECONSTRUCT  = 8,              /* �ع� */
    OP_RECOVER      = 9,              /* �ָ��ع� */
    OP_RESTORE      = 10,             /* �����޸� */
    OP_WRITEHOLE    = 11,             /* writehole�ָ�д������У������ */
    OP_PRECOPY      = 12,             /* Ԥ���� */

    OP_READ_THROUGH = 13,             /* ͸�������ͷŵ�CACHE�еĸɾ����ݺ�ֱ�Ӷ��� */
    OP_EBC_MSG      = 14,             /* ����EBC��Ϣ */

    OP_LEVELING     = 15,             /* ���� */
    /* ���ⵥ��:P12N-3240, Ԫ����͸����д�޸�ʵ��, c90005714, 2012/09/22,begin*/
    OP_REPAIR_WRITE = 16,             /* Ԫ����͸���ɹ����޸�д */
    OP_STRIPE_REPAIR = 17,             /* �����޸� */
    /* ���ⵥ��:P12N-3240, Ԫ����͸����д�޸�ʵ��, c90005714, 2012/09/22,end*/

    OP_RSS_REPAIR_WRITE = 18,           /* ��ֵ�����޸�д */
    OP_RSS_REPAIR_READ = 19,            /* ��ֵ�����޸��� */

    /*SCSI�·���˽������ begin*/
    OP_SCSI_PRIVATE_WRITE_ALLOC = 20,
    OP_SCSI_PRIVATE_WRITE = 21,
    OP_SCSI_PRIVATE_READ = 22,
    /*SCSI�·���˽������ end*/

    OP_READ_THROUGH_FOR_RETRY = 23,    /* ͸����������*/
                                       /*ǰ���ڶ� IO ����DIFУ�����ʱ�·�����cache
                                         �����е������ݷ��أ������������̶�ȡ��
                                         �Զ���������У�����һ���ԣ���һ����ɹ����أ�
                                         ����˵���������ݲ��ɿ�������ʧ��*/
    OP_STRIPE_INCON_RESTORE = 24,
    /*BEGIN,V3R3 �汾���޸ģ������ĸ�ö�٣��̹�֧��V3֮ǰ����Ӳ����Ҫ*/
    OP_SNAP_READ  =  (OP_READ  | 0x00000040),  /* ������ն� OP_READ  | 100,0000b(0x40) */
    OP_SNAP_WRITE =  (OP_WRITE | 0x20000040),  /* �������д OP_WRITE | 100,0000b(0x40) */

    OP_CLN_READ   =  (OP_READ  | 0x00000080),  /* ���Ѿ����OP_READ  | 1000,0000b(0x80) */
    OP_CLN_WRITE  =  (OP_WRITE | 0x20000080),  /* ���Ѿ���дOP_WRITE | 1000,0000b(0x80) */
    /*END*/

    OP_CPY_READ   =  (OP_READ  | 0x000000c0),  /* LUN������OP_READ  | 1100,0000b(0xc0) */
    OP_CPY_WRITE  =  (OP_WRITE | 0x200000c0),  /* LUN����дOP_WRITE | 1100,0000b(0xc0) */

    /*BEGIN,V3R3 �汾���޸ģ����°˸�ö�٣��̹�֧��V3֮ǰ����Ӳ����Ҫ*/
    OP_LM_READ    =  (OP_READ  | 0x00000100),  /* lunǨ�ƶ�OP_READ  | 1,0000,0000b(0x100) */
    OP_LM_WRITE   =  (OP_WRITE | 0x20000100),  /* lunǨ��дOP_WRITE | 1,0000,0000b(0x100) */

    OP_RM_READ    =  (OP_READ  | 0x00000140),  /* Զ�̾����OP_READ  | 1,0100,0000b(0x140) */
    OP_RM_WRITE   =  (OP_WRITE | 0x20000140),  /* Զ�̾���дOP_WRITE | 1,0100,0000b(0x140) */

    OP_ECP_READ   =  (OP_READ  | 0x00000180),  /* FULLCOPY��OP_READ  | 1,1000,0000b(0x180) */
    OP_ECP_WRITE  =  (OP_WRITE | 0x20000180),  /* FULLCOPYдOP_WRITE | 1,1000,0000b(0x180) */

    OP_LMR_READ   =  (OP_READ  | 0x00000280),  /* �����OP_READ  | 10,1000,0000b(0x280) */
    OP_LMR_WRITE  =  (OP_WRITE | 0x20000280),  /* ����дOP_WRITE | 10,1000,0000b(0x280) */
    /*END*/

    /*BEGIN, Dorado V3�汾������Pool�ø������ͷ�SSD�ռ䣬BDM�账������� */
    OP_TRIM       = 25,              /* �ͷ�SSD�ռ� */
    /*END*/

    /*Զ�̸��ƣ�˫��ʹ��*/
    OP_REMOTE_READ    =  (OP_READ  | 0x00000140),  /* Զ�̾����OP_READ  | 1,0100,0000b(0x140) */
    OP_REMOTE_WRITE   =  (OP_WRITE | 0x20000140),  /* Զ�̾���дOP_WRITE | 1,0100,0000b(0x140) */

    /* ������������Ҫ�õ� */
    OP_PRIVATE_WRITE = 53,
    OP_PRIVATE_MIRROR_WRITE = 54,
    OP_PRIVATE_DIRECT_WRITE = 55,
    OP_DELETE_CACHE = 56,         /* ɾ��CACHE���� */

    /* ����(�ļ�)����ʹ�� */
    OP_OBJSET_REP_ALLOC = 70, /* ������д���� */
    OP_OBJSET_REP_WRITE = 71, /* ������дִ�� */

    /*��ֵ��дʹ��ͳһ�Ĳ����루���ա���¡��lm��lmr�ȣ�*/
	OP_REP_READ  = 72,
	OP_REP_WRITE = 73,

    /*���м�SCSIԪ����д*/
	OP_REP_SCSI_WRITE  = 74,

    /*˫��ת��˫д*/
    OP_REP_TRANS_WRITE = 75,

    OP_REP_SCSI_READ  = 76,
#ifdef DECLARE_FOR_DRV_COMPAT
    /* only used by DMP */
    OP_DMP_WRITE       =  0x1c018020,
    OP_DMP_READ         =  0x0c028021,
    /* modify end by lixuhui(65736), for DE4 IBS, 20070706 */
    OP_MIRROR_READ = 11,
    OP_MIRROR_WRITE  =  0x12018010,

    OP_MIRROR_MSG      =  0x11018011,

    OP_PRIVATE_READ = 50,
    OP_PRIVATE_WRITE_PARSE = 51,
    OP_PRIVATE_WRITE_ALLOC = 52,
#endif

    OP_PVT_MSG = 0x3c018000,         /* ����˽����Ϣ */
    OP_INFO_READ = 0x3c028000,       /* ��ѯ���ղ���λͼ */
    /*�����Ժ���: windows2012��֤��������,SR-0000341803��20140118��start*/
    OP_QUERY = 0X4c0a8000,  /*��ѯ������*/
    /*�����Ժ���: windows2012��֤��������,SR-0000341803��20140118��end*/


    OP_HOST_WRITE_REQ_NEED_ABORT = 0x5c0a8000,
    OP_HOST_WRITE_REQ_FINISH_ABORT = 0x5c0b8000,


    OP_BUTT
} REQ_OP_E;

typedef struct tagIOD_S
{
    struct list_head iodQueueNode;   /*���ڽ�REQ������ȶ�������ڵ� */
    int64_t  delayTime;              /*��ʱʱ��,�����ӳ�ִ��*/
    uint16_t pid;                     /*ģ��pid*/
    uint16_t validFlag;              /* �Ϸ���У���� */
    uint8_t ioThreadid;             /*�߳�ID����һ�ε��ȵ�IOD�߳�ID*/
    uint8_t  isInQueue;              /*�Ƿ����IOD���У���ֹ�ظ�����*/
    uint8_t  type;                    /* ����REQ/CMD */
    uint8_t  pri;                     /* ���ȼ� */
} IOD_S;

typedef struct
{
    char     *buf;         /* ҳ��������ʼ��ַ */
    void     *pageCtrl;    /* ҳ�����ͷ��ַ */
    uint32_t len;          /* ��Ч���ݳ��ȣ���λΪbyte */
    uint32_t pad;
} SGL_ENTRY_S;

#define ENTRY_PER_SGL 64
typedef struct tagSGL_S
{
    struct tagSGL_S *nextSgl;           /* ��һ��sglָ�룬�������sgl�� */
    uint16_t     entrySumInChain;       /* sgl����sgl_entry���������ֶ�����sgl����һ��sgl����Ч */
    uint16_t     entrySumInSgl;         /* ��sgl��sgl_entry���� */
    uint32_t     flag;                  /* ���ݱ�ǣ����ڱ�ʶ��sgl���Ƿ������ҳ�桢bstҳ��� */
    uint64_t     serialNum;             /* sgl���к�*/
    SGL_ENTRY_S  entrys[ENTRY_PER_SGL]; /* sgl_entry����*/
    struct list_head stSglNode;
    uint32_t     cpuid ;                /* ��������ýṹ��ʱ��cpu */
} SGL_S;

typedef struct tagREQ_S  REQ_S;
#define MAX_REQ_OPS_NAME_LEN 40
typedef struct tagREQ_OPS_S
{
    char name[MAX_REQ_OPS_NAME_LEN];   /**< ��REQ�������� */
    int32_t  (*start)(REQ_S *req);         /**< ��REQִ�к��� */
    int32_t  (*done)(REQ_S *req);          /**< ��REQ������ɻص������� */
    void (*childDone)(REQ_S *selfReq, REQ_S *childReq);   /**< ��REQ������ɻص���������REQ�ṩ����REQ���� */
    void (*del)(REQ_S *req);        /**< ��REQ��Դ�ͷŲ���������һ���ɸ�REQ���� */
} REQ_OPS_S;

#define MAX_REQ_PRIVATE 32
/** \brief REQ�ṹ */
struct tagREQ_S
{
    IOD_S iodPrivate;              /**< IODʹ�õ�˽����Ϣ */

    uint32_t opCode;             /**< IO�����룬�ο�enum ReqOpCode_e�����ö��ֵ */
    volumeid_t volumeId;           /**< Volume id����ʹ��ʱ��ȫF */
    uint64_t objectId;           /**< ���ʶ���id�����ݷ��ʶ���ͬ������extent id��ckg id��disk id�� */
    uint64_t objectLba;          /**< ���ʵ���ʼ���� */
    uint32_t length;             /**< ���ʵ��������� */

    int32_t  result;             /**< REQִ�н�� */

    uint64_t ctrlFlag;           /**< ���Ʊ��(REQ_CTRL_FLAG_XXX)*/

    SGL_S    *sgl;               /**< REQ���������б���ҳ�� */
    SGL_S    *remoteSgl;         /**< REQ���������о���ҳ�� */
    uint32_t bufOffsetNByte;  /**< ��REQ�ܹ�ʹ�õ�sgl��ƫ�Ƶ�ַ(�ֽ���) */

    uint16_t priority;           /**< IO���ȼ�*/
    uint16_t objectType;               /**< �������*/

    REQ_OPS_S   *ops;         /**< ��REQ�����в������� */

    REQ_S           *parent;     /**< ��REQ�ĸ�REQ */
    struct list_head childList;  /**< �ӽڵ�����ͷ����REQΪ���ڵ�ʱʹ�� */
    struct list_head childNode;  /**< �ӽڵ�����ڵ㣬���ڼ��븸�ڵ���ӽڵ����� */
    atomic_t         notBackNum; /**< δ���ص���REQ���� */
    uint32_t         childSum;   /**< ��REQ���� */

    uint64_t producerPrivate[MAX_REQ_PRIVATE]; /* ����˽����; �����ɸ�REQ��ģ��ʹ��*/
    uint64_t consumerPrivate[MAX_REQ_PRIVATE]; /* ����˽����; �����ո�REQ��ģ��ʹ��*/
    void     *parentSaveInfo;                  /**< ��REQ��������REQ�е�˽����Ϣ, ��REQʹ�� */

    uint64_t onFlyProcess;       /**< REQ����״̬���*/

    uint64_t ioSeiralNumber;     /**< REQ IO���кţ�����REQʱ��д������IOʱ��ͳ��*/
    uint64_t ioStartTime;        /**< REQ��ʼִ�е�ʱ��*/

    int32_t  stat;               /**< ��Ҫ����������֮�䴫����Ϣ*/
    uint32_t pad2;               /**< �������*/

    int8_t   readHit;            /**< �Ƿ����б�־*/
    uint8_t  pad3;               /**< �������*/
    uint8_t  readThroughTimes;   /**< ����͸��ʱ�������Դ���*/
    uint8_t pad4;                /**< �������*/
    uint32_t pad5;               /**< �������*/
    //TRACEINFO_S traceInfo;  /**< FTDS����͸����Ϣ��FTDSר��*/
    REQ_S   *nextReq;              /**< ָ����һ��REQ��������֯REQ��*/
};

/* REQ��صĲ����궨�� */
#define REQ_CHILDDONE(req, childReq)  \
    ((req)->ops->childDone((req), (childReq)))
#define REQ_DELETE(req)               ((req)->ops->del((req)))
#define REQ_START(req)                ((req)->ops->start((req)))
#define REQ_DONE(req)                 ((req)->ops->done((req)))

/* ���úͻ�ȡreq�Ķ����б�־ */
#define SET_REQ_READ_HIT(req) ((req)->readHit = TRUE)
#define SET_REQ_NOT_READ_HIT(req) ((req)->readHit = FALSE)
#define REQ_IS_READ_HIT(req)  (TRUE == (req)->readHit)

/**
\brief REQ ctrl flag����
*/
    /* �����ݿ飬4096+64��ʽ�����ø�λ��Ϊ512+8��ʽ*/
#define REQ_CTRL_FLAG_LONG_BLOCK    (1<<0)
    /* ��������DIF�����������󲻲���DIF */
#define REQ_CTRL_FLAG_NO_DIF_PROTECT    (1<<1)
    /* ��������DIFУ�顣��������DIFУ��*/
#define REQ_CTRL_FLAG_NO_DIF_VERIFY    (1<<2)
    /* ��������DIFУ�顣��������DIFУ��*/
#define REQ_CTRL_FLAG_WRITE_THROUGH    (1ULL<<63)

/**
\brief REQ ctrl flag�����궨��
*/
/* ��ctrl Flagλ, ͬʱ�ö��λ���û����������flag */
#define SET_REQ_CTRL_FLAG(req, flag)    ((req->ctrlFlag) |= (flag))
/* ���ctrl Flagλ, ͬʱ������λ���û����������flag */
#define CLEAR_REQ_CTRL_FLAG(req, flag)    ((req->ctrlFlag) &= ~(flag))
/* �ж�ĳctrl Flagλ�Ƿ���1 */
#define TEST_REQ_CTRL_FLAG(req, flag)    ((req->ctrlFlag) & (flag))

/** \brief GENIO_S�ṹ����������IOʱ����REQ��Ϣ���ݸ���REQ������ֶκ�����REQ��Ӧ�ֶ���ͬ */
//����GENIO_S�ṹ���˳���REQ_S��Ӧ����Сcachemiss
typedef struct
{
    uint32_t opCode;             /**< IO�����룬�ο�enum ReqOpCode_e�����ö��ֵ */
    volumeid_t volumeId;           /**< Volume id����ʹ��ʱ��ȫF */
    uint64_t objectId;           /**< ���ʶ���id�����ݷ��ʶ���ͬ������extent id��ckg id��disk id�� */
    uint64_t objectLba;          /**< ���ʵ���ʼ���� */
    uint32_t length;             /**< ���ʵ��������� */
    uint16_t objectType;
    uint16_t pad2;               /**< �������*/
    uint64_t ctrlFlag;           /**< ���Ʊ�ǣ���ǻ�͸д���Ƿ����*/

    SGL_S    *sgl;               /**< REQ���������б���ҳ�� */
    SGL_S    *remoteSgl;         /**< REQ���������о���ҳ�� */

    uint32_t bufOffsetNByte;     /**< ��REQ�ܹ�ʹ�õ�sgl��ƫ�Ƶ�ַ(�ֽ���) */
    uint16_t priority;           /**< ���ȼ� */
    uint8_t  readThroughTimes;   /**< ����͸��ʱ�������Դ���*/
    uint8_t  notNeedDIF;         /**< IO�Ƿ���Ҫ��DIFУ��, TRUE:����Ҫ��У��, FALSE:��Ҫ��У��*/
    REQ_S    *parent;            /**< ��REQ�ĸ�REQ */

    void     *parentSaveInfo;   /**< ��REQ��������REQ�е�˽����Ϣ, ��REQʹ�� */
    /* toChildInfo��Ҫ�ˣ���ģ���ṩiogen��ʱ��������Զ����������iogen�����п����Զ�����������ݵ�˽�������м��� */

    uint64_t ioSeiralNumber;     /**< REQ IO���кţ�����REQʱ��д������IOʱ��ͳ��*/
    uint64_t volumeLba;
    //TRACEINFO_S traceInfo;  /**< FTDS����͸����Ϣ��FTDSר��*/
} GENIO_S;

/** \brief      ��������һ�������ݵ�SGL chain
 \param[in,out]  sglPtr ����ʱ���NULL
 \param[in,out]  entryIndex �����һ��Entry��SGL�е������±꣬����ʱ���0
 \retval     ��
*/
void move2NextEntryAndModifyPSgl(SGL_S** sglPtr, uint32_t* entryIndex);
/** \brief      ��sgl���ҳ�������ƶ���ǰentryλ�ú�sglָ�룬������sglҳ�����
 \param[in,out] sglPtr      ���sgl������ʱ���NULL
 \param[in,out] entryIndex  �ƶ����entry��SGL�е������±꣬����ʱ���0
 \param[in]     sglHead     sgl����ͷ
 \retval     ��
 */
void move2NextEntryAndIncEntrySum(SGL_S** sglPtr, uint32_t* entryIndex, SGL_S* sglHead);
/** \brief      sglƫ�ƶ��ҳ��
 \param[in,out]  sglPtr      sglָ���ַ
 \param[out]     entryIndex  Entry��SGL�ڵ������±�
 \param[in]      offset      ƫ��ҳ������
 \retval     ��
*/
void sglAndEntryOffsetPages(SGL_S **sglPtr, uint32_t *entryIndex, uint32_t offset);
/** \brief      ����SGL������SGL��entry
 \param[in]   inSgl    ����SGL -- SGL����ͷ
 \param[out]  outSgl  ���SGL
 \param[out]  singleEntry   ���Entry -- Entryλ��(��1��ʼ����)
 \retval     ��
 \see
 \note
 */
void getLastSgl(SGL_S *inSgl, SGL_S **outSgl, uint32_t *singleEntry);
/** \brief      ��ȡsgl ����Ч��ҳ����
    \param[in]  sglPtr        SGL
    \param[in]  sglOffsetByte ƫ���ֽ���
    \param[in]  lengthByte    ����
    \retval     sgl����Чҳ����
*/
uint32_t getValidSglPageNum(SGL_S * sglPtr, uint32_t sglOffsetByte, uint32_t lengthByte);

/** \brief      ��һ��sgl��ָ��entry��ҳ���滻����ҳ��, ͬʱ�ͷ�ԭҳ��
    \param[in]  SGL_S *  sglPtr sgl��ַ
    \param[in]  uint8_t entryArray[] ���entry��������
    \param[in]  uint8_t entryNum     ��Ҫ�滻��entry��������������Ԫ�ظ���
    \retval     ��
*/
void exchangeZeroPageBySglEntryIdx(SGL_S* sglPtr, uint8_t entryArray[], uint8_t entryNum);

/** \brief      ����һ��SGL�е�ȫ��ҳ�浽�µ�дҳ����
    \param[in]   srcSgl         ������ԴSGL
    \param[in]   volumeId       Ŀ��SGLҪд���volume
    \param[in]   tierType       Ŀ��SGLҪд���tier����
    \param[in]   pageType       Ŀ��SGLҳ����;
    \param[in]   inputReqCtrlFlag   �����REQ��͸д��־
    \param[in]   callbackFunc   �ص�����
    \param[in]   callBackArg    �ص�����
    \retval     ����ִ�еĽ��
*/
int32_t copySglForWrite(SGL_S* srcSgl,
                        volumeid_t volumeId,
                        uint32_t tierType,
                        uint32_t pageType,
                        uint64_t inputReqCtrlFlag,
                        void (*callbackFunc)(SGL_S* targetSgl, void* callbackArg),
                        void* callBackArg);
/** \brief      ����һ��SGL�е�ĳЩҳ�浽�µ�дҳ����
    \param[in]  srcSgl      ������ԴSGL
    \param[in]  offsetByte  ԴSGL��OFFSET
    \param[in]  length      Դ����ҳ��ĵ�LENGTH
    \param[in]  reqLba      Դ����ҳ���LBA
    \param[in]  volumeId    Ŀ��SGLҪд���volume
    \param[in]  tierType    Ŀ��SGLҪд���tier����
    \param[in]  pageType    Ŀ��SGLҳ����;
    \param[in]  inputReqCtrlFlag   �����REQ��͸д��־
    \param[in]  callbackFunc  �ص�����
    \param[in]  callBackArg   �ص�����
    \retval     ����ִ�еĽ��
    \note       �����ɵ�sgl��offsetByte��0������reqҪ���¸�ֵΪ0
*/
int32_t copySglForWriteByOffset(SGL_S *srcSgl,
                                uint32_t offsetByte,
                                uint32_t length,
                                uint64_t reqLba,
                                volumeid_t volumeId,
                                uint32_t tierType,
                                uint32_t pageType,
                                uint64_t inputReqCtrlFlag,
                                void (*callbackFunc)(SGL_S *targetSgl, void *callbackArg),
                                void *callBackArg);

/** \brief      ͨ��offset��ȡ���Ӧ��sgl��entry
    \param[in]  sglPtr            sgl������ͷ��ַ
    \param[in]  offseByte       ��Ч���ݵ�ƫ����
    \param[out] outSgl        ƫ�Ƶ�ַ����sgl
    \param[out] singleEntry    ƫ�Ƶ�ַ����entry �±��
    \param[out] bufOffset      ��entry�е�ƫ��
    \retval     ����ִ�еĽ��
*/
int32_t  getCurrentSglByOffset(SGL_S *      sglPtr,
                               uint32_t     offseByte,
                               SGL_S **     outSgl,
                               uint32_t*    singleEntry,
                               uint32_t*    bufOffset);

/** \brief      ��ʾsgl��Ϣ
    \param[in]  sglPtr Ҫ��ʾ��sgl
    \retval     ��
*/
void showSglShell(SGL_S* sglPtr);

/** \brief ��ʾsgl������
 \param[in] sglPtr Ԥ��ʾ��sglָ��
 \retval     ��
*/
void showSglData(SGL_S* sglPtr);

/** \brief ��req����Ϣ������genio
    \param[in]     req     ���Ƶ�Դreq
    \param[in,out] genio   Ŀ��genio
    \retval     ��
    \see  copyGenio2Req
    \note (һ���ڵ���genio����֮ǰ����)
*/
void copyReq2Genio(GENIO_S *genio, REQ_S *req);

/** \brief        ��genio����Ϣ������req
    \param[in]     genio ������Դgenio
    \param[in,out] req   ���Ƶ�Ŀ��req
    \retval       ��
    \see  copyReq2Genio
    \note (һ����genio�����е���)
*/
void copyGenio2Req(REQ_S *req, GENIO_S *genio);

/** \brief        ת���ڴ�ռ䵽sgl
    \param[in]    buf      �ڴ�ռ��ַ
    \param[in]    length   �ڴ泤��(�ֽ���)
    \retval       sgl��
*/
SGL_S *fillBufToSgl(char *buf, uint32_t length);

/** \brief        ����sgl�е�ҳ��Ĳ���У����
    \param[in]    srcSgl     ��ҳ���sgl
    \param[in]    offsetByte ��Ч���ݵ�ƫ����
    \param[in]    length   ���ݳ���(�ֽ���)
    \param[out]   crc     ����CRC����ֵ
    \retval       ִ�н��
*/
int32_t createSglCrc32c(SGL_S *srcSgl, uint32_t offsetByte,
                        uint32_t length, uint32_t *crc);
/** \brief      ��һ��sgl�е�������CRCУ��,sgl�е�ҳ���СΪ4160�������ǰ4KΪ���ݺ�64��
                ��Ϊdif���ݵ�ҳ�棬�˺���������ÿ��ҳ��ĺ�64�ֽ����ݣ�������ǰ4K�ռ��ڵ���Ч���ݡ�
  \param[in]    SGL_S *srcSgl     ��ҳ���sgl
  \param[in]    uint32_t offsetByte ��Ч���ݵ�ƫ����(������DIF����)
  \param[in]    uint32_t length   ���ݳ���(�ֽ���)
  \param[in]    uint32_t *crc     ����CRC����ֵ
  \retval       ִ�н��
  \see
 \note          (HVSC99 DIF��Ԫ����У��ʹ��)
*/
int32_t createSglCrc32IgnoreDif(SGL_S *srcSgl, uint32_t offsetByte,
                                uint32_t length, uint32_t *crc);

/** \brief      ��һ�������ڴ濽�����ݵ�sgl
 \param[in]     dstSgl          Ŀ��sgl��ͷָ��
 \param[in]     dstOffsetInByte Ŀ��sgl��������ʼƫ��(�ֽ�)
 \param[in]     buffer          ������Դ���ݵ�ַ
 \param[in]     dataLength      ���������ݳ���(�ֽ�)
 \retval        RETURN_OK     �����ɹ�
 \retval        RETURN_ERROR  ����ʧ��

 */
int32_t copyDataFromBufferToSgl(SGL_S *dstSgl, uint32_t dstOffsetInByte,
                                char *buffer, uint32_t dataLength);

/** \brief      ��sgl�������ݵ�һ�������ڴ�
 \param[in]     srcSgl          Դsgl��ͷָ��
 \param[in]     srcOffsetInByte Դsgl��������ʼƫ��(�ֽ�)
 \param[in]     buffer          ������Ŀ�����ݵ�ַ
 \param[in]     dataLength      ���������ݳ���(�ֽ�)
 \retval        RETURN_OK     �����ɹ�
 \retval        RETURN_ERROR  ����ʧ��

 */
int32_t copyDataFromSglToBuffer(SGL_S *srcSgl, uint32_t srcOffsetInByte,
                                char *buffer, uint32_t dataLength);



/** \brief      ͨ��offset��ȡ���Ӧ��sgl��entry(����64B��DIF����)
    \param[in]  SGL_S *  v_pstSgl sgl������ͷ��ַ
    \param[in]  OSP_U32  v_uiOffseByte��Ч���ݵ�ƫ����(������DIF����)
    \param[out] SGL_S ** v_ppstOutSglƫ�Ƶ�ַ����sgl
    \param[out] OSP_U32 *v_puiSingleEntry ƫ�Ƶ�ַ����entry �±��
    \param[out] OSP_U32 *v_puiBufOffset  ��entry�е�ƫ��
    \retval     ����ִ�еĽ��
    \see
    \note      (HVSC99 DIF������4K + 64ҳ������)
*/
int32_t  getCurrentSglByOffsetIgnoreDif(SGL_S *      sglPtr,
                                        uint32_t     offseByteNoDif,
                                        SGL_S **     outSgl,
                                        uint32_t*    singleEntry,
                                        uint32_t*    bufOffset);


/** \brief    ��һ�������ڴ濽�����ݵ�sgl��ÿ��entryֻ���4KB ������,����DIF����
 \param[in]   dstSgl          : Ŀ��sgl��ͷָ��
 \param[in]   offseByteNoDif  : Ŀ��sgl��������ʼƫ��(�ֽڣ�������DIF����)
 \param[in]   buffer          : ������Դ���ݵ�ַ
 \param[in]   dataLength      : ���������ݳ���(�ֽ�)
 \retval      int32_t         : OK �����ɹ���ERROR ����ʧ��
 \see
 \note        (HVSC99 DIF������4K + 64ҳ������)
 */
int32_t copyDataFromBufferToSglIgnoreDif(SGL_S *dstSgl, uint32_t offseByteNoDif,
                                         char *buffer, uint32_t dataLength);

/** \brief    ��sgl�������ݵ�һ�������ڴ棬��������Ч���ݣ�������DIF����
              ����dstOffsetInByte����Ч���ݵ�ƫ�ƣ�������DIF����
 \param[in]   srcSgl          : Դsgl��ͷָ��
 \param[in]   offseByteNoDif  : Դsgl��������ʼƫ��(�ֽڣ�������DIF����)
 \param[in]   buffer          : ������Ŀ�����ݵ�ַ
 \param[in]   dataLength      : ���������ݳ���(�ֽڣ���Ч���ݳ��ȣ�������DIF����)
 \retval      int32_t         : OK �����ɹ���ERROR ����ʧ��
 \see
 \note        (HVSC99 DIF������4K + 64ҳ������)
 */
int32_t copyDataFromSglToBufferIgnoreDif(SGL_S *srcSgl, uint32_t offseByteNoDif,
                                         char *buffer, uint32_t dataLength);

/** \brief      ����sgl����ҳ�������Ϊֻ��
 \param[in]     sgl           sgl��ͷָ��
 \retval        ��
 \note          �˺������������������ٽ�����ʹ�ã�ֻ�ܽ�sgl�е���ҳ������Ϊֻ��
*/
void setSglPageRO(SGL_S *sgl);

/** \brief      ����sgl����ҳ�������Ϊ�ɶ�д
 \param[in]     sgl           sgl��ͷָ��
 \retval        ��
 \see
 \note          �˺������������������ٽ�����ʹ��
*/
void setSglPageRW(SGL_S *sgl);

#ifdef _DEBUG
#define SET_SGLPAGE_RO(sgl) setSglPageRO((sgl))
#define SET_SGLPAGE_RW(sgl) setSglPageRW((sgl))
#else
#define SET_SGLPAGE_RO(sgl)
#define SET_SGLPAGE_RW(sgl)
#endif /* _DEBUG */

/** @} */

#ifdef __cplusplus
}
#endif


#endif

