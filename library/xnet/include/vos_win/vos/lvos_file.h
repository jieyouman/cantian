/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_file.h
  �� �� ��   : ����

  ��������   : 2008��12��29��
  ����޸�   :
  ��������   : �ļ������ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��12��29��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_file.h
    \brief �ļ���������ӿڣ�֧��windows��linux�ں�̬��linux�û�̬���ļ������ӿڿ��ܻᵼ�µ�����������

    \date 2008-12-29
*/

/** \addtogroup VOS_FILE �ļ�����
    @{ 
*/


#ifndef __LVOS_FILE_H__
#define __LVOS_FILE_H__

#define INVALID_FD (-1)

/* �ļ�·������󳤶� */
#define MAX_FILE_PATH_LENTH 1024

/* �ļ�������ƴ���������󳤶� ���������2��·���ͼ����ַ���� */
#define MAX_FILE_SHELL_CMD_LEN 4096

/* tar������Ҫ�Ĳ���ģʽ */
typedef enum tagLVOS_TAR_TYPE_E
{
    LVOS_TAR_TYPE_ARCHIVE = 0, /* ��� */
    LVOS_TAR_TYPE_EXTRACT,     /* ��� */
    LVOS_TAR_TYPE_BUTT
} LVOS_TAR_TYPE_E;

#ifdef __KERNEL__
#define NAME_OFFSET(de) ((int) ((de)->d_name - (char __user *) (de)))

struct linux_dirent {
unsigned long    d_ino;      
unsigned long    d_off;      
unsigned short   d_reclen;     
char             d_name[1]; 
}; 


struct getdents_callback {
struct linux_dirent * current_dir;
struct linux_dirent * previous;
int                   count;      
int                   error;
};
#endif

#ifdef WIN32
/* windows������unix�µ��ļ�Ȩ��λ���������к� */
/* ������Ȩ�� */
#define S_IRUSR S_IREAD
#define S_IWUSR S_IWRITE
#define S_IXUSR S_IEXEC
#define S_IRWXU (S_IRUSR | S_IWUSR | S_IXUSR)

/* windows����ʱ����ͳһģ��Ϊ������ */
#define S_IRGRP S_IREAD
#define S_IWGRP S_IWRITE
#define S_IXGRP S_IEXEC
#define S_IRWXG (S_IRGRP | S_IWGRP | S_IXGRP)

#define S_IROTH S_IREAD
#define S_IWOTH S_IWRITE
#define S_IXOTH S_IEXEC
#define S_IRWXO (S_IROTH | S_IWOTH | S_IXOTH)
#else
#define O_TEXT   0  /* Linux�²������Ƿ����ı� */
#define O_BINARY 0
#endif  /* __KERNEL__ */

/* ����ļ��Ƿ���ڼ��Ƿ�ӵ��Ȩ�� */
#define MODE_EXIST  00      /* �ļ��Ƿ���� */
#define MODE_READ   02      /* �Ƿ�ӵ�ж�Ȩ�� */
#define MODE_WRITE  04      /* �Ƿ�ӵ��дȨ�� */
#define MODE_RW     06      /* �Ƿ�ӵ�ж�дȨ�� */

/** 
    \brief ����ļ��Ƿ���ڼ�ӵ��Ȩ��
    \param[in] v_szFilePath ��Ҫ�����ļ�·�����ļ���
    \param[in] v_iMode          ��Ҫ����ģʽ
    \return  ���ɹ����� RETURN_OK, ���ʧ�ܷ��� RETURN_ERROR
    \attention ֧�ֵ�ģʽΪ MODE_EXIST, MODE_READ, MODE_WRITE, MODE_RW
*/


OSP_S32 LVOS_access(const OSP_CHAR *v_szFilePath, OSP_S32 v_iMode);

/** 
    \brief ���ļ�
    \note  ͬ���ӿڣ��п��ܵ��µ���������
    \param[in] v_pcPath     ��Ҫ�򿪵��ļ�·�����ļ���
    \param[in] v_iFlag      ��Ҫ�򿪵��ļ�������
    \param[in] v_iMode      ��Ҫ�򿪵��ļ���Ȩ��
    \retval    ��ȷ�򿪣������ļ����ļ������������򣬷���RETURN_ERROR
*/

