/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_mb.h
  �� �� ��   : ����
  ��    ��   : c90004010
  ��������   : 2013��07��31��
  ����޸�   :
  ��������   : �������ڴ����ϵ���غ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��07��31��
    ��    ��   : c90004010
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __LVOS_MB_H__
#define __LVOS_MB_H__

#if defined(WIN32) || defined(_PCLINT_)

/* ����������winodws��linux�²�һ�����������֤pclint��windows�µı���ͨ�� */

#define barrier MemoryBarrier
#define smp_mb MemoryBarrier
#define smp_rmb MemoryBarrier
#define smp_wmb MemoryBarrier
#define smp_read_barrier_depends MemoryBarrier
#define mb MemoryBarrier
#define rmb MemoryBarrier
#define wmb MemoryBarrier

#endif

#endif
