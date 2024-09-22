/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_socket.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��5��27��
  ����޸�   :
  ��������   : socket����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��5��27��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_socket.h
    \brief socket����ͷ�ļ�
    \note  ֧��windows/linux_kernel/linux_user��ʹ�ù����п��ܻᵼ�µ�������������˲��������жϵȲ�����������������

    \date 2008-12-24
*/

/** \addtogroup VOS_SOCKET Socket��
    socket��Ľӿںͱ�׼�ӿ�һ�£���ֱ�Ӳο���׼�ӿڵĺ���˵��
    @{ 
*/

#ifndef _LVOS_SOCKET_H_
#define _LVOS_SOCKET_H_

/* Windows�����µ�Vista���°汾��֧�� IPv6 */
#if !defined(WIN32) || (_WIN32_WINNT >= 0x0600)
#define IS_OS_SUPPORT_IPV6  1
#else
#define IS_OS_SUPPORT_IPV6  0
#endif


/* ��KSOCKETʵ�ֱ�ʡ��PCLINTʱ����ʹ��WIN32�Ķ��� */
#if (defined(WIN32) || defined(_PCLINT_)) && !defined(_PCLINT_KSOCKET_) /* WIN32, link Ws2_32.lib  */

#define SHUT_RD     0
#define SHUT_WR     1
#define SHUT_RDWR   2
#define ADDR_LEN 16

typedef int socklen_t;

/** \brief Windows��Ҫ��ʼ��socket�⣬�����ṩ��غ������ú�����linux��Ϊ��
    \return ��
*/
static inline void LVOS_SocketInit(void)
{
    WSADATA wsaData;

    /* Windows��Ҫ��ʼ��socket�� */
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
    {
        printf("Error at WSAStartup");
    }
}

static inline void LVOS_SocketExit(void)
{
    return;
}

/** \brief socket������װ */
#define LVOS_socket       socket
/** \brief bind������װ */
#define LVOS_bind         bind
/** \brief listen������װ */
#define LVOS_listen       listen
/** \brief accept������װ */
#define LVOS_accept       accept
/** \brief connect������װ */
#define LVOS_connect      connect
/** \brief sendto������װ */
#define LVOS_sendto       sendto
/** \brief send������װ */
#define LVOS_send         send
/** \brief recvfrom������װ */
#define LVOS_recvfrom     recvfrom
/** \brief recv������װ */
#define LVOS_recv         recv
/** \brief closesocket������װ */
#define LVOS_closesocket  closesocket
/** \brief inet_addr������װ */
#define LVOS_inet_addr(x) (OSP_U32)inet_addr(x)
/** \brief getpeername������װ */
#define LVOS_getpeername  getpeername
/** \brief select������װ */
#define LVOS_select       select
/** \brief ioctlsocket������װ */
#define LVOS_ioctlsocket  ioctlsocket
/** \brief setsockopt������װ */
#define LVOS_setsockopt   setsockopt
/** \brief getsockopt������װ */
#define LVOS_getsockopt   getsockopt
/** \brief shutdown������װ */
#define LVOS_shutdown     shutdown

#elif defined(__LINUX_USR__)
/* Linux�û�̬  */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>

#define LVOS_SocketInit()
#define LVOS_SocketExit()

#define LVOS_socket       socket
#define LVOS_bind         bind
#define LVOS_listen       listen
#define LVOS_accept(s, addr, paddrlen)       accept(s, addr, (socklen_t *)(paddrlen))
#define LVOS_connect      connect
/* Linux�û�̬ͳһ����MSG_NOSIGNAL��־����������socket�Զ˷Ƿ��˳����½��̷Ƿ��˳� */
#define LVOS_sendto(s, buf, len, flags, to, tolen)  sendto((s), (buf), (len), ((flags) | MSG_NOSIGNAL), (to), (tolen))
#define LVOS_send(s, buf, len, flags)               send((s), (buf), (len), ((flags) | MSG_NOSIGNAL))
#define LVOS_recvfrom     recvfrom
#define LVOS_recv         recv
#define LVOS_closesocket  close
#define LVOS_inet_addr    inet_addr
#define LVOS_getpeername(s, addr, paddrlen)  getpeername(s, addr, (socklen_t *)(paddrlen))
#define LVOS_select       select
#define LVOS_ioctlsocket  ioctl
#define LVOS_setsockopt(s, level, optname, optvalue, optlen)   setsockopt(s, level, optname, optvalue, (socklen_t)(optlen))
#define LVOS_getsockopt(s, level, optname, optvalue, poptlen)   getsockopt(s, level, optname, optvalue, (socklen_t *)(poptlen))
#define LVOS_shutdown     shutdown