OSP_S32 LVOS_open(const OSP_CHAR *v_pcPath, OSP_S32 v_iFlag, OSP_S32 v_iMode );

/** 
    \brief ���ļ��ж�ȡ����
    \note  ͬ�������ӿڣ��Ӵ��̶�ȡ�����У����ܻᵼ�µ���������
    \param[in] v_iFd        ��Ҫ��ȡ���ļ����ļ�������
    \param[in] v_pBuf       �û��ṩ�Ķ��뻺����
    \param[in] v_ulCount    �û�ϣ����ȡ���ֽ���
    \retval    ��ȷ��ȡ�����ֽ��������󷵻�RETURN_ERROR
*/
OSP_LONG LVOS_read( OSP_S32 v_iFd, void *v_pBuf, OSP_ULONG v_ulCount );

/** 
    \brief ���ļ��ж�ȡһ������
    \note  ͬ�������ӿڣ��Ӵ��̶�ȡ�����У����ܻᵼ�µ���������
    \param[in] v_iFd        ��Ҫ��ȡ���ļ����ļ�������
    \param[in] v_pBuf       �û��ṩ�Ķ��뻺����
    \param[in] v_iMaxSize   ����ȡ�ĳ���
    \retval    û�ж�ȡ������NULL, �����������v_pBuf��ֵ
*/
OSP_CHAR *LVOS_readline( OSP_S32 v_iFd, void *v_pBuf, OSP_S32 v_iMaxSize);

/** 
    \brief ��һ���ļ�д������
    \note  ����openʱ����v_iFlag�ļ����ԵĲ�ͬ�������Ƿ�ȴ�ʵ�ʵ�����I/O��ɺ󷵻أ������п��ܵ��µ���������
    \param[in] v_iFd        ��Ҫд����ļ����ļ�������
    \param[in] v_pBuf       �û��ṩ��д�뻺����
    \param[in] v_ulCount    �û�ϣ��д����ֽ���
    \retval    ��ȷд����ֽ��������󷵻�RETURN_ERROR
*/
OSP_LONG LVOS_write( OSP_S32 v_iFd, const void *v_pBuf, OSP_ULONG v_ulCount );

/** 
    \brief �ض�λ�ļ�ָ��
    \param[in] v_iFd        ��Ҫ�ض�λ���ļ����ļ�������
    \param[in] v_lOffset    �µ��ļ�ָ��ƫ��
    \param[in] v_iWhence    �ļ�ָ����ʼλ��
    \retval    ��ȷ�ض�λ�򷵻�������ļ���ʼλ�õ��ļ�ƫ�ƣ����򷵻�RETURN_ERROR
*/
OSP_LONG LVOS_lseek( OSP_S32 v_iFd, OSP_LONG v_lOffset, OSP_S32 v_iWhence );

/** 
    \brief ˢָ�����ļ����������ݵ�����
    \note  ͬ�������ӿڣ�ʵ������д�������Ϻ󷵻أ���˿��ܵ��µ���������
    \param[in] v_iFd      ��Ҫִ��ˢ�̲������ļ����ļ������� 
    \retval RETURN_OK     �������óɹ�
    \retval RETURN_ERROR  ��������ʧ��
*/
OSP_S32 LVOS_sync (OSP_S32 v_iFd);

/** 
    \brief �رմ򿪵��ļ�
    \param[in] v_iFd      ��Ҫ�رյ��ļ����ļ�������
    \retval RETURN_OK     �ر��ļ��ɹ�
    \retval RETURN_ERROR  �ر��ļ�ʧ��
*/
OSP_S32 LVOS_close( OSP_S32 v_iFd );

/** 
    \brief �����ļ�
    \param[in] v_pcSrcfile      Դ�ļ���
    \param[in] v_pcDestfile     Ŀ���ļ���
    \retval RETURN_OK     �����ļ��ɹ�
    \retval RETURN_ERROR  �����ļ�ʧ��
*/

OSP_S32 LVOS_copy(const OSP_CHAR * v_pcSrcfile, const OSP_CHAR * v_pcDestfile);




