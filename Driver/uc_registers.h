#ifndef UC_REGISTERS_H
#define UC_REGISTERS_H

/**\file
 *
 * Device header abstraction file for Small System Architecture.
 *
 */

/*
 * Microcontroller header files. Please use correct one compilation switch
 * to include expected register definitions file(s).
 */

#ifdef __UCIO78F1804_30__
   #include "io78f1804_30.h"
   #include "io78f1804_30_ext.h"
#elif (defined __UCIO78F1804_32__)
   #include "io78f1804_32.h"
   #include "io78f1804_32_ext.h"
#elif (defined __UCIO78F1805_30__)
   #include "io78f1805_30.h"
   #include "io78f1805_30_ext.h"
#elif (defined __UCIO78F1805_32__)
   #include "io78f1805_32.h"
   #include "io78f1805_32_ext.h"
#elif (defined __UCIO78F1806_30__)
   #include "io78f1806_30.h"
   #include "io78f1806_30_ext.h"
#elif (defined __UCIO78F1806_32__)
   #include "io78f1806_32.h"
   #include "io78f1806_32_ext.h"
#elif (defined __UCIO78F1807_30__)
   #include "io78f1807_30.h"
   #include "io78f1807_30_ext.h"
#elif (defined __UCIO78F1807_32__)
   #include "io78f1807_32.h"
   #include "io78f1807_32_ext.h"
#elif (defined __UCIO78F1808__)
   #include "io78f1808_40.h"
   #include "io78f1808_40_ext.h"
#elif (defined __UCIO78F1809__)
   #include "io78f1809_40.h"
   #include "io78f1809_40_ext.h"
#elif (defined __UCIO78F1810__)
   #include "io78f1810_40.h"
   #include "io78f1810_40_ext.h"
#elif (defined __UCIO78F1811__)
   #include "io78f1811_40.h"
   #include "io78f1811_40_ext.h"
#elif (defined __UCIO78F1812__)
   #include "io78f1812_48.h"
   #include "io78f1812_48_ext.h"
#elif (defined __UCIO78F1813__)
   #include "io78f1813_48.h"
   #include "io78f1813_48_ext.h"
#elif (defined __UCIO78F1814__)
   #include "io78f1814_48.h"
   #include "io78f1814_48_ext.h"
#elif (defined __UCIO78F1815__)
   #include "io78f1815_48.h"
   #include "io78f1815_48_ext.h"
#elif (defined __UCIO78F1816__)
   #include "io78f1816_48.h"
   #include "io78f1816_48_ext.h"
#elif (defined __UCIO78F1817__)
   #include "io78f1817_48.h"
   #include "io78f1817_48_ext.h"
#elif (defined __UCIO78F1818__)
   #include "io78f1818_64.h"
   #include "io78f1818_64_ext.h"
#elif (defined __UCIO78F1819__)
   #include "io78f1819_64.h"
   #include "io78f1819_64_ext.h"
#elif (defined __UCIO78F1820__)
   #include "io78f1820_64.h"
   #include "io78f1820_64_ext.h"
#elif (defined __UCIO78F1821__)
   #include "io78f1821_64.h"
   #include "io78f1821_64_ext.h"
#elif (defined __UCIO78F1822__)
   #include "io78f1822_64.h"
   #include "io78f1822_64_ext.h"
#elif (defined __UCIO78F1823__)
   #include "io78f1823_80.h"
   #include "io78f1823_80_ext.h"
#elif (defined __UCIO78F1824__)
   #include "io78f1824_80.h"
   #include "io78f1824_80_ext.h"
#elif (defined __UCIO78F1825__)
   #include "io78f1825_80.h"
   #include "io78f1825_80_ext.h"
#elif (defined __UCIO78F1826__)
   #include "io78f1826_48.h"
   #include "io78f1826_48_ext.h"
#elif (defined __UCIO78F1827__)
   #include "io78f1827_48.h"
   #include "io78f1827_48_ext.h"
#elif (defined __UCIO78F1828__)
   #include "io78f1828_48.h"
   #include "io78f1828_48_ext.h"
#elif (defined __UCIO78F1829__)
   #include "io78f1829_48.h"
   #include "io78f1829_48_ext.h"
#elif (defined __UCIO78F1830__)
   #include "io78f1830_48.h"
   #include "io78f1830_48_ext.h"
#elif (defined __UCIO78F1831__)
   #include "io78f1831_64.h"
   #include "io78f1831_64_ext.h"
#elif (defined __UCIO78F1832__)
   #include "io78f1832_64.h"
   #include "io78f1832_64_ext.h"
#elif (defined __UCIO78F1833__)
   #include "io78f1833_64.h"
   #include "io78f1833_64_ext.h"
#elif (defined __UCIO78F1834__)
   #include "io78f1834_64.h"
   #include "io78f1834_64_ext.h"
#elif (defined __UCIO78F1835__)
   #include "io78f1835_64.h"
   #include "io78f1835_64_ext.h"
#elif (defined __UCIO78F1836__)
   #include "io78f1836_80.h"
   #include "io78f1836_80_ext.h"
#elif (defined __UCIO78F1837__)
   #include "io78f1837_80.h"
   #include "io78f1837_80_ext.h"
#elif (defined __UCIO78F1838__)
   #include "io78f1838_80.h"
   #include "io78f1838_80_ext.h"
#elif (defined __UCIO78F1839__)
   #include "io78f1839_80.h"
   #include "io78f1839_80_ext.h"
#elif (defined __UCIO78F1840__)
   #include "io78f1840_80.h"
   #include "io78f1840_80_ext.h"
#elif (defined __UCIO78F1841__)
   #include "io78f1841_a0.h"
   #include "io78f1841_a0_ext.h"
#elif (defined __UCIO78F1842__)
   #include "io78f1842_a0.h"
   #include "io78f1842_a0_ext.h"
#elif (defined __UCIO78F1843__)
   #include "io78f1843_a0.h"
   #include "io78f1843_a0_ext.h"
#elif (defined __UCIO78F1844__)
   #include "io78f1844_a0.h"
   #include "io78f1844_a0_ext.h"
#elif (defined __UCIO78F1845__)
   #include "io78f1845_a0.h"
   #include "io78f1845_a0_ext.h"
#elif (defined __UCIO78F1846__)
   #include "io78f1846_80.h"
   #include "io78f1846_80_ext.h"
#elif (defined __UCIO78F1847__)
   #include "io78f1847_80.h"
   #include "io78f1847_80_ext.h"
#elif (defined __UCIO78F1848__)
   #include "io78f1848_a0.h"
   #include "io78f1848_a0_ext.h"
#elif (defined __UCIO78F1849__)
   #include "io78f1849_a0.h"
   #include "io78f1849_a0_ext.h"
#else
   #error "Please specifiy the uC version in the makefile: -D__UCIO78F18xy__"
#endif

#endif   /* UC_REGISTERS_H */