#elif defined(__KERNEL__)
#ifndef _PCLINT_
#include <linux/in.h>
#endif

#define SHUT_RD     0
#define SHUT_WR     1
#define SHUT_RDWR   2

typedef int socklen_t;

/* ��ʱû��ʵ��select */
void LVOS_SocketInit(void);
void LVOS_SocketExit(void);
int LVOS_socket(int family, int type, int protocol);
int LVOS_bind(int iSocket, struct sockaddr *myaddr, int addrlen);
int LVOS_listen(int iSocket, int backlog);
int LVOS_accept(int iSocket, struct sockaddr *upeer_sockaddr, int *upeer_addrlen);
int LVOS_connect(int iSocket, struct sockaddr *srvraddr, int addrlen);
int LVOS_sendto(int iSocket, void *buff, size_t len, int flags, struct sockaddr *addr, int addr_len);
int LVOS_send(int iSocket, void *buff, size_t len, int flags);
int LVOS_recvfrom(int iSocket, void *buff, size_t size, int flags, struct sockaddr *addr, int *addr_len);
int LVOS_recv(int iSocket, void *buff, size_t size, int flags);
int LVOS_closesocket(int iSocket);
int LVOS_getpeername(int iSocket, struct sockaddr *addr, int *sockaddr_len);
int LVOS_setsockopt(int iSocket, int level, int optname, char *optval, int optlen);
int LVOS_getsockopt(int iSocket, int level, int optname, char *optval, int *optlen);
int LVOS_ioctlsocket(int iSocket, long cmd, unsigned long *argp);
OSP_U32 LVOS_inet_addr(const char *sipaddr);
int LVOS_shutdown(int iSocket, int how);

#else
#error "platform not specify"
#endif




/** \brief ��ȡ�������ڵ�ipv6��ַ; ��ʱ����,�÷��������osҪȥ��֪����ڵĴ���
    \param[out]  v_szIPString  ���ڴ洢ȡ�õ��������ڵ�IP��ַ�ַ�����buffer��Ҫ��֤������40���ֽڵĿռ�
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_GetMngtIPAddr6(OSP_CHAR *v_szIPString);

/** \brief ���������豸���ƻ�ȡIP��ַ
    \param[in]  v_szEthName  �����豸����
    \param[out] v_puiIpAddr  IP��ַ
    \param[out] v_puiMask    �������룬�ò�������ΪNULL��ʾ��ȡ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_GetEthIPAddr(const OSP_CHAR *v_szEthName, OSP_U32 *v_puiIpAddr, OSP_U32 *v_puiMask);

/** \brief ��OSP_U32 ���͵�IP ��ַת��Ϊ�ַ�����
    \param[in]  stAddr  IP ��ַ
    \param[out] pszBuf  ���ڱ���ת���Ժ��IP��ַ���ַ���
    \retval IP���ַ�����ַ�����pszBufΪNULL�򷵻��ڲ���̬���������������򷵻�pszBuf
*/
OSP_CHAR * LVOS_inet_ntoa(OSP_U32 stAddr, OSP_CHAR *pszBuf);