#if DESC("�ļ����ӿ�")
/** \brief �ļ������Ͷ��� */
enum LVOS_FLOCK_TYPE_E
{
    LVOS_FLOCK_TYPE_RDW,   /**< ��ȡ����������������Ľ����������ȴ� */
    LVOS_FLOCK_TYPE_RWW,   /**< ��ȡ��д��������������Ľ����������ȴ� */
    LVOS_FLOCK_TYPE_RDNW,  /**< ��ȡ����������������Ľ�����������������ش��� */
    LVOS_FLOCK_TYPE_RWNW   /**< ��ȡ��д��������������Ľ�����������������ش��� */
} ;

/** \brief �ļ���������Ϣ */
typedef struct
{
    OSP_LONG l_type;    /**< �ο� \ref LVOS_FLOCK_TYPE_E ����*/
    OSP_LONG l_offset;  /**< ��Ҫ�������ݵ�ƫ�Ƶ�ַ */
    OSP_LONG l_len;     /**< ��Ҫ�������ݵĳ��� */
} LVOS_FLOCK_S;

/** 
    \brief �ļ�������
    \param[in] v_iFd      ʹ��\ref LVOS_open�򿪵��ļ�������
    \param[in] v_pstFlock ��������Ϣ���ο�\ref LVOS_FLOCK_S���������Ƿ�֮��Ĭ��Ϊͬ����ȡ����
    \note Ŀǰֻʵ�����û�̬(Linux��Windows)���ļ�����ֻ�ڶ��ʹ���ļ����Ľ���֮����Ч�����������������������޷����ʸ��ļ�, ���ڶ����������֮��������
    \retval RETURN_OK     �ɹ�
    \retval RETURN_ERROR  ʧ��
*/
 OSP_S32 LVOS_LockFile(OSP_S32 v_iFd, LVOS_FLOCK_S *v_pstFlock);

/** 
    \brief �ļ�������
    \param[in] v_iFd      ʹ��\ref LVOS_open�򿪵��ļ�������
    \param[in] v_pstFlock ��������Ϣ���ο�\ref LVOS_FLOCK_S
    \note Ŀǰֻʵ�����û�̬(Linux��Windows)
    \retval RETURN_OK     �ɹ�
    \retval RETURN_ERROR  ʧ��
*/
 OSP_S32 LVOS_UnLockFile(OSP_S32 v_iFd, LVOS_FLOCK_S *v_pstFlock);

#endif



/*****************************************************************************
 �� �� ��  : LVOS_CmdCp
 ��������  : �ļ���Ŀ¼�Ŀ�������
 �������  : const OSP_CHAR *v_pcSrcfile   
             const OSP_CHAR *v_pcDestfile  
             OSP_BOOL v_bIsDir             
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��7��1��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile      Դ�ļ�
    \param[in] v_pcDestfile     Ŀ���ļ�
    \param[in] v_bIsDir         �Ƿ���Ŀ¼
    \retval RETURN_OK           �����ļ��ɹ�
    \retval RETURN_ERROR        �����ļ�ʧ��
*/

OSP_S32 LVOS_CmdCp(const OSP_CHAR *v_pcSrcfile, const OSP_CHAR *v_pcDestfile, OSP_BOOL v_bIsDir);

/*****************************************************************************
 �� �� ��  : LVOS_CmdRm
 ��������  : �ļ���Ŀ¼���Ƴ�����
 �������  : const OSP_CHAR *v_pcfile  
             OSP_BOOL v_bIsDir         
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��7��1��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcfile         ��Ҫ�Ƴ����ļ���Ŀ¼
    \param[in] v_bIsDir         �Ƿ���Ŀ¼
    \retval RETURN_OK           �Ƴ��ɹ�
    \retval RETURN_ERROR        �Ƴ�ʧ��
*/

OSP_S32 LVOS_CmdRm(const OSP_CHAR *v_pcfile, OSP_BOOL v_bIsDir);

/*****************************************************************************
 �� �� ��  : LVOS_CmdTar
 ��������  : ����������
 �������  : const OSP_CHAR *v_pcfile  
             const OSP_CHAR *v_pcDir   
             OSP_U32 v_uiMode          
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��7��1��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcfile         ����
    \param[in] v_pcDir          �������: ��Ҫ������ļ�(Ŀ¼);�������: ���Ŀ��Ŀ¼
    \param[in] v_uiMode         �������(������ߴ��)
    \retval RETURN_OK           ����ɹ�
    \retval RETURN_ERROR        ���ʧ��
*/

