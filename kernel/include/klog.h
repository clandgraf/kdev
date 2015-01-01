/*
 *
 * File:    kernel/include/klog.h
 * Author:  Christoph Landgraf
 * Purpose: klog macros for logging in kernel
 *
 */


#ifndef KERNEL_KLOG_H_INCLUDED
#define KERNEL_KLOG_H_INCLUDED

#include <stdio.h>

#define klog_info(...) printf(__VA_ARGS__)

#ifdef KLOG_DEBUG
#define klog_debug(...) printf(__VA_ARGS__)
#else
#define klog_debug(...)
#endif

#endif