/** \brief ���������ڰ�
    \param[in] v_pszBondPortName ����
    \param[in] v_ppszPortName    Ҫ�󶨵Ķ˿�������
    \param[in] v_uiPortNum       Ҫ�󶨵Ķ˿ڸ���
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_SetBond(OSP_CHAR * v_pszBondPortName, OSP_CHAR * v_ppszPortName[], 
                                                OSP_U32 v_uiPortNum);

/** \brief ��ȡ�����ڰ�
    \param[in] v_pszBondPortName  ����
    \param[in] v_ppszPortName     Ҫȡ���󶨵Ķ˿�������
    \param[in] v_uiPortNum        Ҫȡ���󶨵Ķ˿ڸ���
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_CancelBond(OSP_CHAR * v_pszBondPortName,
                                            OSP_CHAR * v_ppszPortName[], OSP_U32 v_uiPortNum);

OSP_S32 LVOS_InitBond(OSP_CHAR *v_pszBondName);
/** \brief ��ʱ���ö˿�IP����д�������ļ�
    \param[in] v_pszPortName  �˿���
    \param[in] v_pIpAddr      IP
    \param[in] v_pNetMask     ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_SetPortIP(OSP_CHAR * v_pszPortName , OSP_CHAR *v_pIpAddr,
                                                OSP_CHAR *v_pNetMask);

/** \brief ��ȡ�˿�IP
    \param[in] v_pszPortName  �˿���
    \param[in] v_pIpAddr      IP
    \param[in] v_pNetMask     ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_GetPortIP(OSP_CHAR * v_pszPortName , OSP_CHAR *v_pIpAddr,
                                                OSP_CHAR *v_pNetMask);

/** \brief ɾ���˿�IP
    \param[in] v_pszPortName  �˿���
    \param[in] v_pIpAddr      IP
    \param[in] v_pNetMask     ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_DelPortIP(OSP_CHAR * v_pszPortName , OSP_CHAR *v_pIpAddr,
                                                OSP_CHAR *v_pNetMask);												


/** \brief ���·����Ϣ������ϵͳ�ںˣ���д�������ļ�
    \param[in] v_pszPortName  �˿���
    \param[in] v_pDestAddr    Ŀ��IP
    \param[in] v_pDestMask    ����
    \param[in] v_pGateWay     ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_AddPortRoute(OSP_CHAR * v_pszPortName, OSP_CHAR * v_pDestAddr, 
                                                         OSP_CHAR * v_pDestMask, OSP_CHAR * v_pGateWay);

/** \brief �Ӳ���ϵͳ�ں�ɾ��·����Ϣ����д�������ļ�
    \param[in] v_pszPortName �˿���
    \param[in] v_pDestAddr Ŀ��IP
    \param[in] v_pDestMask ����
    \param[in] v_pGateWay  ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_DelPortRoute(OSP_CHAR * v_pszPortName, OSP_CHAR * v_pDestAddr, 
                                                OSP_CHAR * v_pDestMask, OSP_CHAR * v_pGateWay);

/** \brief ��ʱ���ö˿�IP����д�������ļ�
    \param[in] �˿���
    \param[in] IP
    \param[in] ���볤��
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_SetPortIP6(OSP_CHAR * v_pszPortName , OSP_CHAR *v_pIp6Addr,
                                                OSP_U32 iNetMaskLen);

/** \brief ��ʱɾ���˿�IP����д�������ļ�
    \param[in] �˿���
    \param[in] IP
    \param[in] ���볤��
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_DelPortIP6(OSP_CHAR * v_pszPortName , OSP_CHAR *v_pIp6Addr,
                                                OSP_U32 iNetMaskLen);

/** \brief ��ʱ���·����Ϣ����д�������ļ�
    \param[in] �˿���
    \param[in] Ŀ��IP
    \param[in] ���볤��
    \param[in] ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_AddPortRoute6(OSP_CHAR * v_pszPortName, OSP_CHAR * v_pDestAddr, 
                                                         OSP_S32 iDestMaskLen, OSP_CHAR * v_pGateWay);

/** \brief ��ʱɾ��·����Ϣ����д�������ļ�
    \param[in] �˿���
    \param[in] Ŀ��IP
    \param[in] ���볤��
    \param[in] ����
    \retval RETURN_OK  �ɹ�
    \retval RETURN_ERROR ʧ��
*/
OSP_S32 LVOS_DelPortRoute6(OSP_CHAR * v_pszPortName, OSP_CHAR * v_pDestAddr, 
                                                OSP_S32 iDestMaskLen, OSP_CHAR * v_pGateWay);