OSP_S32 LVOS_CmdTar(const OSP_CHAR *v_pcfile, const OSP_CHAR *v_pcDir, OSP_U32 v_uiMode);

/*****************************************************************************
 �� �� ��  : LVOS_CmdTouch
 ��������  : �����ļ����޸��ļ���ʱ���(�޸��ļ���ʱ����ݲ�ʵ��)
 �������  : const OSP_CHAR *v_pcfile  
             OSP_U32 v_uiMode          
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��7��1��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcfile         �ļ���
    \param[in] v_uiMode         �����ļ����޸��ļ���ʱ���
    \retval RETURN_OK           �ɹ�
    \retval RETURN_ERROR        ʧ��
*/

OSP_S32 LVOS_CmdTouch(const OSP_CHAR *v_pcfile, OSP_U32 v_uiMode);

/*****************************************************************************
 �� �� ��  : LVOS_CmdMv
 ��������  : ���������ƶ�����
 �������  : const OSP_CHAR *v_pcSrcfile   
             const OSP_CHAR *v_pcDestfile  
             OSP_BOOL v_bIsDir             
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��7��1��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile         Դ�ļ�����ԴĿ¼��
    \param[in] v_pcDestfile        Ŀ���ļ�����Ŀ��Ŀ¼��
    \param[in] v_bIsDir            �Ƿ���Ŀ¼
    \retval RETURN_OK              �ɹ�
    \retval RETURN_ERROR           ʧ��
*/

OSP_S32 LVOS_CmdMv(const OSP_CHAR *v_pcSrcfile, const OSP_CHAR *v_pcDestfile, OSP_BOOL v_bIsDir);

/*****************************************************************************
 �� �� ��  : LVOS_CmdMkdir
 ��������  : ����Ŀ¼������
 �������  : OSP_CHAR *v_pcfile  
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2010��6��18��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile         ��Ҫ������Ŀ¼��
    \retval RETURN_OK              �ɹ�
    \retval RETURN_ERROR           ʧ��
*/

OSP_S32 LVOS_CmdMkdir(OSP_CHAR *v_pcfile);

#ifndef _PCLINT_

#ifdef __KERNEL__
/*****************************************************************************
 �� �� ��  : LVOS_readdir
 ��������  : ��ȡĿ¼����
 �������  : OSP_CHAR *v_pcPath 
             filldir_t filler �ص�����
             void * buf  �������ڴ�ռ�
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��5��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile         ��Ҫ������Ŀ¼��
    \retval RETURN_OK              �ɹ�
    \retval RETURN_ERROR           ʧ��
*/

OSP_S32 LVOS_readdir(const OSP_CHAR * v_pcPath, filldir_t filler, void * buf);



/*****************************************************************************
 �� �� ��  : LVOS_stat
 ��������  : ��ȡ�ļ�����
 �������  : OSP_CHAR *v_pcPath 
             struct kstat* buf  �����ļ�����
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��5��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile         ��Ҫ������Ŀ¼��
    \retval RETURN_OK              �ɹ�
    \retval RETURN_ERROR           ʧ��
*/

OSP_S32 LVOS_stat(const char* v_pcPath, struct kstat* buf);



/*****************************************************************************
 �� �� ��  : LVOS_statfs
 ��������  : ��ȡ�ļ�ϵͳ����
 �������  : OSP_CHAR *v_pcPath 
             struct kstat* buf  �����ļ�����
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��5��

    �޸�����   : �����ɺ���

*****************************************************************************/
/** 
    \brief �ļ�����
    \param[in] v_pcSrcfile         ��Ҫ������Ŀ¼��
    \retval RETURN_OK              �ɹ�
    \retval RETURN_ERROR           ʧ��
*/

OSP_S32 LVOS_statfs(const char* v_pcPath, struct kstatfs* buf);

#endif
#endif

#endif /* __LVOS_FILE_H__ */

/** @} */