/** \brief �Ƚ�����IP �Ƿ��ͻ
    \param[in] IP��ַ1
    \param[in] ����
    \param[in] IP��ַ2
    \param[in] ����
    \retval TRUE  ��ͻ
    \retval FALSE ����ͻ
*/
OSP_BOOL LVOS_IfIpConflict(OSP_CHAR *v_pIpAddr1, OSP_CHAR * v_pNetMask1, 
                                OSP_CHAR *v_pIpAddr2, OSP_CHAR * v_pNetMask2);

/** \brief �Ƚ�����IPv6 �Ƿ��ͻ
    \param[in] IP��ַ1
    \param[in] ����
    \param[in] IP��ַ2
    \param[in] ����
    \retval TRUE  ��ͻ
    \retval FALSE ����ͻ
*/
OSP_BOOL LVOS_IfIpV6Conflict(OSP_CHAR *v_pIpAddr1, OSP_U32 v_uiPrefixLen1, 
                                   OSP_CHAR *v_pIpAddr2, OSP_U32 v_uiPrefixLen2);


/* R2 IPV6 added by f00004188 2011/03/01 begin */
#define LVOS_IN6_IS_ADDR_LINKLOCAL(a)       \
        ((((OSP_U8*)(a))[0] == 0xfe) && (((OSP_U8*)(a))[1] & 0xc0 == 0x80))

#define LVOS_IN6_IS_ADDR_SITELOCAL(a)        \
        ((((OSP_U8*)(a))[0] == 0xfe) && (((OSP_U8*)(a))[1] & 0xc0 == 0xc0))
     

#define LVOS_IN6_IS_ADDR_MULTICAST(a)        \
        (((OSP_U8*)(a))[0] == 0xff)

#define LVOS_IN6_IS_ADDR_LOOPBACK(a)         \
         ((*(OSP_U32 *)(&(a[0])) == 0) &&  \
           (*(OSP_U32 *)(&(a[4])) == 0) &&  \
           (*(OSP_U32 *)(&(a[8])) == 0) &&  \
           (*(OSP_U32 *)(&(a[12])) == 0x01000000))
           
#define LVOS_IN6_ARE_ADDR_EQUAL(a, b)                        \
        (memcmp((OSP_U8*)a, (OSP_U8*)b, sizeof(OSP_U8)*16) == 0)

#define LOVS_IN6_IS_ADDR_UNSPECIFIED(a)         \
        ((*(OSP_U32 *)(&(a[0])) == 0) &&    \
          (*(OSP_U32 *)(&(a[4])) == 0) &&     \
          (*(OSP_U32 *)(&(a[8])) == 0) &&    \
          (*(OSP_U32 *)(&(a[12])) == 0) )

/*suse ��IPV6������������*/
/*��Ч��IPV6���ص�ַ����߰�λ�Ķ���������(00100000-11011111)*/
#define LVOS_IN6_GW_ISVALID(a)                   \
        ((*(OSP_U8*)(&(a[0]))) >= 32 &&   \
        (*(OSP_U8*)(&(a[0]))) <= 223)

#if 1
 /**% INT16 Size */ 
 #define NS_INT16SZ   2  
 /**% IPv4 Address Size */ 
 #define NS_INADDRSZ  4  
 /**% IPv6 Address Size */ 
 #define NS_IN6ADDRSZ    16  

OSP_S32 LVOS_inet_pton4(const char *src, void *dst);     
OSP_S32 LVOS_inet_pton6(const char *src, void *dst);
OSP_S32 LVOS_inet_pton(int af, const char *src, void *dst);
#endif

#endif
/** @} */

