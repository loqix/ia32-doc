/** @file */
#pragma once
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

/**
 * @defgroup INTEL_MANUAL \
 *           Intel Manual
 *
 * @remarks All references are based on <b>Intel(R) 64 and IA-32 architectures software developer's manual combined volumes:
 *          1, 2A, 2B, 2C, 2D, 3A, 3B, 3C, 3D, and 4</b> (May 2018).
 * @{
 */
/**
 * @defgroup CONTROL_REGISTERS \
 *           Control registers
 *
 * Control registers (CR0, CR1, CR2, CR3, and CR4) determine operating mode of the processor and the characteristics of the
 * currently executing task. These registers are 32 bits in all 32-bit modes and compatibility mode.
 * In 64-bit mode, control registers are expanded to 64 bits. The MOV CRn instructions are used to manipulate the register
 * bits. Operand-size prefixes for these instructions are ignored. The following is also true:
 * - The control registers can be read and loaded (or modified) using the move-to-or-from-control-registers forms of the
 * MOV instruction. In protected mode, the MOV instructions allow the control registers to be read or loaded (at privilege
 * level 0 only). This restriction means that application programs or operating-system procedures (running at privilege
 * levels 1, 2, or 3) are prevented from reading or loading the control registers.
 * - Bits 63:32 of CR0 and CR4 are reserved and must be written with zeros. Writing a nonzero value to any of the upper 32
 * bits results in a general-protection exception, \#GP(0).
 * - All 64 bits of CR2 are writable by software.
 * - Bits 51:40 of CR3 are reserved and must be 0.
 * - The MOV CRn instructions do not check that addresses written to CR2 and CR3 are within the linear-address or
 * physical-address limitations of the implementation.
 * - Register CR8 is available in 64-bit mode only. The control registers are summarized below, and each architecturally
 * defined control field in these control registers is described individually.
 * - CR0 - Contains system control flags that control operating mode and states of the processor.
 * - CR1 - Reserved.
 * - CR2 - Contains the page-fault linear address (the linear address that caused a page fault).
 * - CR3 - Contains the physical address of the base of the paging-structure hierarchy and two flags (PCD and PWT). Only
 * the most-significant bits (less the lower 12 bits) of the base address are specified; the lower 12 bits of the address
 * are assumed to be 0. The first paging structure must thus be aligned to a page (4-KByte) boundary. The PCD and PWT flags
 * control caching of that paging structure in the processor's internal data caches (they do not control TLB caching of
 * page-directory information). When using the physical address extension, the CR3 register contains the base address of
 * the page-directorypointer table. In IA-32e mode, the CR3 register contains the base address of the PML4 table.
 * - CR4 - Contains a group of flags that enable several architectural extensions, and indicate operating system or
 * executive support for specific processor capabilities.
 * - CR8 - Provides read and write access to the Task Priority Register (TPR). It specifies the priority threshold value
 * that operating systems use to control the priority class of external interrupts allowed to interrupt the processor. This
 * register is available only in 64-bit mode. However, interrupt filtering continues to apply in compatibility mode.
 *
 * @see Vol3A[2.5(CONTROL REGISTERS)] (reference)
 * @{
 */
typedef union
{
  struct
  {
    /**
     * @brief Protection Enable
     *
     * [Bit 0] Enables protected mode when set; enables real-address mode when clear. This flag does not enable paging
     * directly. It only enables segment-level protection. To enable paging, both the PE and PG flags must be set.
     *
     * @see Vol3A[9.9(Mode Switching)]
     */
    UINT64 ProtectionEnable                                        : 1;
#define CR0_PROTECTION_ENABLE_BIT                                    0
#define CR0_PROTECTION_ENABLE_MASK                                   0x01
#define CR0_PROTECTION_ENABLE(_)                                     (((_) >> 0) & 0x01)

    /**
     * @brief Monitor Coprocessor
     *
     * [Bit 1] Controls the interaction of the WAIT (or FWAIT) instruction with the TS flag (bit 3 of CR0). If the MP flag is
     * set, a WAIT instruction generates a device-not-available exception (\#NM) if the TS flag is also set. If the MP flag is
     * clear, the WAIT instruction ignores the setting of the TS flag.
     */
    UINT64 MonitorCoprocessor                                      : 1;
#define CR0_MONITOR_COPROCESSOR_BIT                                  1
#define CR0_MONITOR_COPROCESSOR_MASK                                 0x01
#define CR0_MONITOR_COPROCESSOR(_)                                   (((_) >> 1) & 0x01)

    /**
     * @brief FPU Emulation
     *
     * [Bit 2] Indicates that the processor does not have an internal or external x87 FPU when set; indicates an x87 FPU is
     * present when clear. This flag also affects the execution of MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instructions.
     * When the EM flag is set, execution of an x87 FPU instruction generates a device-not-available exception (\#NM). This
     * flag must be set when the processor does not have an internal x87 FPU or is not connected to an external math
     * coprocessor. Setting this flag forces all floating-point instructions to be handled by software emulation.
     * Also, when the EM flag is set, execution of an MMX instruction causes an invalid-opcode exception (\#UD) to be
     * generated. Thus, if an IA-32 or Intel 64 processor incorporates MMX technology, the EM flag must be set to 0 to enable
     * execution of MMX instructions. Similarly for SSE/SSE2/SSE3/SSSE3/SSE4 extensions, when the EM flag is set, execution of
     * most SSE/SSE2/SSE3/SSSE3/SSE4 instructions causes an invalid opcode exception (\#UD) to be generated. If an IA-32 or
     * Intel 64 processor incorporates the SSE/SSE2/SSE3/SSSE3/SSE4 extensions, the EM flag must be set to 0 to enable
     * execution of these extensions. SSE/SSE2/SSE3/SSSE3/SSE4 instructions not affected by the EM flag include: PAUSE,
     * PREFETCHh, SFENCE, LFENCE, MFENCE, MOVNTI, CLFLUSH, CRC32, and POPCNT.
     */
    UINT64 EmulateFpu                                              : 1;
#define CR0_EMULATE_FPU_BIT                                          2
#define CR0_EMULATE_FPU_MASK                                         0x01
#define CR0_EMULATE_FPU(_)                                           (((_) >> 2) & 0x01)

    /**
     * @brief Task Switched
     *
     * [Bit 3] Allows the saving of the x87 FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 context on a task switch to be delayed until an
     * x87 FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instruction is actually executed by the new task. The processor sets this flag on
     * every task switch and tests it when executing x87 FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instructions.
     * - If the TS flag is set and the EM flag (bit 2 of CR0) is clear, a device-not-available exception (\#NM) is raised prior
     * to the execution of any x87 FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instruction; with the exception of PAUSE, PREFETCHh,
     * SFENCE, LFENCE, MFENCE, MOVNTI, CLFLUSH, CRC32, and POPCNT.
     * - If the TS flag is set and the MP flag (bit 1 of CR0) and EM flag are clear, an \#NM exception is not raised prior to
     * the execution of an x87 FPU WAIT/FWAIT instruction.
     * - If the EM flag is set, the setting of the TS flag has no effect on the execution of x87
     * FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instructions.
     *   The processor does not automatically save the context of the x87 FPU, XMM, and MXCSR registers on a task switch.
     *   Instead, it sets the TS flag, which causes the processor to raise an \#NM exception whenever it encounters an x87
     *   FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instruction in the instruction stream for the new task (with the exception of the
     *   instructions listed above).
     *   The fault handler for the \#NM exception can then be used to clear the TS flag (with the CLTS instruction) and save
     *   the context of the x87 FPU, XMM, and MXCSR registers. If the task never encounters an x87
     *   FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 instruction, the x87 FPU/MMX/SSE/SSE2/SSE3/SSSE3/SSE4 context is never saved.
     */
    UINT64 TaskSwitched                                            : 1;
#define CR0_TASK_SWITCHED_BIT                                        3
#define CR0_TASK_SWITCHED_MASK                                       0x01
#define CR0_TASK_SWITCHED(_)                                         (((_) >> 3) & 0x01)

    /**
     * @brief Extension Type
     *
     * [Bit 4] Reserved in the Pentium 4, Intel Xeon, P6 family, and Pentium processors. In the Pentium 4, Intel Xeon, and P6
     * family processors, this flag is hardcoded to 1. In the Intel386 and Intel486 processors, this flag indicates support of
     * Intel 387 DX math coprocessor instructions when set.
     */
    UINT64 ExtensionType                                           : 1;
#define CR0_EXTENSION_TYPE_BIT                                       4
#define CR0_EXTENSION_TYPE_MASK                                      0x01
#define CR0_EXTENSION_TYPE(_)                                        (((_) >> 4) & 0x01)

    /**
     * @brief Numeric Error
     *
     * [Bit 5] Enables the native (internal) mechanism for reporting x87 FPU errors when set; enables the PC-style x87 FPU
     * error reporting mechanism when clear. When the NE flag is clear and the IGNNE\# input is asserted, x87 FPU errors are
     * ignored. When the NE flag is clear and the IGNNE\# input is deasserted, an unmasked x87 FPU error causes the processor
     * to assert the FERR\# pin to generate an external interrupt and to stop instruction execution immediately before
     * executing the next waiting floating-point instruction or WAIT/FWAIT instruction.
     * The FERR\# pin is intended to drive an input to an external interrupt controller (the FERR\# pin emulates the ERROR\#
     * pin of the Intel 287 and Intel 387 DX math coprocessors). The NE flag, IGNNE\# pin, and FERR\# pin are used with
     * external logic to implement PC-style error reporting. Using FERR\# and IGNNE\# to handle floating-point exceptions is
     * deprecated by modern operating systems; this non-native approach also limits newer processors to operate with one
     * logical processor active.
     *
     * @see Vol1[8.7(Handling x87 FPU Exceptions in Software)]
     * @see Vol1[A.1(APPENDIX A | EFLAGS Cross-Reference)]
     */
    UINT64 NumericError                                            : 1;
#define CR0_NUMERIC_ERROR_BIT                                        5
#define CR0_NUMERIC_ERROR_MASK                                       0x01
#define CR0_NUMERIC_ERROR(_)                                         (((_) >> 5) & 0x01)
    UINT64 Reserved1                                               : 10;

    /**
     * @brief Write Protect
     *
     * [Bit 16] When set, inhibits supervisor-level procedures from writing into readonly pages; when clear, allows
     * supervisor-level procedures to write into read-only pages (regardless of the U/S bit setting). This flag facilitates
     * implementation of the copy-onwrite method of creating a new process (forking) used by operating systems such as UNIX.
     *
     * @see Vol3A[4.1.3(Paging-Mode Modifiers)]
     * @see Vol3A[4.6(ACCESS RIGHTS)]
     */
    UINT64 WriteProtect                                            : 1;
#define CR0_WRITE_PROTECT_BIT                                        16
#define CR0_WRITE_PROTECT_MASK                                       0x01
#define CR0_WRITE_PROTECT(_)                                         (((_) >> 16) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief Alignment Mask
     *
     * [Bit 18] Enables automatic alignment checking when set; disables alignment checking when clear. Alignment checking is
     * performed only when the AM flag is set, the AC flag in the EFLAGS register is set, CPL is 3, and the processor is
     * operating in either protected or virtual-8086 mode.
     */
    UINT64 AlignmentMask                                           : 1;
#define CR0_ALIGNMENT_MASK_BIT                                       18
#define CR0_ALIGNMENT_MASK_MASK                                      0x01
#define CR0_ALIGNMENT_MASK(_)                                        (((_) >> 18) & 0x01)
    UINT64 Reserved3                                               : 10;

    /**
     * @brief Not Write-through
     *
     * [Bit 29] When the NW and CD flags are clear, write-back (for Pentium 4, Intel Xeon, P6 family, and Pentium processors)
     * or write-through (for Intel486 processors) is enabled for writes that hit the cache and invalidation cycles are enabled.
     */
    UINT64 NotWriteThrough                                         : 1;
#define CR0_NOT_WRITE_THROUGH_BIT                                    29
#define CR0_NOT_WRITE_THROUGH_MASK                                   0x01
#define CR0_NOT_WRITE_THROUGH(_)                                     (((_) >> 29) & 0x01)

    /**
     * @brief Cache Disable
     *
     * [Bit 30] When the CD and NW flags are clear, caching of memory locations for the whole of physical memory in the
     * processor's internal (and external) caches is enabled. When the CD flag is set, caching is restricted. To prevent the
     * processor from accessing and updating its caches, the CD flag must be set and the caches must be invalidated so that no
     * cache hits can occur.
     *
     * @see Vol3A[11.5.3(Preventing Caching)]
     * @see Vol3A[11.5(CACHE CONTROL)]
     */
    UINT64 CacheDisable                                            : 1;
#define CR0_CACHE_DISABLE_BIT                                        30
#define CR0_CACHE_DISABLE_MASK                                       0x01
#define CR0_CACHE_DISABLE(_)                                         (((_) >> 30) & 0x01)

    /**
     * @brief Paging Enable
     *
     * [Bit 31] Enables paging when set; disables paging when clear. When paging is disabled, all linear addresses are treated
     * as physical addresses. The PG flag has no effect if the PE flag (bit 0 of register CR0) is not also set; setting the PG
     * flag when the PE flag is clear causes a general-protection exception (\#GP).
     * On Intel 64 processors, enabling and disabling IA-32e mode operation also requires modifying CR0.PG.
     *
     * @see Vol3A[4(PAGING)]
     */
    UINT64 PagingEnable                                            : 1;
#define CR0_PAGING_ENABLE_BIT                                        31
#define CR0_PAGING_ENABLE_MASK                                       0x01
#define CR0_PAGING_ENABLE(_)                                         (((_) >> 31) & 0x01)
    UINT64 Reserved4                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR0;

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 3;

    /**
     * @brief Page-level Write-Through
     *
     * [Bit 3] Controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
     * This bit is not used if paging is disabled, with PAE paging, or with 4-level paging if CR4.PCIDE=1.
     *
     * @see Vol3A[4.9(PAGING AND MEMORY TYPING)]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define CR3_PAGE_LEVEL_WRITE_THROUGH_BIT                             3
#define CR3_PAGE_LEVEL_WRITE_THROUGH_MASK                            0x01
#define CR3_PAGE_LEVEL_WRITE_THROUGH(_)                              (((_) >> 3) & 0x01)

    /**
     * @brief Page-level Cache Disable
     *
     * [Bit 4] Controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
     * This bit is not used if paging is disabled, with PAE paging, or with 4-level paging2 if CR4.PCIDE=1.
     *
     * @see Vol3A[4.9(PAGING AND MEMORY TYPING)]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define CR3_PAGE_LEVEL_CACHE_DISABLE_BIT                             4
#define CR3_PAGE_LEVEL_CACHE_DISABLE_MASK                            0x01
#define CR3_PAGE_LEVEL_CACHE_DISABLE(_)                              (((_) >> 4) & 0x01)
    UINT64 Reserved2                                               : 7;

    /**
     * @brief Address of page directory
     *
     * [Bits 47:12] Physical address of the 4-KByte aligned page directory (32-bit paging) or PML4 table (64-bit paging) used
     * for linear-address translation.
     *
     * @see Vol3A[4.3(32-BIT PAGING)]
     * @see Vol3A[4.5(4-LEVEL PAGING)]
     */
    UINT64 AddressOfPageDirectory                                  : 36;
#define CR3_ADDRESS_OF_PAGE_DIRECTORY_BIT                            12
#define CR3_ADDRESS_OF_PAGE_DIRECTORY_MASK                           0xFFFFFFFFF
#define CR3_ADDRESS_OF_PAGE_DIRECTORY(_)                             (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved3                                               : 16;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR3;

typedef union
{
  struct
  {
    /**
     * @brief Virtual-8086 Mode Extensions
     *
     * [Bit 0] Enables interrupt- and exception-handling extensions in virtual-8086 mode when set; disables the extensions when
     * clear. Use of the virtual mode extensions can improve the performance of virtual-8086 applications by eliminating the
     * overhead of calling the virtual- 8086 monitor to handle interrupts and exceptions that occur while executing an 8086
     * program and, instead, redirecting the interrupts and exceptions back to the 8086 program's handlers. It also provides
     * hardware support for a virtual interrupt flag (VIF) to improve reliability of running 8086 programs in multitasking and
     * multiple-processor environments.
     *
     * @see Vol3B[20.3(INTERRUPT AND EXCEPTION HANDLING IN VIRTUAL-8086 MODE)]
     */
    UINT64 VirtualModeExtensions                                   : 1;
#define CR4_VIRTUAL_MODE_EXTENSIONS_BIT                              0
#define CR4_VIRTUAL_MODE_EXTENSIONS_MASK                             0x01
#define CR4_VIRTUAL_MODE_EXTENSIONS(_)                               (((_) >> 0) & 0x01)

    /**
     * @brief Protected-Mode Virtual Interrupts
     *
     * [Bit 1] Enables hardware support for a virtual interrupt flag (VIF) in protected mode when set; disables the VIF flag in
     * protected mode when clear.
     *
     * @see Vol3B[20.4(PROTECTED-MODE VIRTUAL INTERRUPTS)]
     */
    UINT64 ProtectedModeVirtualInterrupts                          : 1;
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS_BIT                    1
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS_MASK                   0x01
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS(_)                     (((_) >> 1) & 0x01)

    /**
     * @brief Time Stamp Disable
     *
     * [Bit 2] Restricts the execution of the RDTSC instruction to procedures running at privilege level 0 when set; allows
     * RDTSC instruction to be executed at any privilege level when clear. This bit also applies to the RDTSCP instruction if
     * supported (if CPUID.80000001H:EDX[27] = 1).
     */
    UINT64 TimestampDisable                                        : 1;
#define CR4_TIMESTAMP_DISABLE_BIT                                    2
#define CR4_TIMESTAMP_DISABLE_MASK                                   0x01
#define CR4_TIMESTAMP_DISABLE(_)                                     (((_) >> 2) & 0x01)

    /**
     * @brief Debugging Extensions
     *
     * [Bit 3] References to debug registers DR4 and DR5 cause an undefined opcode (\#UD) exception to be generated when set;
     * when clear, processor aliases references to registers DR4 and DR5 for compatibility with software written to run on
     * earlier IA-32 processors.
     *
     * @see Vol3B[17.2.2(Debug Registers DR4 and DR5)]
     */
    UINT64 DebuggingExtensions                                     : 1;
#define CR4_DEBUGGING_EXTENSIONS_BIT                                 3
#define CR4_DEBUGGING_EXTENSIONS_MASK                                0x01
#define CR4_DEBUGGING_EXTENSIONS(_)                                  (((_) >> 3) & 0x01)

    /**
     * @brief Page Size Extensions
     *
     * [Bit 4] Enables 4-MByte pages with 32-bit paging when set; restricts 32-bit paging to pages of 4 KBytes when clear.
     *
     * @see Vol3A[4.3(32-BIT PAGING)]
     */
    UINT64 PageSizeExtensions                                      : 1;
#define CR4_PAGE_SIZE_EXTENSIONS_BIT                                 4
#define CR4_PAGE_SIZE_EXTENSIONS_MASK                                0x01
#define CR4_PAGE_SIZE_EXTENSIONS(_)                                  (((_) >> 4) & 0x01)

    /**
     * @brief Physical Address Extension
     *
     * [Bit 5] When set, enables paging to produce physical addresses with more than 32 bits. When clear, restricts physical
     * addresses to 32 bits. PAE must be set before entering IA-32e mode.
     *
     * @see Vol3A[4(PAGING)]
     */
    UINT64 PhysicalAddressExtension                                : 1;
#define CR4_PHYSICAL_ADDRESS_EXTENSION_BIT                           5
#define CR4_PHYSICAL_ADDRESS_EXTENSION_MASK                          0x01
#define CR4_PHYSICAL_ADDRESS_EXTENSION(_)                            (((_) >> 5) & 0x01)

    /**
     * @brief Machine-Check Enable
     *
     * [Bit 6] Enables the machine-check exception when set; disables the machine-check exception when clear.
     *
     * @see Vol3B[15(MACHINE-CHECK ARCHITECTURE)]
     */
    UINT64 MachineCheckEnable                                      : 1;
#define CR4_MACHINE_CHECK_ENABLE_BIT                                 6
#define CR4_MACHINE_CHECK_ENABLE_MASK                                0x01
#define CR4_MACHINE_CHECK_ENABLE(_)                                  (((_) >> 6) & 0x01)

    /**
     * @brief Page Global Enable
     *
     * [Bit 7] (Introduced in the P6 family processors.) Enables the global page feature when set; disables the global page
     * feature when clear. The global page feature allows frequently used or shared pages to be marked as global to all users
     * (done with the global flag, bit 8, in a page-directory or page-table entry). Global pages are not flushed from the
     * translation-lookaside buffer (TLB) on a task switch or a write to register CR3. When enabling the global page feature,
     * paging must be enabled (by setting the PG flag in control register CR0) before the PGE flag is set. Reversing this
     * sequence may affect program correctness, and processor performance will be impacted.
     *
     * @see Vol3A[4.10(CACHING TRANSLATION INFORMATION)]
     */
    UINT64 PageGlobalEnable                                        : 1;
#define CR4_PAGE_GLOBAL_ENABLE_BIT                                   7
#define CR4_PAGE_GLOBAL_ENABLE_MASK                                  0x01
#define CR4_PAGE_GLOBAL_ENABLE(_)                                    (((_) >> 7) & 0x01)

    /**
     * @brief Performance-Monitoring Counter Enable
     *
     * [Bit 8] Enables execution of the RDPMC instruction for programs or procedures running at any protection level when set;
     * RDPMC instruction can be executed only at protection level 0 when clear.
     */
    UINT64 PerformanceMonitoringCounterEnable                      : 1;
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE_BIT                8
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE_MASK               0x01
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE(_)                 (((_) >> 8) & 0x01)

    /**
     * @brief Operating System Support for FXSAVE and FXRSTOR instructions
     *
     * [Bit 9] When set, this flag:
     * -# indicates to software that the operating system supports the use of the FXSAVE and FXRSTOR instructions,
     * -# enables the FXSAVE and FXRSTOR instructions to save and restore the contents of the XMM and MXCSR registers along
     * with the contents of the x87 FPU and MMX registers, and
     * -# enables the processor to execute SSE/SSE2/SSE3/SSSE3/SSE4 instructions, with the exception of the PAUSE, PREFETCHh,
     * SFENCE, LFENCE, MFENCE, MOVNTI, CLFLUSH, CRC32, and POPCNT.
     * If this flag is clear, the FXSAVE and FXRSTOR instructions will save and restore the contents of the x87 FPU and MMX
     * registers, but they may not save and restore the contents of the XMM and MXCSR registers. Also, the processor will
     * generate an invalid opcode exception (\#UD) if it attempts to execute any SSE/SSE2/SSE3 instruction, with the exception
     * of PAUSE, PREFETCHh, SFENCE, LFENCE, MFENCE, MOVNTI, CLFLUSH, CRC32, and POPCNT. The operating system or executive must
     * explicitly set this flag.
     *
     * @remarks CPUID feature flag FXSR indicates availability of the FXSAVE/FXRSTOR instructions. The OSFXSR bit provides
     *          operating system software with a means of enabling FXSAVE/FXRSTOR to save/restore the contents of the X87 FPU, XMM and
     *          MXCSR registers. Consequently OSFXSR bit indicates that the operating system provides context switch support for
     *          SSE/SSE2/SSE3/SSSE3/SSE4.
     */
    UINT64 OsFxsaveFxrstorSupport                                  : 1;
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT_BIT                            9
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT_MASK                           0x01
#define CR4_OS_FXSAVE_FXRSTOR_SUPPORT(_)                             (((_) >> 9) & 0x01)

    /**
     * @brief Operating System Support for Unmasked SIMD Floating-Point Exceptions
     *
     * [Bit 10] Operating System Support for Unmasked SIMD Floating-Point Exceptions - When set, indicates that the operating
     * system supports the handling of unmasked SIMD floating-point exceptions through an exception handler that is invoked
     * when a SIMD floating-point exception (\#XM) is generated. SIMD floating-point exceptions are only generated by
     * SSE/SSE2/SSE3/SSE4.1 SIMD floatingpoint instructions.
     * The operating system or executive must explicitly set this flag. If this flag is not set, the processor will generate an
     * invalid opcode exception (\#UD) whenever it detects an unmasked SIMD floating-point exception.
     */
    UINT64 OsXmmExceptionSupport                                   : 1;
#define CR4_OS_XMM_EXCEPTION_SUPPORT_BIT                             10
#define CR4_OS_XMM_EXCEPTION_SUPPORT_MASK                            0x01
#define CR4_OS_XMM_EXCEPTION_SUPPORT(_)                              (((_) >> 10) & 0x01)

    /**
     * @brief User-Mode Instruction Prevention
     *
     * [Bit 11] When set, the following instructions cannot be executed if CPL > 0: SGDT, SIDT, SLDT, SMSW, and STR. An attempt
     * at such execution causes a generalprotection exception (\#GP).
     */
    UINT64 UsermodeInstructionPrevention                           : 1;
#define CR4_USERMODE_INSTRUCTION_PREVENTION_BIT                      11
#define CR4_USERMODE_INSTRUCTION_PREVENTION_MASK                     0x01
#define CR4_USERMODE_INSTRUCTION_PREVENTION(_)                       (((_) >> 11) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * @brief VMX-Enable
     *
     * [Bit 13] Enables VMX operation when set.
     *
     * @see Vol3C[23(INTRODUCTION TO VIRTUAL MACHINE EXTENSIONS)]
     */
    UINT64 VmxEnable                                               : 1;
#define CR4_VMX_ENABLE_BIT                                           13
#define CR4_VMX_ENABLE_MASK                                          0x01
#define CR4_VMX_ENABLE(_)                                            (((_) >> 13) & 0x01)

    /**
     * @brief SMX-Enable
     *
     * [Bit 14] Enables SMX operation when set.
     *
     * @see Vol2[6(SAFER MODE EXTENSIONS REFERENCE)]
     */
    UINT64 SmxEnable                                               : 1;
#define CR4_SMX_ENABLE_BIT                                           14
#define CR4_SMX_ENABLE_MASK                                          0x01
#define CR4_SMX_ENABLE(_)                                            (((_) >> 14) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief FSGSBASE-Enable
     *
     * [Bit 16] Enables the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE.
     */
    UINT64 FsgsbaseEnable                                          : 1;
#define CR4_FSGSBASE_ENABLE_BIT                                      16
#define CR4_FSGSBASE_ENABLE_MASK                                     0x01
#define CR4_FSGSBASE_ENABLE(_)                                       (((_) >> 16) & 0x01)

    /**
     * @brief PCID-Enable
     *
     * [Bit 17] Enables process-context identifiers (PCIDs) when set. Can be set only in IA-32e mode (if IA32_EFER.LMA = 1).
     *
     * @see Vol3A[4.10.1(Process-Context Identifiers (PCIDs))]
     */
    UINT64 PcidEnable                                              : 1;
#define CR4_PCID_ENABLE_BIT                                          17
#define CR4_PCID_ENABLE_MASK                                         0x01
#define CR4_PCID_ENABLE(_)                                           (((_) >> 17) & 0x01)

    /**
     * @brief XSAVE and Processor Extended States-Enable
     *
     * [Bit 18] When set, this flag:
     * -# indicates (via CPUID.01H:ECX.OSXSAVE[bit 27]) that the operating system supports the use of the XGETBV, XSAVE and
     * XRSTOR instructions by general software;
     * -# enables the XSAVE and XRSTOR instructions to save and restore the x87 FPU state (including MMX registers), the SSE
     * state (XMM registers and MXCSR), along with other processor extended states enabled in XCR0;
     * -# enables the processor to execute XGETBV and XSETBV instructions in order to read and write XCR0.
     *
     * @see Vol3A[2.6(EXTENDED CONTROL REGISTERS (INCLUDING XCR0))]
     * @see Vol3A[13(SYSTEM PROGRAMMING FOR INSTRUCTION SET EXTENSIONS AND PROCESSOR EXTENDED)]
     */
    UINT64 OsXsave                                                 : 1;
#define CR4_OS_XSAVE_BIT                                             18
#define CR4_OS_XSAVE_MASK                                            0x01
#define CR4_OS_XSAVE(_)                                              (((_) >> 18) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * @brief SMEP-Enable
     *
     * [Bit 20] Enables supervisor-mode execution prevention (SMEP) when set.
     *
     * @see Vol3A[4.6(ACCESS RIGHTS)]
     */
    UINT64 SmepEnable                                              : 1;
#define CR4_SMEP_ENABLE_BIT                                          20
#define CR4_SMEP_ENABLE_MASK                                         0x01
#define CR4_SMEP_ENABLE(_)                                           (((_) >> 20) & 0x01)

    /**
     * @brief SMAP-Enable
     *
     * [Bit 21] Enables supervisor-mode access prevention (SMAP) when set.
     *
     * @see Vol3A[4.6(ACCESS RIGHTS)]
     */
    UINT64 SmapEnable                                              : 1;
#define CR4_SMAP_ENABLE_BIT                                          21
#define CR4_SMAP_ENABLE_MASK                                         0x01
#define CR4_SMAP_ENABLE(_)                                           (((_) >> 21) & 0x01)

    /**
     * @brief Protection-Key-Enable
     *
     * [Bit 22] Enables 4-level paging to associate each linear address with a protection key. The PKRU register specifies, for
     * each protection key, whether user-mode linear addresses with that protection key can be read or written. This bit also
     * enables access to the PKRU register using the RDPKRU and WRPKRU instructions.
     */
    UINT64 ProtectionKeyEnable                                     : 1;
#define CR4_PROTECTION_KEY_ENABLE_BIT                                22
#define CR4_PROTECTION_KEY_ENABLE_MASK                               0x01
#define CR4_PROTECTION_KEY_ENABLE(_)                                 (((_) >> 22) & 0x01)
    UINT64 Reserved4                                               : 41;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR4;

typedef union
{
  struct
  {
    /**
     * @brief Task Priority Level
     *
     * [Bits 3:0] This sets the threshold value corresponding to the highestpriority interrupt to be blocked. A value of 0
     * means all interrupts are enabled. This field is available in 64- bit mode. A value of 15 means all interrupts will be
     * disabled.
     */
    UINT64 TaskPriorityLevel                                       : 4;
#define CR8_TASK_PRIORITY_LEVEL_BIT                                  0
#define CR8_TASK_PRIORITY_LEVEL_MASK                                 0x0F
#define CR8_TASK_PRIORITY_LEVEL(_)                                   (((_) >> 0) & 0x0F)

    /**
     * @brief Reserved
     *
     * [Bits 63:4] Reserved and must be written with zeros. Failure to do this causes a general-protection exception.
     */
    UINT64 Reserved                                                : 60;
#define CR8_RESERVED_BIT                                             4
#define CR8_RESERVED_MASK                                            0xFFFFFFFFFFFFFFF
#define CR8_RESERVED(_)                                              (((_) >> 4) & 0xFFFFFFFFFFFFFFF)
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR8;

/**
 * @}
 */

/**
 * @defgroup CPUID \
 *           CPUID
 *
 * @see Vol2A[3.2(CPUID)] (reference)
 * @{
 */
/**
 * @brief Returns CPUID's Highest Value for Basic Processor Information and the Vendor Identification String
 *
 * When CPUID executes with EAX set to 0, the processor returns the highest value the CPUID recognizes for returning basic
 * processor information. The value is returned in the EAX register and is processor specific.
 * A vendor identification string is also returned in EBX, EDX, and ECX. For Intel processors, the string is "GenuineIntel"
 * and is expressed:
 * - EBX <- 756e6547h (* "Genu", with G in the low eight bits of BL *)
 * - EDX <- 49656e69h (* "ineI", with i in the low eight bits of DL *)
 * - ECX <- 6c65746eh (* "ntel", with n in the low eight bits of CL *)
 */
typedef struct
{
  UINT32 MaxCpuidInputValue;
  UINT32 EbxValueGenu;
  UINT32 EcxValueNtel;
  UINT32 EdxValueInei;
} CPUID_EAX_00;

/**
 * @brief Returns Model, Family, Stepping Information, Additional Information and Feature Information
 *
 * Returns:
 *   * Model, Family, Stepping Information in EAX
 *   * Additional Information in EBX
 *   * Feature Information in ECX and EDX
 */
typedef struct
{
  /**
   * @brief When CPUID executes with EAX set to 01H, version information is returned in EAX
   */
  union
  {
    struct
    {
      UINT32 SteppingId                                            : 4;
#define CPUID_VERSION_INFORMATION_STEPPING_ID_BIT                    0
#define CPUID_VERSION_INFORMATION_STEPPING_ID_MASK                   0x0F
#define CPUID_VERSION_INFORMATION_STEPPING_ID(_)                     (((_) >> 0) & 0x0F)
      UINT32 Model                                                 : 4;
#define CPUID_VERSION_INFORMATION_MODEL_BIT                          4
#define CPUID_VERSION_INFORMATION_MODEL_MASK                         0x0F
#define CPUID_VERSION_INFORMATION_MODEL(_)                           (((_) >> 4) & 0x0F)
      UINT32 FamilyId                                              : 4;
#define CPUID_VERSION_INFORMATION_FAMILY_ID_BIT                      8
#define CPUID_VERSION_INFORMATION_FAMILY_ID_MASK                     0x0F
#define CPUID_VERSION_INFORMATION_FAMILY_ID(_)                       (((_) >> 8) & 0x0F)

      /**
       * [Bits 13:12] - 0 - Original OEM Processor
       * - 1 - Intel OverDrive(R) Processor
       * - 2 - Dual processor (not applicable to Intel486 processors)
       * - 3 - Intel reserved
       */
      UINT32 ProcessorType                                         : 2;
#define CPUID_VERSION_INFORMATION_PROCESSOR_TYPE_BIT                 12
#define CPUID_VERSION_INFORMATION_PROCESSOR_TYPE_MASK                0x03
#define CPUID_VERSION_INFORMATION_PROCESSOR_TYPE(_)                  (((_) >> 12) & 0x03)
      UINT32 Reserved1                                             : 2;

      /**
       * [Bits 19:16] The Extended Model ID needs to be examined only when the Family ID is 06H or 0FH.
       */
      UINT32 ExtendedModelId                                       : 4;
#define CPUID_VERSION_INFORMATION_EXTENDED_MODEL_ID_BIT              16
#define CPUID_VERSION_INFORMATION_EXTENDED_MODEL_ID_MASK             0x0F
#define CPUID_VERSION_INFORMATION_EXTENDED_MODEL_ID(_)               (((_) >> 16) & 0x0F)

      /**
       * [Bits 27:20] The Extended Family ID needs to be examined only when the Family ID is 0FH.
       */
      UINT32 ExtendedFamilyId                                      : 8;
#define CPUID_VERSION_INFORMATION_EXTENDED_FAMILY_ID_BIT             20
#define CPUID_VERSION_INFORMATION_EXTENDED_FAMILY_ID_MASK            0xFF
#define CPUID_VERSION_INFORMATION_EXTENDED_FAMILY_ID(_)              (((_) >> 20) & 0xFF)
      UINT32 Reserved2                                             : 4;
    };

    UINT32 Flags;
  } CpuidVersionInformation;

  /**
   * @brief When CPUID executes with EAX set to 01H, additional information is returned to the EBX register
   */
  struct
  {
    UINT8 BrandIndex;
    UINT8 ClflushLineSize;
    UINT8 MaxAddressableIds;
    UINT8 InitialApicId;
  } CpuidAdditionalInformation;

  /**
   * @brief When CPUID executes with EAX set to 01H, feature information is returned in ECX and EDX
   */
  union
  {
    struct
    {
      /**
       * @brief Streaming SIMD Extensions 3 (SSE3)
       *
       * [Bit 0] A value of 1 indicates the processor supports this technology.
       */
      UINT32 StreamingSimdExtensions3                              : 1;
#define CPUID_FEATURE_INFORMATION_ECX_STREAMING_SIMD_EXTENSIONS_3_BIT 0
#define CPUID_FEATURE_INFORMATION_ECX_STREAMING_SIMD_EXTENSIONS_3_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_STREAMING_SIMD_EXTENSIONS_3(_) (((_) >> 0) & 0x01)

      /**
       * @brief PCLMULQDQ instruction
       *
       * [Bit 1] A value of 1 indicates the processor supports the PCLMULQDQ instruction.
       */
      UINT32 PclmulqdqInstruction                                  : 1;
#define CPUID_FEATURE_INFORMATION_ECX_PCLMULQDQ_INSTRUCTION_BIT      1
#define CPUID_FEATURE_INFORMATION_ECX_PCLMULQDQ_INSTRUCTION_MASK     0x01
#define CPUID_FEATURE_INFORMATION_ECX_PCLMULQDQ_INSTRUCTION(_)       (((_) >> 1) & 0x01)

      /**
       * @brief 64-bit DS Area
       *
       * [Bit 2] A value of 1 indicates the processor supports DS area using 64-bit layout.
       */
      UINT32 DsArea64BitLayout                                     : 1;
#define CPUID_FEATURE_INFORMATION_ECX_DS_AREA_64BIT_LAYOUT_BIT       2
#define CPUID_FEATURE_INFORMATION_ECX_DS_AREA_64BIT_LAYOUT_MASK      0x01
#define CPUID_FEATURE_INFORMATION_ECX_DS_AREA_64BIT_LAYOUT(_)        (((_) >> 2) & 0x01)

      /**
       * @brief MONITOR/MWAIT instruction
       *
       * [Bit 3] A value of 1 indicates the processor supports this feature.
       */
      UINT32 MonitorMwaitInstruction                               : 1;
#define CPUID_FEATURE_INFORMATION_ECX_MONITOR_MWAIT_INSTRUCTION_BIT  3
#define CPUID_FEATURE_INFORMATION_ECX_MONITOR_MWAIT_INSTRUCTION_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_MONITOR_MWAIT_INSTRUCTION(_)   (((_) >> 3) & 0x01)

      /**
       * @brief CPL Qualified Debug Store
       *
       * [Bit 4] A value of 1 indicates the processor supports the extensions to the Debug Store feature to allow for branch
       * message storage qualified by CPL.
       */
      UINT32 CplQualifiedDebugStore                                : 1;
#define CPUID_FEATURE_INFORMATION_ECX_CPL_QUALIFIED_DEBUG_STORE_BIT  4
#define CPUID_FEATURE_INFORMATION_ECX_CPL_QUALIFIED_DEBUG_STORE_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_CPL_QUALIFIED_DEBUG_STORE(_)   (((_) >> 4) & 0x01)

      /**
       * @brief Virtual Machine Extensions
       *
       * [Bit 5] A value of 1 indicates that the processor supports this technology.
       */
      UINT32 VirtualMachineExtensions                              : 1;
#define CPUID_FEATURE_INFORMATION_ECX_VIRTUAL_MACHINE_EXTENSIONS_BIT 5
#define CPUID_FEATURE_INFORMATION_ECX_VIRTUAL_MACHINE_EXTENSIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_VIRTUAL_MACHINE_EXTENSIONS(_)  (((_) >> 5) & 0x01)

      /**
       * @brief Safer Mode Extensions
       *
       * [Bit 6] A value of 1 indicates that the processor supports this technology.
       *
       * @see Vol2[6(SAFER MODE EXTENSIONS REFERENCE)]
       */
      UINT32 SaferModeExtensions                                   : 1;
#define CPUID_FEATURE_INFORMATION_ECX_SAFER_MODE_EXTENSIONS_BIT      6
#define CPUID_FEATURE_INFORMATION_ECX_SAFER_MODE_EXTENSIONS_MASK     0x01
#define CPUID_FEATURE_INFORMATION_ECX_SAFER_MODE_EXTENSIONS(_)       (((_) >> 6) & 0x01)

      /**
       * @brief Enhanced Intel SpeedStep(R) technology
       *
       * [Bit 7] A value of 1 indicates that the processor supports this technology.
       */
      UINT32 EnhancedIntelSpeedstepTechnology                      : 1;
#define CPUID_FEATURE_INFORMATION_ECX_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY_BIT 7
#define CPUID_FEATURE_INFORMATION_ECX_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY(_) (((_) >> 7) & 0x01)

      /**
       * @brief Thermal Monitor 2
       *
       * [Bit 8] A value of 1 indicates whether the processor supports this technology.
       */
      UINT32 ThermalMonitor2                                       : 1;
#define CPUID_FEATURE_INFORMATION_ECX_THERMAL_MONITOR_2_BIT          8
#define CPUID_FEATURE_INFORMATION_ECX_THERMAL_MONITOR_2_MASK         0x01
#define CPUID_FEATURE_INFORMATION_ECX_THERMAL_MONITOR_2(_)           (((_) >> 8) & 0x01)

      /**
       * @brief Supplemental Streaming SIMD Extensions 3 (SSSE3)
       *
       * [Bit 9] A value of 1 indicates the presence of the Supplemental Streaming SIMD Extensions 3 (SSSE3). A value of 0
       * indicates the instruction extensions are not present in the processor.
       */
      UINT32 SupplementalStreamingSimdExtensions3                  : 1;
#define CPUID_FEATURE_INFORMATION_ECX_SUPPLEMENTAL_STREAMING_SIMD_EXTENSIONS_3_BIT 9
#define CPUID_FEATURE_INFORMATION_ECX_SUPPLEMENTAL_STREAMING_SIMD_EXTENSIONS_3_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_SUPPLEMENTAL_STREAMING_SIMD_EXTENSIONS_3(_) (((_) >> 9) & 0x01)

      /**
       * @brief L1 Context ID
       *
       * [Bit 10] A value of 1 indicates the L1 data cache mode can be set to either adaptive mode or shared mode. A value of 0
       * indicates this feature is not supported. See definition of the IA32_MISC_ENABLE MSR Bit 24 (L1 Data Cache Context Mode)
       * for details.
       */
      UINT32 L1ContextId                                           : 1;
#define CPUID_FEATURE_INFORMATION_ECX_L1_CONTEXT_ID_BIT              10
#define CPUID_FEATURE_INFORMATION_ECX_L1_CONTEXT_ID_MASK             0x01
#define CPUID_FEATURE_INFORMATION_ECX_L1_CONTEXT_ID(_)               (((_) >> 10) & 0x01)

      /**
       * @brief IA32_DEBUG_INTERFACE MSR for silicon debug
       *
       * [Bit 11] A value of 1 indicates the processor supports IA32_DEBUG_INTERFACE MSR for silicon debug.
       */
      UINT32 SiliconDebug                                          : 1;
#define CPUID_FEATURE_INFORMATION_ECX_SILICON_DEBUG_BIT              11
#define CPUID_FEATURE_INFORMATION_ECX_SILICON_DEBUG_MASK             0x01
#define CPUID_FEATURE_INFORMATION_ECX_SILICON_DEBUG(_)               (((_) >> 11) & 0x01)

      /**
       * @brief FMA extensions using YMM state
       *
       * [Bit 12] A value of 1 indicates the processor supports FMA (Fused Multiple Add) extensions using YMM state.
       */
      UINT32 FmaExtensions                                         : 1;
#define CPUID_FEATURE_INFORMATION_ECX_FMA_EXTENSIONS_BIT             12
#define CPUID_FEATURE_INFORMATION_ECX_FMA_EXTENSIONS_MASK            0x01
#define CPUID_FEATURE_INFORMATION_ECX_FMA_EXTENSIONS(_)              (((_) >> 12) & 0x01)

      /**
       * @brief CMPXCHG16B instruction
       *
       * [Bit 13] A value of 1 indicates that the feature is available.
       */
      UINT32 Cmpxchg16BInstruction                                 : 1;
#define CPUID_FEATURE_INFORMATION_ECX_CMPXCHG16B_INSTRUCTION_BIT     13
#define CPUID_FEATURE_INFORMATION_ECX_CMPXCHG16B_INSTRUCTION_MASK    0x01
#define CPUID_FEATURE_INFORMATION_ECX_CMPXCHG16B_INSTRUCTION(_)      (((_) >> 13) & 0x01)

      /**
       * @brief xTPR Update Control
       *
       * [Bit 14] A value of 1 indicates that the processor supports changing IA32_MISC_ENABLE[bit 23].
       */
      UINT32 XtprUpdateControl                                     : 1;
#define CPUID_FEATURE_INFORMATION_ECX_XTPR_UPDATE_CONTROL_BIT        14
#define CPUID_FEATURE_INFORMATION_ECX_XTPR_UPDATE_CONTROL_MASK       0x01
#define CPUID_FEATURE_INFORMATION_ECX_XTPR_UPDATE_CONTROL(_)         (((_) >> 14) & 0x01)

      /**
       * @brief Perfmon and Debug Capability
       *
       * [Bit 15] A value of 1 indicates the processor supports the performance and debug feature indication MSR
       * IA32_PERF_CAPABILITIES.
       */
      UINT32 PerfmonAndDebugCapability                             : 1;
#define CPUID_FEATURE_INFORMATION_ECX_PERFMON_AND_DEBUG_CAPABILITY_BIT 15
#define CPUID_FEATURE_INFORMATION_ECX_PERFMON_AND_DEBUG_CAPABILITY_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_PERFMON_AND_DEBUG_CAPABILITY(_) (((_) >> 15) & 0x01)
      UINT32 Reserved1                                             : 1;

      /**
       * @brief Process-context identifiers
       *
       * [Bit 17] A value of 1 indicates that the processor supports PCIDs and that software may set CR4.PCIDE to 1.
       */
      UINT32 ProcessContextIdentifiers                             : 1;
#define CPUID_FEATURE_INFORMATION_ECX_PROCESS_CONTEXT_IDENTIFIERS_BIT 17
#define CPUID_FEATURE_INFORMATION_ECX_PROCESS_CONTEXT_IDENTIFIERS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_PROCESS_CONTEXT_IDENTIFIERS(_) (((_) >> 17) & 0x01)

      /**
       * @brief Direct Cache Access
       *
       * [Bit 18] A value of 1 indicates the processor supports the ability to prefetch data from a memory mapped device (Direct
       * Cache Access).
       */
      UINT32 DirectCacheAccess                                     : 1;
#define CPUID_FEATURE_INFORMATION_ECX_DIRECT_CACHE_ACCESS_BIT        18
#define CPUID_FEATURE_INFORMATION_ECX_DIRECT_CACHE_ACCESS_MASK       0x01
#define CPUID_FEATURE_INFORMATION_ECX_DIRECT_CACHE_ACCESS(_)         (((_) >> 18) & 0x01)

      /**
       * @brief SSE4.1 support
       *
       * [Bit 19] A value of 1 indicates that the processor supports SSE4.1.
       */
      UINT32 Sse41Support                                          : 1;
#define CPUID_FEATURE_INFORMATION_ECX_SSE41_SUPPORT_BIT              19
#define CPUID_FEATURE_INFORMATION_ECX_SSE41_SUPPORT_MASK             0x01
#define CPUID_FEATURE_INFORMATION_ECX_SSE41_SUPPORT(_)               (((_) >> 19) & 0x01)

      /**
       * @brief SSE4.2 support
       *
       * [Bit 20] A value of 1 indicates that the processor supports SSE4.2.
       */
      UINT32 Sse42Support                                          : 1;
#define CPUID_FEATURE_INFORMATION_ECX_SSE42_SUPPORT_BIT              20
#define CPUID_FEATURE_INFORMATION_ECX_SSE42_SUPPORT_MASK             0x01
#define CPUID_FEATURE_INFORMATION_ECX_SSE42_SUPPORT(_)               (((_) >> 20) & 0x01)

      /**
       * @brief x2APIC support
       *
       * [Bit 21] A value of 1 indicates that the processor supports x2APIC feature.
       */
      UINT32 X2ApicSupport                                         : 1;
#define CPUID_FEATURE_INFORMATION_ECX_X2APIC_SUPPORT_BIT             21
#define CPUID_FEATURE_INFORMATION_ECX_X2APIC_SUPPORT_MASK            0x01
#define CPUID_FEATURE_INFORMATION_ECX_X2APIC_SUPPORT(_)              (((_) >> 21) & 0x01)

      /**
       * @brief MOVBE instruction
       *
       * [Bit 22] A value of 1 indicates that the processor supports MOVBE instruction.
       */
      UINT32 MovbeInstruction                                      : 1;
#define CPUID_FEATURE_INFORMATION_ECX_MOVBE_INSTRUCTION_BIT          22
#define CPUID_FEATURE_INFORMATION_ECX_MOVBE_INSTRUCTION_MASK         0x01
#define CPUID_FEATURE_INFORMATION_ECX_MOVBE_INSTRUCTION(_)           (((_) >> 22) & 0x01)

      /**
       * @brief POPCNT instruction
       *
       * [Bit 23] A value of 1 indicates that the processor supports the POPCNT instruction.
       */
      UINT32 PopcntInstruction                                     : 1;
#define CPUID_FEATURE_INFORMATION_ECX_POPCNT_INSTRUCTION_BIT         23
#define CPUID_FEATURE_INFORMATION_ECX_POPCNT_INSTRUCTION_MASK        0x01
#define CPUID_FEATURE_INFORMATION_ECX_POPCNT_INSTRUCTION(_)          (((_) >> 23) & 0x01)

      /**
       * @brief TSC Deadline
       *
       * [Bit 24] A value of 1 indicates that the processor's local APIC timer supports one-shot operation using a TSC deadline
       * value.
       */
      UINT32 TscDeadline                                           : 1;
#define CPUID_FEATURE_INFORMATION_ECX_TSC_DEADLINE_BIT               24
#define CPUID_FEATURE_INFORMATION_ECX_TSC_DEADLINE_MASK              0x01
#define CPUID_FEATURE_INFORMATION_ECX_TSC_DEADLINE(_)                (((_) >> 24) & 0x01)

      /**
       * @brief AESNI instruction extensions
       *
       * [Bit 25] A value of 1 indicates that the processor supports the AESNI instruction extensions.
       */
      UINT32 AesniInstructionExtensions                            : 1;
#define CPUID_FEATURE_INFORMATION_ECX_AESNI_INSTRUCTION_EXTENSIONS_BIT 25
#define CPUID_FEATURE_INFORMATION_ECX_AESNI_INSTRUCTION_EXTENSIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_AESNI_INSTRUCTION_EXTENSIONS(_) (((_) >> 25) & 0x01)

      /**
       * @brief XSAVE/XRSTOR instruction extensions
       *
       * [Bit 26] A value of 1 indicates that the processor supports the XSAVE/XRSTOR processor extended states feature, the
       * XSETBV/XGETBV instructions, and XCR0.
       */
      UINT32 XsaveXrstorInstruction                                : 1;
#define CPUID_FEATURE_INFORMATION_ECX_XSAVE_XRSTOR_INSTRUCTION_BIT   26
#define CPUID_FEATURE_INFORMATION_ECX_XSAVE_XRSTOR_INSTRUCTION_MASK  0x01
#define CPUID_FEATURE_INFORMATION_ECX_XSAVE_XRSTOR_INSTRUCTION(_)    (((_) >> 26) & 0x01)

      /**
       * @brief CR4.OSXSAVE[bit 18] set
       *
       * [Bit 27] A value of 1 indicates that the OS has set CR4.OSXSAVE[bit 18] to enable XSETBV/XGETBV instructions to access
       * XCR0 and to support processor extended state management using XSAVE/XRSTOR.
       */
      UINT32 OsxSave                                               : 1;
#define CPUID_FEATURE_INFORMATION_ECX_OSX_SAVE_BIT                   27
#define CPUID_FEATURE_INFORMATION_ECX_OSX_SAVE_MASK                  0x01
#define CPUID_FEATURE_INFORMATION_ECX_OSX_SAVE(_)                    (((_) >> 27) & 0x01)

      /**
       * @brief AVX instruction extensions support
       *
       * [Bit 28] A value of 1 indicates the processor supports the AVX instruction extensions.
       */
      UINT32 AvxSupport                                            : 1;
#define CPUID_FEATURE_INFORMATION_ECX_AVX_SUPPORT_BIT                28
#define CPUID_FEATURE_INFORMATION_ECX_AVX_SUPPORT_MASK               0x01
#define CPUID_FEATURE_INFORMATION_ECX_AVX_SUPPORT(_)                 (((_) >> 28) & 0x01)

      /**
       * @brief 16-bit floating-point conversion instructions support
       *
       * [Bit 29] A value of 1 indicates that processor supports 16-bit floating-point conversion instructions.
       */
      UINT32 HalfPrecisionConversionInstructions                   : 1;
#define CPUID_FEATURE_INFORMATION_ECX_HALF_PRECISION_CONVERSION_INSTRUCTIONS_BIT 29
#define CPUID_FEATURE_INFORMATION_ECX_HALF_PRECISION_CONVERSION_INSTRUCTIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_ECX_HALF_PRECISION_CONVERSION_INSTRUCTIONS(_) (((_) >> 29) & 0x01)

      /**
       * @brief RDRAND instruction support
       *
       * [Bit 30] A value of 1 indicates that processor supports RDRAND instruction.
       */
      UINT32 RdrandInstruction                                     : 1;
#define CPUID_FEATURE_INFORMATION_ECX_RDRAND_INSTRUCTION_BIT         30
#define CPUID_FEATURE_INFORMATION_ECX_RDRAND_INSTRUCTION_MASK        0x01
#define CPUID_FEATURE_INFORMATION_ECX_RDRAND_INSTRUCTION(_)          (((_) >> 30) & 0x01)
      UINT32 Reserved2                                             : 1;
    };

    UINT32 Flags;
  } CpuidFeatureInformationEcx;

  /**
   * @brief When CPUID executes with EAX set to 01H, feature information is returned in ECX and EDX
   */
  union
  {
    struct
    {
      /**
       * @brief Floating Point Unit On-Chip
       *
       * [Bit 0] The processor contains an x87 FPU.
       */
      UINT32 FloatingPointUnitOnChip                               : 1;
#define CPUID_FEATURE_INFORMATION_EDX_FLOATING_POINT_UNIT_ON_CHIP_BIT 0
#define CPUID_FEATURE_INFORMATION_EDX_FLOATING_POINT_UNIT_ON_CHIP_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_FLOATING_POINT_UNIT_ON_CHIP(_) (((_) >> 0) & 0x01)

      /**
       * @brief Virtual 8086 Mode Enhancements
       *
       * [Bit 1] Virtual 8086 mode enhancements, including CR4.VME for controlling the feature, CR4.PVI for protected mode
       * virtual interrupts, software interrupt indirection, expansion of the TSS with the software indirection bitmap, and
       * EFLAGS.VIF and EFLAGS.VIP flags.
       */
      UINT32 Virtual8086ModeEnhancements                           : 1;
#define CPUID_FEATURE_INFORMATION_EDX_VIRTUAL_8086_MODE_ENHANCEMENTS_BIT 1
#define CPUID_FEATURE_INFORMATION_EDX_VIRTUAL_8086_MODE_ENHANCEMENTS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_VIRTUAL_8086_MODE_ENHANCEMENTS(_) (((_) >> 1) & 0x01)

      /**
       * @brief Debugging Extensions
       *
       * [Bit 2] Support for I/O breakpoints, including CR4.DE for controlling the feature, and optional trapping of accesses to
       * DR4 and DR5.
       */
      UINT32 DebuggingExtensions                                   : 1;
#define CPUID_FEATURE_INFORMATION_EDX_DEBUGGING_EXTENSIONS_BIT       2
#define CPUID_FEATURE_INFORMATION_EDX_DEBUGGING_EXTENSIONS_MASK      0x01
#define CPUID_FEATURE_INFORMATION_EDX_DEBUGGING_EXTENSIONS(_)        (((_) >> 2) & 0x01)

      /**
       * @brief Page Size Extension
       *
       * [Bit 3] Large pages of size 4 MByte are supported, including CR4.PSE for controlling the feature, the defined dirty bit
       * in PDE (Page Directory Entries), optional reserved bit trapping in CR3, PDEs, and PTEs.
       */
      UINT32 PageSizeExtension                                     : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION_BIT        3
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION_MASK       0x01
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION(_)         (((_) >> 3) & 0x01)

      /**
       * @brief Time Stamp Counter
       *
       * [Bit 4] The RDTSC instruction is supported, including CR4.TSD for controlling privilege.
       */
      UINT32 TimestampCounter                                      : 1;
#define CPUID_FEATURE_INFORMATION_EDX_TIMESTAMP_COUNTER_BIT          4
#define CPUID_FEATURE_INFORMATION_EDX_TIMESTAMP_COUNTER_MASK         0x01
#define CPUID_FEATURE_INFORMATION_EDX_TIMESTAMP_COUNTER(_)           (((_) >> 4) & 0x01)

      /**
       * @brief Model Specific Registers RDMSR and WRMSR Instructions
       *
       * [Bit 5] The RDMSR and WRMSR instructions are supported. Some of the MSRs are implementation dependent.
       */
      UINT32 RdmsrWrmsrInstructions                                : 1;
#define CPUID_FEATURE_INFORMATION_EDX_RDMSR_WRMSR_INSTRUCTIONS_BIT   5
#define CPUID_FEATURE_INFORMATION_EDX_RDMSR_WRMSR_INSTRUCTIONS_MASK  0x01
#define CPUID_FEATURE_INFORMATION_EDX_RDMSR_WRMSR_INSTRUCTIONS(_)    (((_) >> 5) & 0x01)

      /**
       * @brief Physical Address Extension
       *
       * [Bit 6] Physical addresses greater than 32 bits are supported: extended page table entry formats, an extra level in the
       * page translation tables is defined, 2-MByte pages are supported instead of 4 Mbyte pages if PAE bit is 1.
       */
      UINT32 PhysicalAddressExtension                              : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PHYSICAL_ADDRESS_EXTENSION_BIT 6
#define CPUID_FEATURE_INFORMATION_EDX_PHYSICAL_ADDRESS_EXTENSION_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_PHYSICAL_ADDRESS_EXTENSION(_)  (((_) >> 6) & 0x01)

      /**
       * @brief Machine Check Exception
       *
       * [Bit 7] Exception 18 is defined for Machine Checks, including CR4.MCE for controlling the feature. This feature does not
       * define the model-specific implementations of machine-check error logging, reporting, and processor shutdowns. Machine
       * Check exception handlers may have to depend on processor version to do model specific processing of the exception, or
       * test for the presence of the Machine Check feature.
       */
      UINT32 MachineCheckException                                 : 1;
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_EXCEPTION_BIT    7
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_EXCEPTION_MASK   0x01
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_EXCEPTION(_)     (((_) >> 7) & 0x01)

      /**
       * @brief CMPXCHG8B Instruction
       *
       * [Bit 8] The compare-and-exchange 8 bytes (64 bits) instruction is supported (implicitly locked and atomic).
       */
      UINT32 Cmpxchg8B                                             : 1;
#define CPUID_FEATURE_INFORMATION_EDX_CMPXCHG8B_BIT                  8
#define CPUID_FEATURE_INFORMATION_EDX_CMPXCHG8B_MASK                 0x01
#define CPUID_FEATURE_INFORMATION_EDX_CMPXCHG8B(_)                   (((_) >> 8) & 0x01)

      /**
       * @brief APIC On-Chip
       *
       * [Bit 9] The processor contains an Advanced Programmable Interrupt Controller (APIC), responding to memory mapped
       * commands in the physical address range FFFE0000H to FFFE0FFFH (by default - some processors permit the APIC to be
       * relocated).
       */
      UINT32 ApicOnChip                                            : 1;
#define CPUID_FEATURE_INFORMATION_EDX_APIC_ON_CHIP_BIT               9
#define CPUID_FEATURE_INFORMATION_EDX_APIC_ON_CHIP_MASK              0x01
#define CPUID_FEATURE_INFORMATION_EDX_APIC_ON_CHIP(_)                (((_) >> 9) & 0x01)
      UINT32 Reserved1                                             : 1;

      /**
       * @brief SYSENTER and SYSEXIT Instructions
       *
       * [Bit 11] The SYSENTER and SYSEXIT and associated MSRs are supported.
       */
      UINT32 SysenterSysexitInstructions                           : 1;
#define CPUID_FEATURE_INFORMATION_EDX_SYSENTER_SYSEXIT_INSTRUCTIONS_BIT 11
#define CPUID_FEATURE_INFORMATION_EDX_SYSENTER_SYSEXIT_INSTRUCTIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_SYSENTER_SYSEXIT_INSTRUCTIONS(_) (((_) >> 11) & 0x01)

      /**
       * @brief Memory Type Range Registers
       *
       * [Bit 12] MTRRs are supported. The MTRRcap MSR contains feature bits that describe what memory types are supported, how
       * many variable MTRRs are supported, and whether fixed MTRRs are supported.
       */
      UINT32 MemoryTypeRangeRegisters                              : 1;
#define CPUID_FEATURE_INFORMATION_EDX_MEMORY_TYPE_RANGE_REGISTERS_BIT 12
#define CPUID_FEATURE_INFORMATION_EDX_MEMORY_TYPE_RANGE_REGISTERS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_MEMORY_TYPE_RANGE_REGISTERS(_) (((_) >> 12) & 0x01)

      /**
       * @brief Page Global Bit
       *
       * [Bit 13] The global bit is supported in paging-structure entries that map a page, indicating TLB entries that are common
       * to different processes and need not be flushed. The CR4.PGE bit controls this feature.
       */
      UINT32 PageGlobalBit                                         : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_GLOBAL_BIT_BIT            13
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_GLOBAL_BIT_MASK           0x01
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_GLOBAL_BIT(_)             (((_) >> 13) & 0x01)

      /**
       * @brief Machine Check Architecture
       *
       * [Bit 14] A value of 1 indicates the Machine Check Architecture of reporting machine errors is supported. The MCG_CAP MSR
       * contains feature bits describing how many banks of error reporting MSRs are supported.
       */
      UINT32 MachineCheckArchitecture                              : 1;
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_ARCHITECTURE_BIT 14
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_ARCHITECTURE_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_MACHINE_CHECK_ARCHITECTURE(_)  (((_) >> 14) & 0x01)

      /**
       * @brief Conditional Move Instructions
       *
       * [Bit 15] The conditional move instruction CMOV is supported. In addition, if x87 FPU is present as indicated by the
       * CPUID.FPU feature bit, then the FCOMI and FCMOV instructions are supported
       */
      UINT32 ConditionalMoveInstructions                           : 1;
#define CPUID_FEATURE_INFORMATION_EDX_CONDITIONAL_MOVE_INSTRUCTIONS_BIT 15
#define CPUID_FEATURE_INFORMATION_EDX_CONDITIONAL_MOVE_INSTRUCTIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_CONDITIONAL_MOVE_INSTRUCTIONS(_) (((_) >> 15) & 0x01)

      /**
       * @brief Page Attribute Table
       *
       * [Bit 16] Page Attribute Table is supported. This feature augments the Memory Type Range Registers (MTRRs), allowing an
       * operating system to specify attributes of memory accessed through a linear address on a 4KB granularity.
       */
      UINT32 PageAttributeTable                                    : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_ATTRIBUTE_TABLE_BIT       16
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_ATTRIBUTE_TABLE_MASK      0x01
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_ATTRIBUTE_TABLE(_)        (((_) >> 16) & 0x01)

      /**
       * @brief 36-Bit Page Size Extension
       *
       * [Bit 17] 4-MByte pages addressing physical memory beyond 4 GBytes are supported with 32-bit paging. This feature
       * indicates that upper bits of the physical address of a 4-MByte page are encoded in bits 20:13 of the page-directory
       * entry. Such physical addresses are limited by MAXPHYADDR and may be up to 40 bits in size.
       */
      UINT32 PageSizeExtension36Bit                                : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION_36BIT_BIT  17
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION_36BIT_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_PAGE_SIZE_EXTENSION_36BIT(_)   (((_) >> 17) & 0x01)

      /**
       * @brief Processor Serial Number
       *
       * [Bit 18] The processor supports the 96-bit processor identification number feature and the feature is enabled.
       */
      UINT32 ProcessorSerialNumber                                 : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PROCESSOR_SERIAL_NUMBER_BIT    18
#define CPUID_FEATURE_INFORMATION_EDX_PROCESSOR_SERIAL_NUMBER_MASK   0x01
#define CPUID_FEATURE_INFORMATION_EDX_PROCESSOR_SERIAL_NUMBER(_)     (((_) >> 18) & 0x01)

      /**
       * @brief CLFLUSH Instruction
       *
       * [Bit 19] CLFLUSH Instruction is supported.
       */
      UINT32 Clflush                                               : 1;
#define CPUID_FEATURE_INFORMATION_EDX_CLFLUSH_BIT                    19
#define CPUID_FEATURE_INFORMATION_EDX_CLFLUSH_MASK                   0x01
#define CPUID_FEATURE_INFORMATION_EDX_CLFLUSH(_)                     (((_) >> 19) & 0x01)
      UINT32 Reserved2                                             : 1;

      /**
       * @brief Debug Store
       *
       * [Bit 21] The processor supports the ability to write debug information into a memory resident buffer. This feature is
       * used by the branch trace store (BTS) and processor event-based sampling (PEBS) facilities.
       *
       * @see Vol3C[23(INTRODUCTION TO VIRTUAL MACHINE EXTENSIONS)]
       */
      UINT32 DebugStore                                            : 1;
#define CPUID_FEATURE_INFORMATION_EDX_DEBUG_STORE_BIT                21
#define CPUID_FEATURE_INFORMATION_EDX_DEBUG_STORE_MASK               0x01
#define CPUID_FEATURE_INFORMATION_EDX_DEBUG_STORE(_)                 (((_) >> 21) & 0x01)

      /**
       * @brief Thermal Monitor and Software Controlled Clock Facilities
       *
       * [Bit 22] The processor implements internal MSRs that allow processor temperature to be monitored and processor
       * performance to be modulated in predefined duty cycles under software control.
       */
      UINT32 ThermalControlMsrsForAcpi                             : 1;
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_CONTROL_MSRS_FOR_ACPI_BIT 22
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_CONTROL_MSRS_FOR_ACPI_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_CONTROL_MSRS_FOR_ACPI(_) (((_) >> 22) & 0x01)

      /**
       * @brief Intel MMX Technology
       *
       * [Bit 23] The processor supports the Intel MMX technology.
       */
      UINT32 MmxSupport                                            : 1;
#define CPUID_FEATURE_INFORMATION_EDX_MMX_SUPPORT_BIT                23
#define CPUID_FEATURE_INFORMATION_EDX_MMX_SUPPORT_MASK               0x01
#define CPUID_FEATURE_INFORMATION_EDX_MMX_SUPPORT(_)                 (((_) >> 23) & 0x01)

      /**
       * @brief FXSAVE and FXRSTOR Instructions
       *
       * [Bit 24] The FXSAVE and FXRSTOR instructions are supported for fast save and restore of the floating point context.
       * Presence of this bit also indicates that CR4.OSFXSR is available for an operating system to indicate that it supports
       * the FXSAVE and FXRSTOR instructions.
       */
      UINT32 FxsaveFxrstorInstructions                             : 1;
#define CPUID_FEATURE_INFORMATION_EDX_FXSAVE_FXRSTOR_INSTRUCTIONS_BIT 24
#define CPUID_FEATURE_INFORMATION_EDX_FXSAVE_FXRSTOR_INSTRUCTIONS_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_FXSAVE_FXRSTOR_INSTRUCTIONS(_) (((_) >> 24) & 0x01)

      /**
       * @brief SSE extensions support
       *
       * [Bit 25] The processor supports the SSE extensions.
       */
      UINT32 SseSupport                                            : 1;
#define CPUID_FEATURE_INFORMATION_EDX_SSE_SUPPORT_BIT                25
#define CPUID_FEATURE_INFORMATION_EDX_SSE_SUPPORT_MASK               0x01
#define CPUID_FEATURE_INFORMATION_EDX_SSE_SUPPORT(_)                 (((_) >> 25) & 0x01)

      /**
       * @brief SSE2 extensions support
       *
       * [Bit 26] The processor supports the SSE2 extensions.
       */
      UINT32 Sse2Support                                           : 1;
#define CPUID_FEATURE_INFORMATION_EDX_SSE2_SUPPORT_BIT               26
#define CPUID_FEATURE_INFORMATION_EDX_SSE2_SUPPORT_MASK              0x01
#define CPUID_FEATURE_INFORMATION_EDX_SSE2_SUPPORT(_)                (((_) >> 26) & 0x01)

      /**
       * @brief Self Snoop
       *
       * [Bit 27] The processor supports the management of conflicting memory types by performing a snoop of its own cache
       * structure for transactions issued to the bus.
       */
      UINT32 SelfSnoop                                             : 1;
#define CPUID_FEATURE_INFORMATION_EDX_SELF_SNOOP_BIT                 27
#define CPUID_FEATURE_INFORMATION_EDX_SELF_SNOOP_MASK                0x01
#define CPUID_FEATURE_INFORMATION_EDX_SELF_SNOOP(_)                  (((_) >> 27) & 0x01)

      /**
       * @brief Max APIC IDs reserved field is Valid
       *
       * [Bit 28] A value of 0 for HTT indicates there is only a single logical processor in the package and software should
       * assume only a single APIC ID is reserved. A value of 1 for HTT indicates the value in CPUID.1.EBX[23:16] (the Maximum
       * number of addressable IDs for logical processors in this package) is valid for the package.
       */
      UINT32 HyperThreadingTechnology                              : 1;
#define CPUID_FEATURE_INFORMATION_EDX_HYPER_THREADING_TECHNOLOGY_BIT 28
#define CPUID_FEATURE_INFORMATION_EDX_HYPER_THREADING_TECHNOLOGY_MASK 0x01
#define CPUID_FEATURE_INFORMATION_EDX_HYPER_THREADING_TECHNOLOGY(_)  (((_) >> 28) & 0x01)

      /**
       * @brief Thermal Monitor
       *
       * [Bit 29] The processor implements the thermal monitor automatic thermal control circuitry (TCC).
       */
      UINT32 ThermalMonitor                                        : 1;
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_MONITOR_BIT            29
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_MONITOR_MASK           0x01
#define CPUID_FEATURE_INFORMATION_EDX_THERMAL_MONITOR(_)             (((_) >> 29) & 0x01)
      UINT32 Reserved3                                             : 1;

      /**
       * @brief Pending Break Enable
       *
       * [Bit 31] The processor supports the use of the FERR\#/PBE\# pin when the processor is in the stop-clock state (STPCLK\#
       * is asserted) to signal the processor that an interrupt is pending and that the processor should return to normal
       * operation to handle the interrupt. Bit 10 (PBE enable) in the IA32_MISC_ENABLE MSR enables this capability.
       */
      UINT32 PendingBreakEnable                                    : 1;
#define CPUID_FEATURE_INFORMATION_EDX_PENDING_BREAK_ENABLE_BIT       31
#define CPUID_FEATURE_INFORMATION_EDX_PENDING_BREAK_ENABLE_MASK      0x01
#define CPUID_FEATURE_INFORMATION_EDX_PENDING_BREAK_ENABLE(_)        (((_) >> 31) & 0x01)
    };

    UINT32 Flags;
  } CpuidFeatureInformationEdx;

} CPUID_EAX_01;

/**
 * @brief Deterministic Cache Parameters Leaf
 *
 * When CPUID executes with EAX set to 04H and ECX contains an index value, the processor returns encoded data that
 * describe a set of deterministic cache parameters (for the cache level associated with the input in ECX). Valid index
 * values start from 0.
 * Software can enumerate the deterministic cache parameters for each level of the cache hierarchy starting with an index
 * value of 0, until the parameters report the value associated with the cache type field is 0. The architecturally defined
 * fields reported by deterministic cache parameters are documented in Table 3-8.
 * This Cache Size in Bytes
 * - = (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
 * - = (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
 * The CPUID leaf 04H also reports data that can be used to derive the topology of processor cores in a physical package.
 * This information is constant for all valid index values. Software can query the raw data reported by executing CPUID
 * with EAX=04H and ECX=0 and use it as part of the topology enumeration algorithm.
 *
 * @see Vol3A[8(Multiple-Processor Management)]
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 4:0] - 0 = Null - No more caches. - 1 = Data Cache. - 2 = Instruction Cache. - 3 = Unified Cache. - 4-31 =
       * Reserved.
       */
      UINT32 CacheTypeField                                        : 5;
#define CPUID_EAX_CACHE_TYPE_FIELD_BIT                               0
#define CPUID_EAX_CACHE_TYPE_FIELD_MASK                              0x1F
#define CPUID_EAX_CACHE_TYPE_FIELD(_)                                (((_) >> 0) & 0x1F)

      /**
       * [Bits 7:5] Cache Level (starts at 1).
       */
      UINT32 CacheLevel                                            : 3;
#define CPUID_EAX_CACHE_LEVEL_BIT                                    5
#define CPUID_EAX_CACHE_LEVEL_MASK                                   0x07
#define CPUID_EAX_CACHE_LEVEL(_)                                     (((_) >> 5) & 0x07)

      /**
       * [Bit 8] Self Initializing cache level (does not need SW initialization).
       */
      UINT32 SelfInitializingCacheLevel                            : 1;
#define CPUID_EAX_SELF_INITIALIZING_CACHE_LEVEL_BIT                  8
#define CPUID_EAX_SELF_INITIALIZING_CACHE_LEVEL_MASK                 0x01
#define CPUID_EAX_SELF_INITIALIZING_CACHE_LEVEL(_)                   (((_) >> 8) & 0x01)

      /**
       * [Bit 9] Fully Associative cache.
       */
      UINT32 FullyAssociativeCache                                 : 1;
#define CPUID_EAX_FULLY_ASSOCIATIVE_CACHE_BIT                        9
#define CPUID_EAX_FULLY_ASSOCIATIVE_CACHE_MASK                       0x01
#define CPUID_EAX_FULLY_ASSOCIATIVE_CACHE(_)                         (((_) >> 9) & 0x01)
      UINT32 Reserved1                                             : 4;

      /**
       * [Bits 25:14] Maximum number of addressable IDs for logical processors sharing this cache.
       *
       * @note Add one to the return value to get the result.
       *       The nearest power-of-2 integer that is not smaller than (1 + EAX[25:14]) is the number of unique initial APIC IDs
       *       reserved for addressing different logical processors sharing this cache.
       */
      UINT32 MaxAddressableIdsForLogicalProcessorsSharingThisCache : 12;
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_SHARING_THIS_CACHE_BIT 14
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_SHARING_THIS_CACHE_MASK 0xFFF
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_SHARING_THIS_CACHE(_) (((_) >> 14) & 0xFFF)

      /**
       * [Bits 31:26] Maximum number of addressable IDs for processor cores in the physical package.
       *
       * @note Add one to the return value to get the result.
       *       The nearest power-of-2 integer that is not smaller than (1 + EAX[31:26]) is the number of unique Core_IDs reserved for
       *       addressing different processor cores in a physical package. Core ID is a subset of bits of the initial APIC ID.
       *       The returned value is constant for valid initial values in ECX. Valid ECX values start from 0.
       */
      UINT32 MaxAddressableIdsForProcessorCoresInPhysicalPackage   : 6;
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_PROCESSOR_CORES_IN_PHYSICAL_PACKAGE_BIT 26
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_PROCESSOR_CORES_IN_PHYSICAL_PACKAGE_MASK 0x3F
#define CPUID_EAX_MAX_ADDRESSABLE_IDS_FOR_PROCESSOR_CORES_IN_PHYSICAL_PACKAGE(_) (((_) >> 26) & 0x3F)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 11:0] System Coherency Line Size.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 SystemCoherencyLineSize                               : 12;
#define CPUID_EBX_SYSTEM_COHERENCY_LINE_SIZE_BIT                     0
#define CPUID_EBX_SYSTEM_COHERENCY_LINE_SIZE_MASK                    0xFFF
#define CPUID_EBX_SYSTEM_COHERENCY_LINE_SIZE(_)                      (((_) >> 0) & 0xFFF)

      /**
       * [Bits 21:12] Physical Line partitions.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 PhysicalLinePartitions                                : 10;
#define CPUID_EBX_PHYSICAL_LINE_PARTITIONS_BIT                       12
#define CPUID_EBX_PHYSICAL_LINE_PARTITIONS_MASK                      0x3FF
#define CPUID_EBX_PHYSICAL_LINE_PARTITIONS(_)                        (((_) >> 12) & 0x3FF)

      /**
       * [Bits 31:22] Ways of associativity.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 WaysOfAssociativity                                   : 10;
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_BIT                          22
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_MASK                         0x3FF
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY(_)                           (((_) >> 22) & 0x3FF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Number of Sets.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 NumberOfSets                                          : 32;
#define CPUID_ECX_NUMBER_OF_SETS_BIT                                 0
#define CPUID_ECX_NUMBER_OF_SETS_MASK                                0xFFFFFFFF
#define CPUID_ECX_NUMBER_OF_SETS(_)                                  (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * @brief Write-Back Invalidate/Invalidate
       *
       * [Bit 0] - 0 = WBINVD/INVD from threads sharing this cache acts upon lower level caches for threads sharing this cache.
       * - 1 = WBINVD/INVD is not guaranteed to act upon lower level caches of non-originating threads sharing this cache.
       */
      UINT32 WriteBackInvalidate                                   : 1;
#define CPUID_EDX_WRITE_BACK_INVALIDATE_BIT                          0
#define CPUID_EDX_WRITE_BACK_INVALIDATE_MASK                         0x01
#define CPUID_EDX_WRITE_BACK_INVALIDATE(_)                           (((_) >> 0) & 0x01)

      /**
       * @brief Cache Inclusiveness
       *
       * [Bit 1] - 0 = Cache is not inclusive of lower cache levels.
       * - 1 = Cache is inclusive of lower cache levels.
       */
      UINT32 CacheInclusiveness                                    : 1;
#define CPUID_EDX_CACHE_INCLUSIVENESS_BIT                            1
#define CPUID_EDX_CACHE_INCLUSIVENESS_MASK                           0x01
#define CPUID_EDX_CACHE_INCLUSIVENESS(_)                             (((_) >> 1) & 0x01)

      /**
       * @brief Complex Cache Indexing
       *
       * [Bit 2] - 0 = Direct mapped cache.
       * - 1 = A complex function is used to index the cache, potentially using all address bits.
       */
      UINT32 ComplexCacheIndexing                                  : 1;
#define CPUID_EDX_COMPLEX_CACHE_INDEXING_BIT                         2
#define CPUID_EDX_COMPLEX_CACHE_INDEXING_MASK                        0x01
#define CPUID_EDX_COMPLEX_CACHE_INDEXING(_)                          (((_) >> 2) & 0x01)
      UINT32 Reserved1                                             : 29;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_04;

/**
 * @brief MONITOR/MWAIT Leaf
 *
 * When CPUID executes with EAX set to 05H, the processor returns information about features available to MONITOR/MWAIT
 * instructions. The MONITOR instruction is used for address-range monitoring in conjunction with MWAIT instruction. The
 * MWAIT instruction optionally provides additional extensions for advanced power management.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 15:0] Smallest monitor-line size in bytes (default is processor's monitor granularity).
       */
      UINT32 SmallestMonitorLineSize                               : 16;
#define CPUID_EAX_SMALLEST_MONITOR_LINE_SIZE_BIT                     0
#define CPUID_EAX_SMALLEST_MONITOR_LINE_SIZE_MASK                    0xFFFF
#define CPUID_EAX_SMALLEST_MONITOR_LINE_SIZE(_)                      (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Largest monitor-line size in bytes (default is processor's monitor granularity).
       */
      UINT32 LargestMonitorLineSize                                : 16;
#define CPUID_EBX_LARGEST_MONITOR_LINE_SIZE_BIT                      0
#define CPUID_EBX_LARGEST_MONITOR_LINE_SIZE_MASK                     0xFFFF
#define CPUID_EBX_LARGEST_MONITOR_LINE_SIZE(_)                       (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] Enumeration of Monitor-Mwait extensions (beyond EAX and EBX registers) supported.
       */
      UINT32 EnumerationOfMonitorMwaitExtensions                   : 1;
#define CPUID_ECX_ENUMERATION_OF_MONITOR_MWAIT_EXTENSIONS_BIT        0
#define CPUID_ECX_ENUMERATION_OF_MONITOR_MWAIT_EXTENSIONS_MASK       0x01
#define CPUID_ECX_ENUMERATION_OF_MONITOR_MWAIT_EXTENSIONS(_)         (((_) >> 0) & 0x01)

      /**
       * [Bit 1] Supports treating interrupts as break-event for MWAIT, even when interrupts disabled.
       */
      UINT32 SupportsTreatingInterruptsAsBreakEventForMwait        : 1;
#define CPUID_ECX_SUPPORTS_TREATING_INTERRUPTS_AS_BREAK_EVENT_FOR_MWAIT_BIT 1
#define CPUID_ECX_SUPPORTS_TREATING_INTERRUPTS_AS_BREAK_EVENT_FOR_MWAIT_MASK 0x01
#define CPUID_ECX_SUPPORTS_TREATING_INTERRUPTS_AS_BREAK_EVENT_FOR_MWAIT(_) (((_) >> 1) & 0x01)
      UINT32 Reserved1                                             : 30;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 3:0] Number of C0 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC0SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C0_SUB_C_STATES_BIT                      0
#define CPUID_EDX_NUMBER_OF_C0_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C0_SUB_C_STATES(_)                       (((_) >> 0) & 0x0F)

      /**
       * [Bits 7:4] Number of C1 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC1SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C1_SUB_C_STATES_BIT                      4
#define CPUID_EDX_NUMBER_OF_C1_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C1_SUB_C_STATES(_)                       (((_) >> 4) & 0x0F)

      /**
       * [Bits 11:8] Number of C2 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC2SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C2_SUB_C_STATES_BIT                      8
#define CPUID_EDX_NUMBER_OF_C2_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C2_SUB_C_STATES(_)                       (((_) >> 8) & 0x0F)

      /**
       * [Bits 15:12] Number of C3 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC3SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C3_SUB_C_STATES_BIT                      12
#define CPUID_EDX_NUMBER_OF_C3_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C3_SUB_C_STATES(_)                       (((_) >> 12) & 0x0F)

      /**
       * [Bits 19:16] Number of C4 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC4SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C4_SUB_C_STATES_BIT                      16
#define CPUID_EDX_NUMBER_OF_C4_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C4_SUB_C_STATES(_)                       (((_) >> 16) & 0x0F)

      /**
       * [Bits 23:20] Number of C5 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC5SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C5_SUB_C_STATES_BIT                      20
#define CPUID_EDX_NUMBER_OF_C5_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C5_SUB_C_STATES(_)                       (((_) >> 20) & 0x0F)

      /**
       * [Bits 27:24] Number of C6 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC6SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C6_SUB_C_STATES_BIT                      24
#define CPUID_EDX_NUMBER_OF_C6_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C6_SUB_C_STATES(_)                       (((_) >> 24) & 0x0F)

      /**
       * [Bits 31:28] Number of C7 sub C-states supported using MWAIT.
       */
      UINT32 NumberOfC7SubCStates                                  : 4;
#define CPUID_EDX_NUMBER_OF_C7_SUB_C_STATES_BIT                      28
#define CPUID_EDX_NUMBER_OF_C7_SUB_C_STATES_MASK                     0x0F
#define CPUID_EDX_NUMBER_OF_C7_SUB_C_STATES(_)                       (((_) >> 28) & 0x0F)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_05;

/**
 * @brief Thermal and Power Management Leaf
 *
 * When CPUID executes with EAX set to 06H, the processor returns information about thermal and power management features.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bit 0] Digital temperature sensor is supported if set.
       */
      UINT32 TemperatureSensorSupported                            : 1;
#define CPUID_EAX_TEMPERATURE_SENSOR_SUPPORTED_BIT                   0
#define CPUID_EAX_TEMPERATURE_SENSOR_SUPPORTED_MASK                  0x01
#define CPUID_EAX_TEMPERATURE_SENSOR_SUPPORTED(_)                    (((_) >> 0) & 0x01)

      /**
       * [Bit 1] Intel Turbo Boost Technology available (see description of IA32_MISC_ENABLE[38]).
       */
      UINT32 IntelTurboBoostTechnologyAvailable                    : 1;
#define CPUID_EAX_INTEL_TURBO_BOOST_TECHNOLOGY_AVAILABLE_BIT         1
#define CPUID_EAX_INTEL_TURBO_BOOST_TECHNOLOGY_AVAILABLE_MASK        0x01
#define CPUID_EAX_INTEL_TURBO_BOOST_TECHNOLOGY_AVAILABLE(_)          (((_) >> 1) & 0x01)

      /**
       * [Bit 2] ARAT. APIC-Timer-always-running feature is supported if set.
       */
      UINT32 ApicTimerAlwaysRunning                                : 1;
#define CPUID_EAX_APIC_TIMER_ALWAYS_RUNNING_BIT                      2
#define CPUID_EAX_APIC_TIMER_ALWAYS_RUNNING_MASK                     0x01
#define CPUID_EAX_APIC_TIMER_ALWAYS_RUNNING(_)                       (((_) >> 2) & 0x01)
      UINT32 Reserved1                                             : 1;

      /**
       * [Bit 4] PLN. Power limit notification controls are supported if set.
       */
      UINT32 PowerLimitNotification                                : 1;
#define CPUID_EAX_POWER_LIMIT_NOTIFICATION_BIT                       4
#define CPUID_EAX_POWER_LIMIT_NOTIFICATION_MASK                      0x01
#define CPUID_EAX_POWER_LIMIT_NOTIFICATION(_)                        (((_) >> 4) & 0x01)

      /**
       * [Bit 5] ECMD. Clock modulation duty cycle extension is supported if set.
       */
      UINT32 ClockModulationDuty                                   : 1;
#define CPUID_EAX_CLOCK_MODULATION_DUTY_BIT                          5
#define CPUID_EAX_CLOCK_MODULATION_DUTY_MASK                         0x01
#define CPUID_EAX_CLOCK_MODULATION_DUTY(_)                           (((_) >> 5) & 0x01)

      /**
       * [Bit 6] PTM. Package thermal management is supported if set.
       */
      UINT32 PackageThermalManagement                              : 1;
#define CPUID_EAX_PACKAGE_THERMAL_MANAGEMENT_BIT                     6
#define CPUID_EAX_PACKAGE_THERMAL_MANAGEMENT_MASK                    0x01
#define CPUID_EAX_PACKAGE_THERMAL_MANAGEMENT(_)                      (((_) >> 6) & 0x01)

      /**
       * [Bit 7] HWP. HWP base registers (IA32_PM_ENABLE[bit 0], IA32_HWP_CAPABILITIES, IA32_HWP_REQUEST, IA32_HWP_STATUS) are
       * supported if set.
       */
      UINT32 HwpBaseRegisters                                      : 1;
#define CPUID_EAX_HWP_BASE_REGISTERS_BIT                             7
#define CPUID_EAX_HWP_BASE_REGISTERS_MASK                            0x01
#define CPUID_EAX_HWP_BASE_REGISTERS(_)                              (((_) >> 7) & 0x01)

      /**
       * [Bit 8] HWP_Notification. IA32_HWP_INTERRUPT MSR is supported if set.
       */
      UINT32 HwpNotification                                       : 1;
#define CPUID_EAX_HWP_NOTIFICATION_BIT                               8
#define CPUID_EAX_HWP_NOTIFICATION_MASK                              0x01
#define CPUID_EAX_HWP_NOTIFICATION(_)                                (((_) >> 8) & 0x01)

      /**
       * [Bit 9] HWP_Activity_Window. IA32_HWP_REQUEST[bits 41:32] is supported if set.
       */
      UINT32 HwpActivityWindow                                     : 1;
#define CPUID_EAX_HWP_ACTIVITY_WINDOW_BIT                            9
#define CPUID_EAX_HWP_ACTIVITY_WINDOW_MASK                           0x01
#define CPUID_EAX_HWP_ACTIVITY_WINDOW(_)                             (((_) >> 9) & 0x01)

      /**
       * [Bit 10] HWP_Energy_Performance_Preference. IA32_HWP_REQUEST[bits 31:24] is supported if set.
       */
      UINT32 HwpEnergyPerformancePreference                        : 1;
#define CPUID_EAX_HWP_ENERGY_PERFORMANCE_PREFERENCE_BIT              10
#define CPUID_EAX_HWP_ENERGY_PERFORMANCE_PREFERENCE_MASK             0x01
#define CPUID_EAX_HWP_ENERGY_PERFORMANCE_PREFERENCE(_)               (((_) >> 10) & 0x01)

      /**
       * [Bit 11] HWP_Package_Level_Request. IA32_HWP_REQUEST_PKG MSR is supported if set.
       */
      UINT32 HwpPackageLevelRequest                                : 1;
#define CPUID_EAX_HWP_PACKAGE_LEVEL_REQUEST_BIT                      11
#define CPUID_EAX_HWP_PACKAGE_LEVEL_REQUEST_MASK                     0x01
#define CPUID_EAX_HWP_PACKAGE_LEVEL_REQUEST(_)                       (((_) >> 11) & 0x01)
      UINT32 Reserved2                                             : 1;

      /**
       * [Bit 13] HDC. HDC base registers IA32_PKG_HDC_CTL, IA32_PM_CTL1, IA32_THREAD_STALL MSRs are supported if set.
       */
      UINT32 Hdc                                                   : 1;
#define CPUID_EAX_HDC_BIT                                            13
#define CPUID_EAX_HDC_MASK                                           0x01
#define CPUID_EAX_HDC(_)                                             (((_) >> 13) & 0x01)

      /**
       * [Bit 14] Intel(R) Turbo Boost Max Technology 3.0 available.
       */
      UINT32 IntelTurboBoostMaxTechnology3Available                : 1;
#define CPUID_EAX_INTEL_TURBO_BOOST_MAX_TECHNOLOGY_3_AVAILABLE_BIT   14
#define CPUID_EAX_INTEL_TURBO_BOOST_MAX_TECHNOLOGY_3_AVAILABLE_MASK  0x01
#define CPUID_EAX_INTEL_TURBO_BOOST_MAX_TECHNOLOGY_3_AVAILABLE(_)    (((_) >> 14) & 0x01)

      /**
       * [Bit 15] HWP Capabilities. Highest Performance change is supported if set.
       */
      UINT32 HwpCapabilities                                       : 1;
#define CPUID_EAX_HWP_CAPABILITIES_BIT                               15
#define CPUID_EAX_HWP_CAPABILITIES_MASK                              0x01
#define CPUID_EAX_HWP_CAPABILITIES(_)                                (((_) >> 15) & 0x01)

      /**
       * [Bit 16] HWP PECI override is supported if set.
       */
      UINT32 HwpPeciOverride                                       : 1;
#define CPUID_EAX_HWP_PECI_OVERRIDE_BIT                              16
#define CPUID_EAX_HWP_PECI_OVERRIDE_MASK                             0x01
#define CPUID_EAX_HWP_PECI_OVERRIDE(_)                               (((_) >> 16) & 0x01)

      /**
       * [Bit 17] Flexible HWP is supported if set.
       */
      UINT32 FlexibleHwp                                           : 1;
#define CPUID_EAX_FLEXIBLE_HWP_BIT                                   17
#define CPUID_EAX_FLEXIBLE_HWP_MASK                                  0x01
#define CPUID_EAX_FLEXIBLE_HWP(_)                                    (((_) >> 17) & 0x01)

      /**
       * [Bit 18] Fast access mode for the IA32_HWP_REQUEST MSR is supported if set.
       */
      UINT32 FastAccessModeForHwpRequestMsr                        : 1;
#define CPUID_EAX_FAST_ACCESS_MODE_FOR_HWP_REQUEST_MSR_BIT           18
#define CPUID_EAX_FAST_ACCESS_MODE_FOR_HWP_REQUEST_MSR_MASK          0x01
#define CPUID_EAX_FAST_ACCESS_MODE_FOR_HWP_REQUEST_MSR(_)            (((_) >> 18) & 0x01)
      UINT32 Reserved3                                             : 1;

      /**
       * [Bit 20] Ignoring Idle Logical Processor HWP request is supported if set.
       */
      UINT32 IgnoringIdleLogicalProcessorHwpRequest                : 1;
#define CPUID_EAX_IGNORING_IDLE_LOGICAL_PROCESSOR_HWP_REQUEST_BIT    20
#define CPUID_EAX_IGNORING_IDLE_LOGICAL_PROCESSOR_HWP_REQUEST_MASK   0x01
#define CPUID_EAX_IGNORING_IDLE_LOGICAL_PROCESSOR_HWP_REQUEST(_)     (((_) >> 20) & 0x01)
      UINT32 Reserved4                                             : 11;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 3:0] Number of Interrupt Thresholds in Digital Thermal Sensor.
       */
      UINT32 NumberOfInterruptThresholdsInThermalSensor            : 4;
#define CPUID_EBX_NUMBER_OF_INTERRUPT_THRESHOLDS_IN_THERMAL_SENSOR_BIT 0
#define CPUID_EBX_NUMBER_OF_INTERRUPT_THRESHOLDS_IN_THERMAL_SENSOR_MASK 0x0F
#define CPUID_EBX_NUMBER_OF_INTERRUPT_THRESHOLDS_IN_THERMAL_SENSOR(_) (((_) >> 0) & 0x0F)
      UINT32 Reserved1                                             : 28;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] Hardware Coordination Feedback Capability (Presence of IA32_MPERF and IA32_APERF). The capability to provide a
       * measure of delivered processor performance (since last reset of the counters), as a percentage of the expected processor
       * performance when running at the TSC frequency.
       */
      UINT32 HardwareCoordinationFeedbackCapability                : 1;
#define CPUID_ECX_HARDWARE_COORDINATION_FEEDBACK_CAPABILITY_BIT      0
#define CPUID_ECX_HARDWARE_COORDINATION_FEEDBACK_CAPABILITY_MASK     0x01
#define CPUID_ECX_HARDWARE_COORDINATION_FEEDBACK_CAPABILITY(_)       (((_) >> 0) & 0x01)
      UINT32 Reserved1                                             : 2;

      /**
       * [Bit 3] The processor supports performance-energy bias preference if CPUID.06H:ECX.SETBH[bit 3] is set and it also
       * implies the presence of a new architectural MSR called IA32_ENERGY_PERF_BIAS (1B0H).
       */
      UINT32 PerformanceEnergyBiasPreference                       : 1;
#define CPUID_ECX_PERFORMANCE_ENERGY_BIAS_PREFERENCE_BIT             3
#define CPUID_ECX_PERFORMANCE_ENERGY_BIAS_PREFERENCE_MASK            0x01
#define CPUID_ECX_PERFORMANCE_ENERGY_BIAS_PREFERENCE(_)              (((_) >> 3) & 0x01)
      UINT32 Reserved2                                             : 28;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_06;

/**
 * @brief Structured Extended Feature Flags Enumeration Leaf (Output depends on ECX input value)
 *
 * When CPUID executes with EAX set to 07H and ECX = 0, the processor returns information about the maximum input value for
 * sub-leaves that contain extended feature flags.
 * When CPUID executes with EAX set to 07H and the input value of ECX is invalid (see leaf 07H entry in Table 3-8), the
 * processor returns 0 in EAX/EBX/ECX/EDX. In subleaf 0, EAX returns the maximum input value of the highest leaf 7
 * sub-leaf, and EBX, ECX & EDX contain information of extended feature flags.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the maximum input value for supported leaf 7 sub-leaves.
       */
      UINT32 NumberOfSubLeaves                                     : 32;
#define CPUID_EAX_NUMBER_OF_SUB_LEAVES_BIT                           0
#define CPUID_EAX_NUMBER_OF_SUB_LEAVES_MASK                          0xFFFFFFFF
#define CPUID_EAX_NUMBER_OF_SUB_LEAVES(_)                            (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bit 0] Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE if 1.
       */
      UINT32 Fsgsbase                                              : 1;
#define CPUID_EBX_FSGSBASE_BIT                                       0
#define CPUID_EBX_FSGSBASE_MASK                                      0x01
#define CPUID_EBX_FSGSBASE(_)                                        (((_) >> 0) & 0x01)

      /**
       * [Bit 1] IA32_TSC_ADJUST MSR is supported if 1.
       */
      UINT32 Ia32TscAdjustMsr                                      : 1;
#define CPUID_EBX_IA32_TSC_ADJUST_MSR_BIT                            1
#define CPUID_EBX_IA32_TSC_ADJUST_MSR_MASK                           0x01
#define CPUID_EBX_IA32_TSC_ADJUST_MSR(_)                             (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Supports Intel(R) Software Guard Extensions (Intel(R) SGX Extensions) if 1.
       */
      UINT32 Sgx                                                   : 1;
#define CPUID_EBX_SGX_BIT                                            2
#define CPUID_EBX_SGX_MASK                                           0x01
#define CPUID_EBX_SGX(_)                                             (((_) >> 2) & 0x01)

      /**
       * [Bit 3] BMI1.
       */
      UINT32 Bmi1                                                  : 1;
#define CPUID_EBX_BMI1_BIT                                           3
#define CPUID_EBX_BMI1_MASK                                          0x01
#define CPUID_EBX_BMI1(_)                                            (((_) >> 3) & 0x01)

      /**
       * [Bit 4] HLE.
       */
      UINT32 Hle                                                   : 1;
#define CPUID_EBX_HLE_BIT                                            4
#define CPUID_EBX_HLE_MASK                                           0x01
#define CPUID_EBX_HLE(_)                                             (((_) >> 4) & 0x01)

      /**
       * [Bit 5] AVX2.
       */
      UINT32 Avx2                                                  : 1;
#define CPUID_EBX_AVX2_BIT                                           5
#define CPUID_EBX_AVX2_MASK                                          0x01
#define CPUID_EBX_AVX2(_)                                            (((_) >> 5) & 0x01)

      /**
       * [Bit 6] x87 FPU Data Pointer updated only on x87 exceptions if 1.
       */
      UINT32 FdpExcptnOnly                                         : 1;
#define CPUID_EBX_FDP_EXCPTN_ONLY_BIT                                6
#define CPUID_EBX_FDP_EXCPTN_ONLY_MASK                               0x01
#define CPUID_EBX_FDP_EXCPTN_ONLY(_)                                 (((_) >> 6) & 0x01)

      /**
       * [Bit 7] Supports Supervisor-Mode Execution Prevention if 1.
       */
      UINT32 Smep                                                  : 1;
#define CPUID_EBX_SMEP_BIT                                           7
#define CPUID_EBX_SMEP_MASK                                          0x01
#define CPUID_EBX_SMEP(_)                                            (((_) >> 7) & 0x01)

      /**
       * [Bit 8] BMI2.
       */
      UINT32 Bmi2                                                  : 1;
#define CPUID_EBX_BMI2_BIT                                           8
#define CPUID_EBX_BMI2_MASK                                          0x01
#define CPUID_EBX_BMI2(_)                                            (((_) >> 8) & 0x01)

      /**
       * [Bit 9] Supports Enhanced REP MOVSB/STOSB if 1.
       */
      UINT32 EnhancedRepMovsbStosb                                 : 1;
#define CPUID_EBX_ENHANCED_REP_MOVSB_STOSB_BIT                       9
#define CPUID_EBX_ENHANCED_REP_MOVSB_STOSB_MASK                      0x01
#define CPUID_EBX_ENHANCED_REP_MOVSB_STOSB(_)                        (((_) >> 9) & 0x01)

      /**
       * [Bit 10] If 1, supports INVPCID instruction for system software that manages process-context identifiers.
       */
      UINT32 Invpcid                                               : 1;
#define CPUID_EBX_INVPCID_BIT                                        10
#define CPUID_EBX_INVPCID_MASK                                       0x01
#define CPUID_EBX_INVPCID(_)                                         (((_) >> 10) & 0x01)

      /**
       * [Bit 11] RTM.
       */
      UINT32 Rtm                                                   : 1;
#define CPUID_EBX_RTM_BIT                                            11
#define CPUID_EBX_RTM_MASK                                           0x01
#define CPUID_EBX_RTM(_)                                             (((_) >> 11) & 0x01)

      /**
       * [Bit 12] Supports Intel(R) Resource Director Technology (Intel(R) RDT) Monitoring capability if 1.
       */
      UINT32 RdtM                                                  : 1;
#define CPUID_EBX_RDT_M_BIT                                          12
#define CPUID_EBX_RDT_M_MASK                                         0x01
#define CPUID_EBX_RDT_M(_)                                           (((_) >> 12) & 0x01)

      /**
       * [Bit 13] Deprecates FPU CS and FPU DS values if 1.
       */
      UINT32 Deprecates                                            : 1;
#define CPUID_EBX_DEPRECATES_BIT                                     13
#define CPUID_EBX_DEPRECATES_MASK                                    0x01
#define CPUID_EBX_DEPRECATES(_)                                      (((_) >> 13) & 0x01)

      /**
       * [Bit 14] Supports Intel(R) Memory Protection Extensions if 1.
       */
      UINT32 Mpx                                                   : 1;
#define CPUID_EBX_MPX_BIT                                            14
#define CPUID_EBX_MPX_MASK                                           0x01
#define CPUID_EBX_MPX(_)                                             (((_) >> 14) & 0x01)

      /**
       * [Bit 15] Supports Intel(R) Resource Director Technology (Intel(R) RDT) Allocation capability if 1.
       */
      UINT32 Rdt                                                   : 1;
#define CPUID_EBX_RDT_BIT                                            15
#define CPUID_EBX_RDT_MASK                                           0x01
#define CPUID_EBX_RDT(_)                                             (((_) >> 15) & 0x01)

      /**
       * [Bit 16] AVX512F.
       */
      UINT32 Avx512F                                               : 1;
#define CPUID_EBX_AVX512F_BIT                                        16
#define CPUID_EBX_AVX512F_MASK                                       0x01
#define CPUID_EBX_AVX512F(_)                                         (((_) >> 16) & 0x01)

      /**
       * [Bit 17] AVX512DQ.
       */
      UINT32 Avx512Dq                                              : 1;
#define CPUID_EBX_AVX512DQ_BIT                                       17
#define CPUID_EBX_AVX512DQ_MASK                                      0x01
#define CPUID_EBX_AVX512DQ(_)                                        (((_) >> 17) & 0x01)

      /**
       * [Bit 18] RDSEED.
       */
      UINT32 Rdseed                                                : 1;
#define CPUID_EBX_RDSEED_BIT                                         18
#define CPUID_EBX_RDSEED_MASK                                        0x01
#define CPUID_EBX_RDSEED(_)                                          (((_) >> 18) & 0x01)

      /**
       * [Bit 19] ADX.
       */
      UINT32 Adx                                                   : 1;
#define CPUID_EBX_ADX_BIT                                            19
#define CPUID_EBX_ADX_MASK                                           0x01
#define CPUID_EBX_ADX(_)                                             (((_) >> 19) & 0x01)

      /**
       * [Bit 20] Supports Supervisor-Mode Access Prevention (and the CLAC/STAC instructions) if 1.
       */
      UINT32 Smap                                                  : 1;
#define CPUID_EBX_SMAP_BIT                                           20
#define CPUID_EBX_SMAP_MASK                                          0x01
#define CPUID_EBX_SMAP(_)                                            (((_) >> 20) & 0x01)

      /**
       * [Bit 21] AVX512_IFMA.
       */
      UINT32 Avx512Ifma                                            : 1;
#define CPUID_EBX_AVX512_IFMA_BIT                                    21
#define CPUID_EBX_AVX512_IFMA_MASK                                   0x01
#define CPUID_EBX_AVX512_IFMA(_)                                     (((_) >> 21) & 0x01)
      UINT32 Reserved1                                             : 1;

      /**
       * [Bit 23] CLFLUSHOPT.
       */
      UINT32 Clflushopt                                            : 1;
#define CPUID_EBX_CLFLUSHOPT_BIT                                     23
#define CPUID_EBX_CLFLUSHOPT_MASK                                    0x01
#define CPUID_EBX_CLFLUSHOPT(_)                                      (((_) >> 23) & 0x01)

      /**
       * [Bit 24] CLWB.
       */
      UINT32 Clwb                                                  : 1;
#define CPUID_EBX_CLWB_BIT                                           24
#define CPUID_EBX_CLWB_MASK                                          0x01
#define CPUID_EBX_CLWB(_)                                            (((_) >> 24) & 0x01)

      /**
       * [Bit 25] Intel Processor Trace.
       */
      UINT32 Intel                                                 : 1;
#define CPUID_EBX_INTEL_BIT                                          25
#define CPUID_EBX_INTEL_MASK                                         0x01
#define CPUID_EBX_INTEL(_)                                           (((_) >> 25) & 0x01)

      /**
       * [Bit 26] (Intel(R) Xeon Phi(TM) only).
       */
      UINT32 Avx512Pf                                              : 1;
#define CPUID_EBX_AVX512PF_BIT                                       26
#define CPUID_EBX_AVX512PF_MASK                                      0x01
#define CPUID_EBX_AVX512PF(_)                                        (((_) >> 26) & 0x01)

      /**
       * [Bit 27] (Intel(R) Xeon Phi(TM) only).
       */
      UINT32 Avx512Er                                              : 1;
#define CPUID_EBX_AVX512ER_BIT                                       27
#define CPUID_EBX_AVX512ER_MASK                                      0x01
#define CPUID_EBX_AVX512ER(_)                                        (((_) >> 27) & 0x01)

      /**
       * [Bit 28] AVX512CD.
       */
      UINT32 Avx512Cd                                              : 1;
#define CPUID_EBX_AVX512CD_BIT                                       28
#define CPUID_EBX_AVX512CD_MASK                                      0x01
#define CPUID_EBX_AVX512CD(_)                                        (((_) >> 28) & 0x01)

      /**
       * [Bit 29] Supports Intel(R) Secure Hash Algorithm Extensions (Intel(R) SHA Extensions) if 1.
       */
      UINT32 Sha                                                   : 1;
#define CPUID_EBX_SHA_BIT                                            29
#define CPUID_EBX_SHA_MASK                                           0x01
#define CPUID_EBX_SHA(_)                                             (((_) >> 29) & 0x01)

      /**
       * [Bit 30] AVX512BW.
       */
      UINT32 Avx512Bw                                              : 1;
#define CPUID_EBX_AVX512BW_BIT                                       30
#define CPUID_EBX_AVX512BW_MASK                                      0x01
#define CPUID_EBX_AVX512BW(_)                                        (((_) >> 30) & 0x01)

      /**
       * [Bit 31] AVX512VL.
       */
      UINT32 Avx512Vl                                              : 1;
#define CPUID_EBX_AVX512VL_BIT                                       31
#define CPUID_EBX_AVX512VL_MASK                                      0x01
#define CPUID_EBX_AVX512VL(_)                                        (((_) >> 31) & 0x01)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] (Intel(R) Xeon Phi(TM) only).
       */
      UINT32 Prefetchwt1                                           : 1;
#define CPUID_ECX_PREFETCHWT1_BIT                                    0
#define CPUID_ECX_PREFETCHWT1_MASK                                   0x01
#define CPUID_ECX_PREFETCHWT1(_)                                     (((_) >> 0) & 0x01)

      /**
       * [Bit 1] AVX512_VBMI.
       */
      UINT32 Avx512Vbmi                                            : 1;
#define CPUID_ECX_AVX512_VBMI_BIT                                    1
#define CPUID_ECX_AVX512_VBMI_MASK                                   0x01
#define CPUID_ECX_AVX512_VBMI(_)                                     (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Supports user-mode instruction prevention if 1.
       */
      UINT32 Umip                                                  : 1;
#define CPUID_ECX_UMIP_BIT                                           2
#define CPUID_ECX_UMIP_MASK                                          0x01
#define CPUID_ECX_UMIP(_)                                            (((_) >> 2) & 0x01)

      /**
       * [Bit 3] Supports protection keys for user-mode pages if 1.
       */
      UINT32 Pku                                                   : 1;
#define CPUID_ECX_PKU_BIT                                            3
#define CPUID_ECX_PKU_MASK                                           0x01
#define CPUID_ECX_PKU(_)                                             (((_) >> 3) & 0x01)

      /**
       * [Bit 4] If 1, OS has set CR4.PKE to enable protection keys (and the RDPKRU/WRPKRU instructions).
       */
      UINT32 Ospke                                                 : 1;
#define CPUID_ECX_OSPKE_BIT                                          4
#define CPUID_ECX_OSPKE_MASK                                         0x01
#define CPUID_ECX_OSPKE(_)                                           (((_) >> 4) & 0x01)
      UINT32 Reserved1                                             : 12;

      /**
       * [Bits 21:17] The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode.
       */
      UINT32 Mawau                                                 : 5;
#define CPUID_ECX_MAWAU_BIT                                          17
#define CPUID_ECX_MAWAU_MASK                                         0x1F
#define CPUID_ECX_MAWAU(_)                                           (((_) >> 17) & 0x1F)

      /**
       * [Bit 22] RDPID and IA32_TSC_AUX are available if 1.
       */
      UINT32 Rdpid                                                 : 1;
#define CPUID_ECX_RDPID_BIT                                          22
#define CPUID_ECX_RDPID_MASK                                         0x01
#define CPUID_ECX_RDPID(_)                                           (((_) >> 22) & 0x01)
      UINT32 Reserved2                                             : 7;

      /**
       * [Bit 30] Supports SGX Launch Configuration if 1.
       */
      UINT32 SgxLc                                                 : 1;
#define CPUID_ECX_SGX_LC_BIT                                         30
#define CPUID_ECX_SGX_LC_MASK                                        0x01
#define CPUID_ECX_SGX_LC(_)                                          (((_) >> 30) & 0x01)
      UINT32 Reserved3                                             : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_07;

/**
 * @brief Direct Cache Access Information Leaf
 *
 * When CPUID executes with EAX set to 09H, the processor returns information about Direct Cache Access capabilities.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Value of bits [31:0] of IA32_PLATFORM_DCA_CAP MSR (address 1F8H).
       */
      UINT32 Ia32PlatformDcaCap                                    : 32;
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_BIT                          0
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_MASK                         0xFFFFFFFF
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP(_)                           (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_09;

/**
 * @brief Architectural Performance Monitoring Leaf
 *
 * When CPUID executes with EAX set to 0AH, the processor returns information about support for architectural performance
 * monitoring capabilities. Architectural performance monitoring is supported if the version ID is greater than Pn 0. For
 * each version of architectural performance monitoring capability, software must enumerate this leaf to discover the
 * programming facilities and the architectural performance events available in the processor.
 *
 * @see Vol3C[23(Introduction to Virtual-Machine Extensions)]
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 7:0] Version ID of architectural performance monitoring.
       */
      UINT32 VersionIdOfArchitecturalPerformanceMonitoring         : 8;
#define CPUID_EAX_VERSION_ID_OF_ARCHITECTURAL_PERFORMANCE_MONITORING_BIT 0
#define CPUID_EAX_VERSION_ID_OF_ARCHITECTURAL_PERFORMANCE_MONITORING_MASK 0xFF
#define CPUID_EAX_VERSION_ID_OF_ARCHITECTURAL_PERFORMANCE_MONITORING(_) (((_) >> 0) & 0xFF)

      /**
       * [Bits 15:8] Number of general-purpose performance monitoring counter per logical processor.
       */
      UINT32 NumberOfPerformanceMonitoringCounterPerLogicalProcessor: 8;
#define CPUID_EAX_NUMBER_OF_PERFORMANCE_MONITORING_COUNTER_PER_LOGICAL_PROCESSOR_BIT 8
#define CPUID_EAX_NUMBER_OF_PERFORMANCE_MONITORING_COUNTER_PER_LOGICAL_PROCESSOR_MASK 0xFF
#define CPUID_EAX_NUMBER_OF_PERFORMANCE_MONITORING_COUNTER_PER_LOGICAL_PROCESSOR(_) (((_) >> 8) & 0xFF)

      /**
       * [Bits 23:16] Bit width of general-purpose, performance monitoring counter.
       */
      UINT32 BitWidthOfPerformanceMonitoringCounter                : 8;
#define CPUID_EAX_BIT_WIDTH_OF_PERFORMANCE_MONITORING_COUNTER_BIT    16
#define CPUID_EAX_BIT_WIDTH_OF_PERFORMANCE_MONITORING_COUNTER_MASK   0xFF
#define CPUID_EAX_BIT_WIDTH_OF_PERFORMANCE_MONITORING_COUNTER(_)     (((_) >> 16) & 0xFF)

      /**
       * [Bits 31:24] Length of EBX bit vector to enumerate architectural performance monitoring events.
       */
      UINT32 EbxBitVectorLength                                    : 8;
#define CPUID_EAX_EBX_BIT_VECTOR_LENGTH_BIT                          24
#define CPUID_EAX_EBX_BIT_VECTOR_LENGTH_MASK                         0xFF
#define CPUID_EAX_EBX_BIT_VECTOR_LENGTH(_)                           (((_) >> 24) & 0xFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bit 0] Core cycle event not available if 1.
       */
      UINT32 CoreCycleEventNotAvailable                            : 1;
#define CPUID_EBX_CORE_CYCLE_EVENT_NOT_AVAILABLE_BIT                 0
#define CPUID_EBX_CORE_CYCLE_EVENT_NOT_AVAILABLE_MASK                0x01
#define CPUID_EBX_CORE_CYCLE_EVENT_NOT_AVAILABLE(_)                  (((_) >> 0) & 0x01)

      /**
       * [Bit 1] Instruction retired event not available if 1.
       */
      UINT32 InstructionRetiredEventNotAvailable                   : 1;
#define CPUID_EBX_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE_BIT        1
#define CPUID_EBX_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE_MASK       0x01
#define CPUID_EBX_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE(_)         (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Reference cycles event not available if 1.
       */
      UINT32 ReferenceCyclesEventNotAvailable                      : 1;
#define CPUID_EBX_REFERENCE_CYCLES_EVENT_NOT_AVAILABLE_BIT           2
#define CPUID_EBX_REFERENCE_CYCLES_EVENT_NOT_AVAILABLE_MASK          0x01
#define CPUID_EBX_REFERENCE_CYCLES_EVENT_NOT_AVAILABLE(_)            (((_) >> 2) & 0x01)

      /**
       * [Bit 3] Last-level cache reference event not available if 1.
       */
      UINT32 LastLevelCacheReferenceEventNotAvailable              : 1;
#define CPUID_EBX_LAST_LEVEL_CACHE_REFERENCE_EVENT_NOT_AVAILABLE_BIT 3
#define CPUID_EBX_LAST_LEVEL_CACHE_REFERENCE_EVENT_NOT_AVAILABLE_MASK 0x01
#define CPUID_EBX_LAST_LEVEL_CACHE_REFERENCE_EVENT_NOT_AVAILABLE(_)  (((_) >> 3) & 0x01)

      /**
       * [Bit 4] Last-level cache misses event not available if 1.
       */
      UINT32 LastLevelCacheMissesEventNotAvailable                 : 1;
#define CPUID_EBX_LAST_LEVEL_CACHE_MISSES_EVENT_NOT_AVAILABLE_BIT    4
#define CPUID_EBX_LAST_LEVEL_CACHE_MISSES_EVENT_NOT_AVAILABLE_MASK   0x01
#define CPUID_EBX_LAST_LEVEL_CACHE_MISSES_EVENT_NOT_AVAILABLE(_)     (((_) >> 4) & 0x01)

      /**
       * [Bit 5] Branch instruction retired event not available if 1.
       */
      UINT32 BranchInstructionRetiredEventNotAvailable             : 1;
#define CPUID_EBX_BRANCH_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE_BIT 5
#define CPUID_EBX_BRANCH_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE_MASK 0x01
#define CPUID_EBX_BRANCH_INSTRUCTION_RETIRED_EVENT_NOT_AVAILABLE(_)  (((_) >> 5) & 0x01)

      /**
       * [Bit 6] Branch mispredict retired event not available if 1.
       */
      UINT32 BranchMispredictRetiredEventNotAvailable              : 1;
#define CPUID_EBX_BRANCH_MISPREDICT_RETIRED_EVENT_NOT_AVAILABLE_BIT  6
#define CPUID_EBX_BRANCH_MISPREDICT_RETIRED_EVENT_NOT_AVAILABLE_MASK 0x01
#define CPUID_EBX_BRANCH_MISPREDICT_RETIRED_EVENT_NOT_AVAILABLE(_)   (((_) >> 6) & 0x01)
      UINT32 Reserved1                                             : 25;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 4:0] Number of fixed-function performance counters (if Version ID > 1).
       */
      UINT32 NumberOfFixedFunctionPerformanceCounters              : 5;
#define CPUID_EDX_NUMBER_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS_BIT  0
#define CPUID_EDX_NUMBER_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS_MASK 0x1F
#define CPUID_EDX_NUMBER_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS(_)   (((_) >> 0) & 0x1F)

      /**
       * [Bits 12:5] Bit width of fixed-function performance counters (if Version ID > 1).
       */
      UINT32 BitWidthOfFixedFunctionPerformanceCounters            : 8;
#define CPUID_EDX_BIT_WIDTH_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS_BIT 5
#define CPUID_EDX_BIT_WIDTH_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS_MASK 0xFF
#define CPUID_EDX_BIT_WIDTH_OF_FIXED_FUNCTION_PERFORMANCE_COUNTERS(_) (((_) >> 5) & 0xFF)
      UINT32 Reserved1                                             : 2;

      /**
       * [Bit 15] AnyThread deprecation.
       */
      UINT32 AnyThreadDeprecation                                  : 1;
#define CPUID_EDX_ANY_THREAD_DEPRECATION_BIT                         15
#define CPUID_EDX_ANY_THREAD_DEPRECATION_MASK                        0x01
#define CPUID_EDX_ANY_THREAD_DEPRECATION(_)                          (((_) >> 15) & 0x01)
      UINT32 Reserved2                                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0A;

/**
 * @brief Extended Topology Enumeration Leaf
 *
 * When CPUID executes with EAX set to 0BH, the processor returns information about extended topology enumeration data.
 * Software must detect the presence of CPUID leaf 0BH by verifying
 * - the highest leaf index supported by CPUID is >= 0BH, and
 * - CPUID.0BH:EBX[15:0] reports a non-zero value.
 *
 * @note Most of Leaf 0BH output depends on the initial value in ECX. The EDX output of leaf 0BH is always valid and does
 *       not vary with input value in ECX. Output value in ECX[7:0] always equals input value in ECX[7:0]. Sub-leaf index 0
 *       enumerates SMT level. Each subsequent higher sub-leaf index enumerates a higherlevel topological entity in hierarchical
 *       order. For sub-leaves that return an invalid level-type of 0 in ECX[15:8]; EAX and EBX will return 0. If an input value
 *       n in ECX returns the invalid level-type of 0 in ECX[15:8], other input values with ECX > n also return 0 in ECX[15:8].
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 4:0] Number of bits to shift right on x2APIC ID to get a unique topology ID of the next level type. All logical
       * processors with the same next level ID share current level.
       *
       * @note Software should use this field (EAX[4:0]) to enumerate processor topology of the system.
       */
      UINT32 X2ApicIdToUniqueTopologyIdShift                       : 5;
#define CPUID_EAX_X2APIC_ID_TO_UNIQUE_TOPOLOGY_ID_SHIFT_BIT          0
#define CPUID_EAX_X2APIC_ID_TO_UNIQUE_TOPOLOGY_ID_SHIFT_MASK         0x1F
#define CPUID_EAX_X2APIC_ID_TO_UNIQUE_TOPOLOGY_ID_SHIFT(_)           (((_) >> 0) & 0x1F)
      UINT32 Reserved1                                             : 27;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Number of logical processors at this level type. The number reflects configuration as shipped by Intel.
       *
       * @note Software must not use EBX[15:0] to enumerate processor topology of the system. This value in this field
       *       (EBX[15:0]) is only intended for display/diagnostic purposes. The actual number of logical processors available to
       *       BIOS/OS/Applications may be different from the value of EBX[15:0], depending on software and platform hardware
       *       configurations.
       */
      UINT32 NumberOfLogicalProcessorsAtThisLevelType              : 16;
#define CPUID_EBX_NUMBER_OF_LOGICAL_PROCESSORS_AT_THIS_LEVEL_TYPE_BIT 0
#define CPUID_EBX_NUMBER_OF_LOGICAL_PROCESSORS_AT_THIS_LEVEL_TYPE_MASK 0xFFFF
#define CPUID_EBX_NUMBER_OF_LOGICAL_PROCESSORS_AT_THIS_LEVEL_TYPE(_) (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 7:0] Level number. Same value in ECX input.
       */
      UINT32 LevelNumber                                           : 8;
#define CPUID_ECX_LEVEL_NUMBER_BIT                                   0
#define CPUID_ECX_LEVEL_NUMBER_MASK                                  0xFF
#define CPUID_ECX_LEVEL_NUMBER(_)                                    (((_) >> 0) & 0xFF)

      /**
       * [Bits 15:8] Level type.
       *
       * @note The value of the "level type" field is not related to level numbers in any way, higher "level type" values do not
       *       mean higher levels. Level type field has the following encoding:
       *       - 0: Invalid.
       *       - 1: SMT.
       *       - 2: Core.
       *       - 3-255: Reserved.
       */
      UINT32 LevelType                                             : 8;
#define CPUID_ECX_LEVEL_TYPE_BIT                                     8
#define CPUID_ECX_LEVEL_TYPE_MASK                                    0xFF
#define CPUID_ECX_LEVEL_TYPE(_)                                      (((_) >> 8) & 0xFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] x2APIC ID the current logical processor.
       */
      UINT32 X2ApicId                                              : 32;
#define CPUID_EDX_X2APIC_ID_BIT                                      0
#define CPUID_EDX_X2APIC_ID_MASK                                     0xFFFFFFFF
#define CPUID_EDX_X2APIC_ID(_)                                       (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0B;

/**
 * @defgroup CPUID_EAX_0D \
 *           EAX = 0x0D
 *
 * When CPUID executes with EAX set to 0DH and ECX = 0, the processor returns information about the bit-vector
 * representation of all processor state extensions that are supported in the processor and storage size requirements of
 * the XSAVE/XRSTOR area.
 * When CPUID executes with EAX set to 0DH and ECX = n (n > 1, and is a valid sub-leaf index), the processor returns
 * information about the size and offset of each processor extended state save area within the XSAVE/XRSTOR area. Software
 * can use the forward-extendable technique depicted below to query the valid sub-leaves and obtain size and offset
 * information for each processor extended state save area:
 * <pre> For i = 2 to 62 // sub-leaf 1 is reserved IF (CPUID.(EAX=0DH, ECX=0):VECTOR[i] = 1) // VECTOR is the 64-bit value
 * of EDX:EAX Execute CPUID.(EAX=0DH, ECX = i) to examine size and offset for sub-leaf i; FI; </pre>
 * @{
 */
/**
 * @brief Processor Extended State Enumeration Main Leaf (EAX = 0DH, ECX = 0)
 */
typedef struct
{
  /**
   * @brief Reports the supported bits of the lower 32 bits of XCR0. XCR0[n] can be set to 1 only if EAX[n] is 1
   */
  union
  {
    struct
    {
      /**
       * [Bit 0] x87 state.
       */
      UINT32 X87State                                              : 1;
#define CPUID_EAX_X87_STATE_BIT                                      0
#define CPUID_EAX_X87_STATE_MASK                                     0x01
#define CPUID_EAX_X87_STATE(_)                                       (((_) >> 0) & 0x01)

      /**
       * [Bit 1] SSE state.
       */
      UINT32 SseState                                              : 1;
#define CPUID_EAX_SSE_STATE_BIT                                      1
#define CPUID_EAX_SSE_STATE_MASK                                     0x01
#define CPUID_EAX_SSE_STATE(_)                                       (((_) >> 1) & 0x01)

      /**
       * [Bit 2] AVX state.
       */
      UINT32 AvxState                                              : 1;
#define CPUID_EAX_AVX_STATE_BIT                                      2
#define CPUID_EAX_AVX_STATE_MASK                                     0x01
#define CPUID_EAX_AVX_STATE(_)                                       (((_) >> 2) & 0x01)

      /**
       * [Bits 4:3] MPX state.
       */
      UINT32 MpxState                                              : 2;
#define CPUID_EAX_MPX_STATE_BIT                                      3
#define CPUID_EAX_MPX_STATE_MASK                                     0x03
#define CPUID_EAX_MPX_STATE(_)                                       (((_) >> 3) & 0x03)

      /**
       * [Bits 7:5] AVX-512 state.
       */
      UINT32 Avx512State                                           : 3;
#define CPUID_EAX_AVX_512_STATE_BIT                                  5
#define CPUID_EAX_AVX_512_STATE_MASK                                 0x07
#define CPUID_EAX_AVX_512_STATE(_)                                   (((_) >> 5) & 0x07)

      /**
       * [Bit 8] Used for IA32_XSS.
       */
      UINT32 UsedForIa32Xss1                                       : 1;
#define CPUID_EAX_USED_FOR_IA32_XSS_1_BIT                            8
#define CPUID_EAX_USED_FOR_IA32_XSS_1_MASK                           0x01
#define CPUID_EAX_USED_FOR_IA32_XSS_1(_)                             (((_) >> 8) & 0x01)

      /**
       * [Bit 9] PKRU state.
       */
      UINT32 PkruState                                             : 1;
#define CPUID_EAX_PKRU_STATE_BIT                                     9
#define CPUID_EAX_PKRU_STATE_MASK                                    0x01
#define CPUID_EAX_PKRU_STATE(_)                                      (((_) >> 9) & 0x01)
      UINT32 Reserved1                                             : 3;

      /**
       * [Bit 13] Used for IA32_XSS.
       */
      UINT32 UsedForIa32Xss2                                       : 1;
#define CPUID_EAX_USED_FOR_IA32_XSS_2_BIT                            13
#define CPUID_EAX_USED_FOR_IA32_XSS_2_MASK                           0x01
#define CPUID_EAX_USED_FOR_IA32_XSS_2(_)                             (((_) >> 13) & 0x01)
      UINT32 Reserved2                                             : 18;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) required by enabled features in XCR0.
       * May be different than ECX if some features at the end of the XSAVE save area are not enabled.
       */
      UINT32 MaxSizeRequiredByEnabledFeaturesInXcr0                : 32;
#define CPUID_EBX_MAX_SIZE_REQUIRED_BY_ENABLED_FEATURES_IN_XCR0_BIT  0
#define CPUID_EBX_MAX_SIZE_REQUIRED_BY_ENABLED_FEATURES_IN_XCR0_MASK 0xFFFFFFFF
#define CPUID_EBX_MAX_SIZE_REQUIRED_BY_ENABLED_FEATURES_IN_XCR0(_)   (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) of the XSAVE/XRSTOR save area
       * required by all supported features in the processor, i.e., all the valid bit fields in XCR0.
       */
      UINT32 MaxSizeOfXsaveXrstorSaveArea                          : 32;
#define CPUID_ECX_MAX_SIZE_OF_XSAVE_XRSTOR_SAVE_AREA_BIT             0
#define CPUID_ECX_MAX_SIZE_OF_XSAVE_XRSTOR_SAVE_AREA_MASK            0xFFFFFFFF
#define CPUID_ECX_MAX_SIZE_OF_XSAVE_XRSTOR_SAVE_AREA(_)              (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the supported bits of the upper 32 bits of XCR0. XCR0[n+32] can be set to 1 only if EDX[n] is 1.
       */
      UINT32 Xcr0SupportedBits                                     : 32;
#define CPUID_EDX_XCR0_SUPPORTED_BITS_BIT                            0
#define CPUID_EDX_XCR0_SUPPORTED_BITS_MASK                           0xFFFFFFFF
#define CPUID_EDX_XCR0_SUPPORTED_BITS(_)                             (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_00;

/**
 * @brief Direct Cache Access Information Leaf
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;

      /**
       * [Bit 1] Supports XSAVEC and the compacted form of XRSTOR if set.
       */
      UINT32 SupportsXsavecAndCompactedXrstor                      : 1;
#define CPUID_EAX_SUPPORTS_XSAVEC_AND_COMPACTED_XRSTOR_BIT           1
#define CPUID_EAX_SUPPORTS_XSAVEC_AND_COMPACTED_XRSTOR_MASK          0x01
#define CPUID_EAX_SUPPORTS_XSAVEC_AND_COMPACTED_XRSTOR(_)            (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Supports XGETBV with ECX = 1 if set.
       */
      UINT32 SupportsXgetbvWithEcx1                                : 1;
#define CPUID_EAX_SUPPORTS_XGETBV_WITH_ECX_1_BIT                     2
#define CPUID_EAX_SUPPORTS_XGETBV_WITH_ECX_1_MASK                    0x01
#define CPUID_EAX_SUPPORTS_XGETBV_WITH_ECX_1(_)                      (((_) >> 2) & 0x01)

      /**
       * [Bit 3] Supports XSAVES/XRSTORS and IA32_XSS if set.
       */
      UINT32 SupportsXsaveXrstorAndIa32Xss                         : 1;
#define CPUID_EAX_SUPPORTS_XSAVE_XRSTOR_AND_IA32_XSS_BIT             3
#define CPUID_EAX_SUPPORTS_XSAVE_XRSTOR_AND_IA32_XSS_MASK            0x01
#define CPUID_EAX_SUPPORTS_XSAVE_XRSTOR_AND_IA32_XSS(_)              (((_) >> 3) & 0x01)
      UINT32 Reserved2                                             : 28;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] The size in bytes of the XSAVE area containing all states enabled by XCRO | IA32_XSS.
       */
      UINT32 SizeOfXsaveAread                                      : 32;
#define CPUID_EBX_SIZE_OF_XSAVE_AREAD_BIT                            0
#define CPUID_EBX_SIZE_OF_XSAVE_AREAD_MASK                           0xFFFFFFFF
#define CPUID_EBX_SIZE_OF_XSAVE_AREAD(_)                             (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 7:0] Used for XCR0.
       */
      UINT32 UsedForXcr01                                          : 8;
#define CPUID_ECX_USED_FOR_XCR0_1_BIT                                0
#define CPUID_ECX_USED_FOR_XCR0_1_MASK                               0xFF
#define CPUID_ECX_USED_FOR_XCR0_1(_)                                 (((_) >> 0) & 0xFF)

      /**
       * [Bit 8] PT state.
       */
      UINT32 PtState                                               : 1;
#define CPUID_ECX_PT_STATE_BIT                                       8
#define CPUID_ECX_PT_STATE_MASK                                      0x01
#define CPUID_ECX_PT_STATE(_)                                        (((_) >> 8) & 0x01)

      /**
       * [Bit 9] Used for XCR0.
       */
      UINT32 UsedForXcr02                                          : 1;
#define CPUID_ECX_USED_FOR_XCR0_2_BIT                                9
#define CPUID_ECX_USED_FOR_XCR0_2_MASK                               0x01
#define CPUID_ECX_USED_FOR_XCR0_2(_)                                 (((_) >> 9) & 0x01)
      UINT32 Reserved1                                             : 3;

      /**
       * [Bit 13] HWP state.
       */
      UINT32 HwpState                                              : 1;
#define CPUID_ECX_HWP_STATE_BIT                                      13
#define CPUID_ECX_HWP_STATE_MASK                                     0x01
#define CPUID_ECX_HWP_STATE(_)                                       (((_) >> 13) & 0x01)
      UINT32 Reserved2                                             : 18;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_01;

/**
 * @brief Processor Extended State Enumeration Sub-leaves (EAX = 0DH, ECX = n, n > 1)
 *
 * @note Leaf 0DH output depends on the initial value in ECX. Each sub-leaf index (starting at position 2) is supported if
 *       it corresponds to a supported bit in either the XCR0 register or the IA32_XSS MSR.
 *       If ECX contains an invalid sub-leaf index, EAX/EBX/ECX/EDX return 0. Sub-leaf n (0 <= n <= 31) is invalid if sub-leaf 0
 *       returns 0 in EAX[n] and sub-leaf 1 returns 0 in ECX[n]. Sub-leaf n (32 <= n <= 63) is invalid if sub-leaf 0 returns 0 in
 *       EDX[n-32] and sub-leaf 1 returns 0 in EDX[n-32].
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] The size in bytes (from the offset specified in EBX) of the save area for an extended state feature
       * associated with a valid sub-leaf index, n.
       */
      UINT32 Ia32PlatformDcaCap                                    : 32;
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_BIT                          0
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_MASK                         0xFFFFFFFF
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP(_)                           (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] The offset in bytes of this extended state component's save area from the beginning of the XSAVE/XRSTOR
       * area.
       * This field reports 0 if the sub-leaf index, n, does not map to a valid bit in the XCR0 register.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] Is set if the bit n (corresponding to the sub-leaf index) is supported in the IA32_XSS MSR; it is clear if bit n
       * is instead supported in XCR0.
       */
      UINT32 Ecx2                                                  : 1;
#define CPUID_ECX_ECX_2_BIT                                          0
#define CPUID_ECX_ECX_2_MASK                                         0x01
#define CPUID_ECX_ECX_2(_)                                           (((_) >> 0) & 0x01)

      /**
       * [Bit 1] Is set if, when the compacted format of an XSAVE area is used, this extended state component located on the next
       * 64-byte boundary following the preceding state component (otherwise, it is located immediately following the preceding
       * state component).
       */
      UINT32 Ecx1                                                  : 1;
#define CPUID_ECX_ECX_1_BIT                                          1
#define CPUID_ECX_ECX_1_MASK                                         0x01
#define CPUID_ECX_ECX_1(_)                                           (((_) >> 1) & 0x01)
      UINT32 Reserved1                                             : 30;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] This field reports 0 if the sub-leaf index, n, is invalid; otherwise it is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_N;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_0F \
 *           EAX = 0x0F
 *
 * When CPUID executes with EAX set to 0FH and ECX = 0, the processor returns information about the bit-vector
 * representation of QoS monitoring resource types that are supported in the processor and maximum range of RMID values the
 * processor can use to monitor of any supported resource types. Each bit, starting from bit 1, corresponds to a specific
 * resource type if the bit is set. The bit position corresponds to the sub-leaf index (or ResID) that software must use to
 * query QoS monitoring capability available for that type. See Table 3-8.
 * When CPUID executes with EAX set to 0FH and ECX = n (n >= 1, and is a valid ResID), the processor returns information
 * software can use to program IA32_PQR_ASSOC, IA32_QM_EVTSEL MSRs before reading QoS data from the IA32_QM_CTR MSR.
 * @{
 */
/**
 * @brief Intel Resource Director Technology (Intel RDT) Monitoring Enumeration Sub-leaf (EAX = 0FH, ECX = 0)
 *
 * @note Leaf 0FH output depends on the initial value in ECX. Sub-leaf index 0 reports valid resource type starting at bit
 *       position 1 of EDX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Maximum range (zero-based) of RMID within this physical processor of all types.
       */
      UINT32 RmidMaxRange                                          : 32;
#define CPUID_EBX_RMID_MAX_RANGE_BIT                                 0
#define CPUID_EBX_RMID_MAX_RANGE_MASK                                0xFFFFFFFF
#define CPUID_EBX_RMID_MAX_RANGE(_)                                  (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;

      /**
       * [Bit 1] Supports L3 Cache Intel RDT Monitoring if 1.
       */
      UINT32 SupportsL3CacheIntelRdtMonitoring                     : 1;
#define CPUID_EDX_SUPPORTS_L3_CACHE_INTEL_RDT_MONITORING_BIT         1
#define CPUID_EDX_SUPPORTS_L3_CACHE_INTEL_RDT_MONITORING_MASK        0x01
#define CPUID_EDX_SUPPORTS_L3_CACHE_INTEL_RDT_MONITORING(_)          (((_) >> 1) & 0x01)
      UINT32 Reserved2                                             : 30;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0F_ECX_00;

/**
 * @brief L3 Cache Intel RDT Monitoring Capability Enumeration Sub-leaf (EAX = 0FH, ECX = 1)
 *
 * @note Leaf 0FH output depends on the initial value in ECX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Conversion factor from reported IA32_QM_CTR value to occupancy metric (bytes).
       */
      UINT32 ConversionFactor                                      : 32;
#define CPUID_EBX_CONVERSION_FACTOR_BIT                              0
#define CPUID_EBX_CONVERSION_FACTOR_MASK                             0xFFFFFFFF
#define CPUID_EBX_CONVERSION_FACTOR(_)                               (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Maximum range (zero-based) of RMID within this physical processor of all types.
       */
      UINT32 RmidMaxRange                                          : 32;
#define CPUID_ECX_RMID_MAX_RANGE_BIT                                 0
#define CPUID_ECX_RMID_MAX_RANGE_MASK                                0xFFFFFFFF
#define CPUID_ECX_RMID_MAX_RANGE(_)                                  (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bit 0] Supports L3 occupancy monitoring if 1.
       */
      UINT32 SupportsL3OccupancyMonitoring                         : 1;
#define CPUID_EDX_SUPPORTS_L3_OCCUPANCY_MONITORING_BIT               0
#define CPUID_EDX_SUPPORTS_L3_OCCUPANCY_MONITORING_MASK              0x01
#define CPUID_EDX_SUPPORTS_L3_OCCUPANCY_MONITORING(_)                (((_) >> 0) & 0x01)

      /**
       * [Bit 1] Supports L3 Total Bandwidth monitoring if 1.
       */
      UINT32 SupportsL3TotalBandwidthMonitoring                    : 1;
#define CPUID_EDX_SUPPORTS_L3_TOTAL_BANDWIDTH_MONITORING_BIT         1
#define CPUID_EDX_SUPPORTS_L3_TOTAL_BANDWIDTH_MONITORING_MASK        0x01
#define CPUID_EDX_SUPPORTS_L3_TOTAL_BANDWIDTH_MONITORING(_)          (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Supports L3 Local Bandwidth monitoring if 1.
       */
      UINT32 SupportsL3LocalBandwidthMonitoring                    : 1;
#define CPUID_EDX_SUPPORTS_L3_LOCAL_BANDWIDTH_MONITORING_BIT         2
#define CPUID_EDX_SUPPORTS_L3_LOCAL_BANDWIDTH_MONITORING_MASK        0x01
#define CPUID_EDX_SUPPORTS_L3_LOCAL_BANDWIDTH_MONITORING(_)          (((_) >> 2) & 0x01)
      UINT32 Reserved1                                             : 29;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0F_ECX_01;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_10 \
 *           EAX = 0x10
 *
 * When CPUID executes with EAX set to 10H and ECX = 0, the processor returns information about the bit-vector
 * representation of QoS Enforcement resource types that are supported in the processor. Each bit, starting from bit 1,
 * corresponds to a specific resource type if the bit is set. The bit position corresponds to the sub-leaf index (or ResID)
 * that software must use to query QoS enforcement capability available for that type.
 * When CPUID executes with EAX set to 10H and ECX = n (n >= 1, and is a valid ResID), the processor returns information
 * about available classes of service and range of QoS mask MSRs that software can use to configure each class of services
 * using capability bit masks in the QoS Mask registers, IA32_resourceType_Mask_n.
 * @{
 */
/**
 * @brief Intel Resource Director Technology (Intel RDT) Allocation Enumeration Sub-leaf (EAX = 10H, ECX = 0)
 *
 * @note Leaf 10H output depends on the initial value in ECX. Sub-leaf index 0 reports valid resource identification
 *       (ResID) starting at bit position 1 of EBX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Value of bits [31:0] of IA32_PLATFORM_DCA_CAP MSR (address 1F8H).
       */
      UINT32 Ia32PlatformDcaCap                                    : 32;
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_BIT                          0
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP_MASK                         0xFFFFFFFF
#define CPUID_EAX_IA32_PLATFORM_DCA_CAP(_)                           (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;

      /**
       * [Bit 1] Supports L3 Cache Allocation Technology if 1.
       */
      UINT32 SupportsL3CacheAllocationTechnology                   : 1;
#define CPUID_EBX_SUPPORTS_L3_CACHE_ALLOCATION_TECHNOLOGY_BIT        1
#define CPUID_EBX_SUPPORTS_L3_CACHE_ALLOCATION_TECHNOLOGY_MASK       0x01
#define CPUID_EBX_SUPPORTS_L3_CACHE_ALLOCATION_TECHNOLOGY(_)         (((_) >> 1) & 0x01)

      /**
       * [Bit 2] Supports L2 Cache Allocation Technology if 1.
       */
      UINT32 SupportsL2CacheAllocationTechnology                   : 1;
#define CPUID_EBX_SUPPORTS_L2_CACHE_ALLOCATION_TECHNOLOGY_BIT        2
#define CPUID_EBX_SUPPORTS_L2_CACHE_ALLOCATION_TECHNOLOGY_MASK       0x01
#define CPUID_EBX_SUPPORTS_L2_CACHE_ALLOCATION_TECHNOLOGY(_)         (((_) >> 2) & 0x01)

      /**
       * [Bit 3] Supports Memory Bandwidth Allocation if 1.
       */
      UINT32 SupportsMemoryBandwidthAllocation                     : 1;
#define CPUID_EBX_SUPPORTS_MEMORY_BANDWIDTH_ALLOCATION_BIT           3
#define CPUID_EBX_SUPPORTS_MEMORY_BANDWIDTH_ALLOCATION_MASK          0x01
#define CPUID_EBX_SUPPORTS_MEMORY_BANDWIDTH_ALLOCATION(_)            (((_) >> 3) & 0x01)
      UINT32 Reserved2                                             : 28;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_00;

/**
 * @brief L3 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 1)
 *
 * @note Leaf 10H output depends on the initial value in ECX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 4:0] Length of the capacity bit mask for the corresponding ResID using minus-one notation.
       */
      UINT32 LengthOfCapacityBitMask                               : 5;
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK_BIT                    0
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK_MASK                   0x1F
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK(_)                     (((_) >> 0) & 0x1F)
      UINT32 Reserved1                                             : 27;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Bit-granular map of isolation/contention of allocation units.
       */
      UINT32 Ebx0                                                  : 32;
#define CPUID_EBX_EBX_0_BIT                                          0
#define CPUID_EBX_EBX_0_MASK                                         0xFFFFFFFF
#define CPUID_EBX_EBX_0(_)                                           (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 2;

      /**
       * [Bit 2] Code and Data Prioritization Technology supported if 1.
       */
      UINT32 CodeAndDataPriorizationTechnologySupported            : 1;
#define CPUID_ECX_CODE_AND_DATA_PRIORIZATION_TECHNOLOGY_SUPPORTED_BIT 2
#define CPUID_ECX_CODE_AND_DATA_PRIORIZATION_TECHNOLOGY_SUPPORTED_MASK 0x01
#define CPUID_ECX_CODE_AND_DATA_PRIORIZATION_TECHNOLOGY_SUPPORTED(_) (((_) >> 2) & 0x01)
      UINT32 Reserved2                                             : 29;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Highest COS number supported for this ResID.
       */
      UINT32 HighestCosNumberSupported                             : 16;
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_BIT                   0
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_MASK                  0xFFFF
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED(_)                    (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_01;

/**
 * @brief L2 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 2)
 *
 * @note Leaf 10H output depends on the initial value in ECX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 4:0] Length of the capacity bit mask for the corresponding ResID using minus-one notation.
       */
      UINT32 LengthOfCapacityBitMask                               : 5;
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK_BIT                    0
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK_MASK                   0x1F
#define CPUID_EAX_LENGTH_OF_CAPACITY_BIT_MASK(_)                     (((_) >> 0) & 0x1F)
      UINT32 Reserved1                                             : 27;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Bit-granular map of isolation/contention of allocation units.
       */
      UINT32 Ebx0                                                  : 32;
#define CPUID_EBX_EBX_0_BIT                                          0
#define CPUID_EBX_EBX_0_MASK                                         0xFFFFFFFF
#define CPUID_EBX_EBX_0(_)                                           (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Highest COS number supported for this ResID.
       */
      UINT32 HighestCosNumberSupported                             : 16;
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_BIT                   0
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_MASK                  0xFFFF
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED(_)                    (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_02;

/**
 * @brief Memory Bandwidth Allocation Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 3)
 *
 * @note Leaf 10H output depends on the initial value in ECX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 11:0] Reports the maximum MBA throttling value supported for the corresponding ResID using minus-one notation.
       */
      UINT32 MaxMbaThrottlingValue                                 : 12;
#define CPUID_EAX_MAX_MBA_THROTTLING_VALUE_BIT                       0
#define CPUID_EAX_MAX_MBA_THROTTLING_VALUE_MASK                      0xFFF
#define CPUID_EAX_MAX_MBA_THROTTLING_VALUE(_)                        (((_) >> 0) & 0xFFF)
      UINT32 Reserved1                                             : 20;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 2;

      /**
       * [Bit 2] Reports whether the response of the delay values is linear.
       */
      UINT32 ResponseOfDelayIsLinear                               : 1;
#define CPUID_ECX_RESPONSE_OF_DELAY_IS_LINEAR_BIT                    2
#define CPUID_ECX_RESPONSE_OF_DELAY_IS_LINEAR_MASK                   0x01
#define CPUID_ECX_RESPONSE_OF_DELAY_IS_LINEAR(_)                     (((_) >> 2) & 0x01)
      UINT32 Reserved2                                             : 29;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Highest COS number supported for this ResID.
       */
      UINT32 HighestCosNumberSupported                             : 16;
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_BIT                   0
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED_MASK                  0xFFFF
#define CPUID_EDX_HIGHEST_COS_NUMBER_SUPPORTED(_)                    (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_03;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_12 \
 *           EAX = 0x12
 *
 * When CPUID executes with EAX set to 12H and ECX = 0H, the processor returns information about Intel SGX capabilities.
 * When CPUID executes with EAX set to 12H and ECX = 1H, the processor returns information about Intel SGX attributes.
 * When CPUID executes with EAX set to 12H and ECX = n (n > 1), the processor returns information about Intel SGX Enclave
 * Page Cache.
 * @{
 */
/**
 * @brief Intel SGX Capability Enumeration Leaf, sub-leaf 0 (EAX = 12H, ECX = 0)
 *
 * @note Leaf 12H sub-leaf 0 (ECX = 0) is supported if CPUID.(EAX=07H, ECX=0H):EBX[SGX] = 1.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bit 0] If 1, Indicates Intel SGX supports the collection of SGX1 leaf functions.
       */
      UINT32 Sgx1                                                  : 1;
#define CPUID_EAX_SGX1_BIT                                           0
#define CPUID_EAX_SGX1_MASK                                          0x01
#define CPUID_EAX_SGX1(_)                                            (((_) >> 0) & 0x01)

      /**
       * [Bit 1] If 1, Indicates Intel SGX supports the collection of SGX2 leaf functions.
       */
      UINT32 Sgx2                                                  : 1;
#define CPUID_EAX_SGX2_BIT                                           1
#define CPUID_EAX_SGX2_MASK                                          0x01
#define CPUID_EAX_SGX2(_)                                            (((_) >> 1) & 0x01)
      UINT32 Reserved1                                             : 3;

      /**
       * [Bit 5] If 1, indicates Intel SGX supports ENCLV instruction leaves EINCVIRTCHILD, EDECVIRTCHILD, and ESETCONTEXT.
       */
      UINT32 SgxEnclvAdvanced                                      : 1;
#define CPUID_EAX_SGX_ENCLV_ADVANCED_BIT                             5
#define CPUID_EAX_SGX_ENCLV_ADVANCED_MASK                            0x01
#define CPUID_EAX_SGX_ENCLV_ADVANCED(_)                              (((_) >> 5) & 0x01)

      /**
       * [Bit 6] If 1, indicates Intel SGX supports ENCLS instruction leaves ETRACKC, ERDINFO, ELDBC, and ELDUC.
       */
      UINT32 SgxEnclsAdvanced                                      : 1;
#define CPUID_EAX_SGX_ENCLS_ADVANCED_BIT                             6
#define CPUID_EAX_SGX_ENCLS_ADVANCED_MASK                            0x01
#define CPUID_EAX_SGX_ENCLS_ADVANCED(_)                              (((_) >> 6) & 0x01)
      UINT32 Reserved2                                             : 25;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Bit vector of supported extended SGX features.
       */
      UINT32 Miscselect                                            : 32;
#define CPUID_EBX_MISCSELECT_BIT                                     0
#define CPUID_EBX_MISCSELECT_MASK                                    0xFFFFFFFF
#define CPUID_EBX_MISCSELECT(_)                                      (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 7:0] The maximum supported enclave size in non-64-bit mode is 2^(EDX[7:0]).
       */
      UINT32 MaxEnclaveSizeNot64                                   : 8;
#define CPUID_EDX_MAX_ENCLAVE_SIZE_NOT64_BIT                         0
#define CPUID_EDX_MAX_ENCLAVE_SIZE_NOT64_MASK                        0xFF
#define CPUID_EDX_MAX_ENCLAVE_SIZE_NOT64(_)                          (((_) >> 0) & 0xFF)

      /**
       * [Bits 15:8] The maximum supported enclave size in 64-bit mode is 2^(EDX[15:8]).
       */
      UINT32 MaxEnclaveSize64                                      : 8;
#define CPUID_EDX_MAX_ENCLAVE_SIZE_64_BIT                            8
#define CPUID_EDX_MAX_ENCLAVE_SIZE_64_MASK                           0xFF
#define CPUID_EDX_MAX_ENCLAVE_SIZE_64(_)                             (((_) >> 8) & 0xFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_00;

/**
 * @brief Intel SGX Attributes Enumeration Leaf, sub-leaf 1 (EAX = 12H, ECX = 1)
 *
 * @note Leaf 12H sub-leaf 1 (ECX = 1) is supported if CPUID.(EAX=07H, ECX=0H):EBX[SGX] = 1.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the valid bits of SECS.ATTRIBUTES[31:0] that software can set with ECREATE.
       */
      UINT32 ValidSecsAttributes0                                  : 32;
#define CPUID_EAX_VALID_SECS_ATTRIBUTES_0_BIT                        0
#define CPUID_EAX_VALID_SECS_ATTRIBUTES_0_MASK                       0xFFFFFFFF
#define CPUID_EAX_VALID_SECS_ATTRIBUTES_0(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the valid bits of SECS.ATTRIBUTES[63:32] that software can set with ECREATE.
       */
      UINT32 ValidSecsAttributes1                                  : 32;
#define CPUID_EBX_VALID_SECS_ATTRIBUTES_1_BIT                        0
#define CPUID_EBX_VALID_SECS_ATTRIBUTES_1_MASK                       0xFFFFFFFF
#define CPUID_EBX_VALID_SECS_ATTRIBUTES_1(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the valid bits of SECS.ATTRIBUTES[95:64] that software can set with ECREATE.
       */
      UINT32 ValidSecsAttributes2                                  : 32;
#define CPUID_ECX_VALID_SECS_ATTRIBUTES_2_BIT                        0
#define CPUID_ECX_VALID_SECS_ATTRIBUTES_2_MASK                       0xFFFFFFFF
#define CPUID_ECX_VALID_SECS_ATTRIBUTES_2(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the valid bits of SECS.ATTRIBUTES[127:96] that software can set with ECREATE.
       */
      UINT32 ValidSecsAttributes3                                  : 32;
#define CPUID_EDX_VALID_SECS_ATTRIBUTES_3_BIT                        0
#define CPUID_EDX_VALID_SECS_ATTRIBUTES_3_MASK                       0xFFFFFFFF
#define CPUID_EDX_VALID_SECS_ATTRIBUTES_3(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_01;

/**
 * @brief Intel SGX EPC Enumeration Leaf, sub-leaves (EAX = 12H, ECX = 2 or higher)
 *
 * @note Leaf 12H sub-leaf 2 or higher (ECX >= 2) is supported if CPUID.(EAX=07H, ECX=0H):EBX[SGX] = 1.
 *       This structure describes sub-leaf type 0.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 3:0] Sub-leaf Type 0. Indicates this sub-leaf is invalid.
       */
      UINT32 SubLeafType                                           : 4;
#define CPUID_EAX_SUB_LEAF_TYPE_BIT                                  0
#define CPUID_EAX_SUB_LEAF_TYPE_MASK                                 0x0F
#define CPUID_EAX_SUB_LEAF_TYPE(_)                                   (((_) >> 0) & 0x0F)
      UINT32 Reserved1                                             : 28;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is zero.
       */
      UINT32 Zero                                                  : 32;
#define CPUID_EBX_ZERO_BIT                                           0
#define CPUID_EBX_ZERO_MASK                                          0xFFFFFFFF
#define CPUID_EBX_ZERO(_)                                            (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is zero.
       */
      UINT32 Zero                                                  : 32;
#define CPUID_ECX_ZERO_BIT                                           0
#define CPUID_ECX_ZERO_MASK                                          0xFFFFFFFF
#define CPUID_ECX_ZERO(_)                                            (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is zero.
       */
      UINT32 Zero                                                  : 32;
#define CPUID_EDX_ZERO_BIT                                           0
#define CPUID_EDX_ZERO_MASK                                          0xFFFFFFFF
#define CPUID_EDX_ZERO(_)                                            (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_02P_SLT_0;

/**
 * @brief Intel SGX EPC Enumeration Leaf, sub-leaves (EAX = 12H, ECX = 2 or higher)
 *
 * @note Leaf 12H sub-leaf 2 or higher (ECX >= 2) is supported if CPUID.(EAX=07H, ECX=0H):EBX[SGX] = 1.
 *       This structure describes sub-leaf type 1.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 3:0] Sub-leaf Type 1. This sub-leaf enumerates an EPC section. EBX:EAX and EDX:ECX provide information on the
       * Enclave Page Cache (EPC) section.
       */
      UINT32 SubLeafType                                           : 4;
#define CPUID_EAX_SUB_LEAF_TYPE_BIT                                  0
#define CPUID_EAX_SUB_LEAF_TYPE_MASK                                 0x0F
#define CPUID_EAX_SUB_LEAF_TYPE(_)                                   (((_) >> 0) & 0x0F)
      UINT32 Reserved1                                             : 8;

      /**
       * [Bits 31:12] Bits 31:12 of the physical address of the base of the EPC section.
       */
      UINT32 EpcBasePhysicalAddress1                               : 20;
#define CPUID_EAX_EPC_BASE_PHYSICAL_ADDRESS_1_BIT                    12
#define CPUID_EAX_EPC_BASE_PHYSICAL_ADDRESS_1_MASK                   0xFFFFF
#define CPUID_EAX_EPC_BASE_PHYSICAL_ADDRESS_1(_)                     (((_) >> 12) & 0xFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 19:0] Bits 51:32 of the physical address of the base of the EPC section.
       */
      UINT32 EpcBasePhysicalAddress2                               : 20;
#define CPUID_EBX_EPC_BASE_PHYSICAL_ADDRESS_2_BIT                    0
#define CPUID_EBX_EPC_BASE_PHYSICAL_ADDRESS_2_MASK                   0xFFFFF
#define CPUID_EBX_EPC_BASE_PHYSICAL_ADDRESS_2(_)                     (((_) >> 0) & 0xFFFFF)
      UINT32 Reserved1                                             : 12;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 3:0] EPC section property encoding defined as follows:
       * - If EAX[3:0] 0000b, then all bits of the EDX:ECX pair are enumerated as 0.
       * - If EAX[3:0] 0001b, then this section has confidentiality and integrity protection.
       * All other encodings are reserved.
       */
      UINT32 EpcSectionProperty                                    : 4;
#define CPUID_ECX_EPC_SECTION_PROPERTY_BIT                           0
#define CPUID_ECX_EPC_SECTION_PROPERTY_MASK                          0x0F
#define CPUID_ECX_EPC_SECTION_PROPERTY(_)                            (((_) >> 0) & 0x0F)
      UINT32 Reserved1                                             : 8;

      /**
       * [Bits 31:12] Bits 31:12 of the size of the corresponding EPC section within the Processor Reserved Memory.
       */
      UINT32 EpcSize1                                              : 20;
#define CPUID_ECX_EPC_SIZE_1_BIT                                     12
#define CPUID_ECX_EPC_SIZE_1_MASK                                    0xFFFFF
#define CPUID_ECX_EPC_SIZE_1(_)                                      (((_) >> 12) & 0xFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 19:0] Bits 51:32 of the size of the corresponding EPC section within the Processor Reserved Memory.
       */
      UINT32 EpcSize2                                              : 20;
#define CPUID_EDX_EPC_SIZE_2_BIT                                     0
#define CPUID_EDX_EPC_SIZE_2_MASK                                    0xFFFFF
#define CPUID_EDX_EPC_SIZE_2(_)                                      (((_) >> 0) & 0xFFFFF)
      UINT32 Reserved1                                             : 12;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_02P_SLT_1;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_14 \
 *           EAX = 0x14
 *
 * When CPUID executes with EAX set to 14H and ECX = 0H, the processor returns information about Intel Processor Trace
 * extensions.
 * When CPUID executes with EAX set to 14H and ECX = n (n > 0 and less than the number of non-zero bits in CPUID.(EAX=14H,
 * ECX= 0H).EAX), the processor returns information about packet generation in Intel Processor Trace.
 * @{
 */
/**
 * @brief Intel Processor Trace Enumeration Main Leaf (EAX = 14H, ECX = 0)
 *
 * @note Leaf 14H main leaf (ECX = 0).
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the maximum sub-leaf supported in leaf 14H.
       */
      UINT32 MaxSubLeaf                                            : 32;
#define CPUID_EAX_MAX_SUB_LEAF_BIT                                   0
#define CPUID_EAX_MAX_SUB_LEAF_MASK                                  0xFFFFFFFF
#define CPUID_EAX_MAX_SUB_LEAF(_)                                    (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bit 0] If 1, indicates that IA32_RTIT_CTL.CR3Filter can be set to 1, and that IA32_RTIT_CR3_MATCH MSR can be accessed.
       */
      UINT32 Flag0                                                 : 1;
#define CPUID_EBX_FLAG0_BIT                                          0
#define CPUID_EBX_FLAG0_MASK                                         0x01
#define CPUID_EBX_FLAG0(_)                                           (((_) >> 0) & 0x01)

      /**
       * [Bit 1] If 1, indicates support of Configurable PSB and Cycle-Accurate Mode.
       */
      UINT32 Flag1                                                 : 1;
#define CPUID_EBX_FLAG1_BIT                                          1
#define CPUID_EBX_FLAG1_MASK                                         0x01
#define CPUID_EBX_FLAG1(_)                                           (((_) >> 1) & 0x01)

      /**
       * [Bit 2] If 1, indicates support of IP Filtering, TraceStop filtering, and preservation of Intel PT MSRs across warm
       * reset.
       */
      UINT32 Flag2                                                 : 1;
#define CPUID_EBX_FLAG2_BIT                                          2
#define CPUID_EBX_FLAG2_MASK                                         0x01
#define CPUID_EBX_FLAG2(_)                                           (((_) >> 2) & 0x01)

      /**
       * [Bit 3] If 1, indicates support of MTC timing packet and suppression of COFI-based packets.
       */
      UINT32 Flag3                                                 : 1;
#define CPUID_EBX_FLAG3_BIT                                          3
#define CPUID_EBX_FLAG3_MASK                                         0x01
#define CPUID_EBX_FLAG3(_)                                           (((_) >> 3) & 0x01)

      /**
       * [Bit 4] If 1, indicates support of PTWRITE. Writes can set IA32_RTIT_CTL[12] (PTWEn) and IA32_RTIT_CTL[5] (FUPonPTW),
       * and PTWRITE can generate packets.
       */
      UINT32 Flag4                                                 : 1;
#define CPUID_EBX_FLAG4_BIT                                          4
#define CPUID_EBX_FLAG4_MASK                                         0x01
#define CPUID_EBX_FLAG4(_)                                           (((_) >> 4) & 0x01)

      /**
       * [Bit 5] If 1, indicates support of Power Event Trace. Writes can set IA32_RTIT_CTL[4] (PwrEvtEn), enabling Power Event
       * Trace packet generation.
       */
      UINT32 Flag5                                                 : 1;
#define CPUID_EBX_FLAG5_BIT                                          5
#define CPUID_EBX_FLAG5_MASK                                         0x01
#define CPUID_EBX_FLAG5(_)                                           (((_) >> 5) & 0x01)
      UINT32 Reserved1                                             : 26;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] If 1, Tracing can be enabled with IA32_RTIT_CTL.ToPA = 1, hence utilizing the ToPA output scheme;
       * IA32_RTIT_OUTPUT_BASE and IA32_RTIT_OUTPUT_MASK_PTRS MSRs can be accessed.
       */
      UINT32 Flag0                                                 : 1;
#define CPUID_ECX_FLAG0_BIT                                          0
#define CPUID_ECX_FLAG0_MASK                                         0x01
#define CPUID_ECX_FLAG0(_)                                           (((_) >> 0) & 0x01)

      /**
       * [Bit 1] If 1, ToPA tables can hold any number of output entries, up to the maximum allowed by the MaskOrTableOffset
       * field of IA32_RTIT_OUTPUT_MASK_PTRS.
       */
      UINT32 Flag1                                                 : 1;
#define CPUID_ECX_FLAG1_BIT                                          1
#define CPUID_ECX_FLAG1_MASK                                         0x01
#define CPUID_ECX_FLAG1(_)                                           (((_) >> 1) & 0x01)

      /**
       * [Bit 2] If 1, indicates support of Single-Range Output scheme.
       */
      UINT32 Flag2                                                 : 1;
#define CPUID_ECX_FLAG2_BIT                                          2
#define CPUID_ECX_FLAG2_MASK                                         0x01
#define CPUID_ECX_FLAG2(_)                                           (((_) >> 2) & 0x01)

      /**
       * [Bit 3] If 1, indicates support of output to Trace Transport subsystem.
       */
      UINT32 Flag3                                                 : 1;
#define CPUID_ECX_FLAG3_BIT                                          3
#define CPUID_ECX_FLAG3_MASK                                         0x01
#define CPUID_ECX_FLAG3(_)                                           (((_) >> 3) & 0x01)
      UINT32 Reserved1                                             : 27;

      /**
       * [Bit 31] If 1, generated packets which contain IP payloads have LIP values, which include the CS base component.
       */
      UINT32 Flag31                                                : 1;
#define CPUID_ECX_FLAG31_BIT                                         31
#define CPUID_ECX_FLAG31_MASK                                        0x01
#define CPUID_ECX_FLAG31(_)                                          (((_) >> 31) & 0x01)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_14_ECX_00;

/**
 * @brief Intel Processor Trace Enumeration Sub-leaf (EAX = 14H, ECX = 1)
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 2:0] Number of configurable Address Ranges for filtering.
       */
      UINT32 NumberOfConfigurableAddressRangesForFiltering         : 3;
#define CPUID_EAX_NUMBER_OF_CONFIGURABLE_ADDRESS_RANGES_FOR_FILTERING_BIT 0
#define CPUID_EAX_NUMBER_OF_CONFIGURABLE_ADDRESS_RANGES_FOR_FILTERING_MASK 0x07
#define CPUID_EAX_NUMBER_OF_CONFIGURABLE_ADDRESS_RANGES_FOR_FILTERING(_) (((_) >> 0) & 0x07)
      UINT32 Reserved1                                             : 13;

      /**
       * [Bits 31:16] Bitmap of supported MTC period encodings.
       */
      UINT32 BitmapOfSupportedMtcPeriodEncodings                   : 16;
#define CPUID_EAX_BITMAP_OF_SUPPORTED_MTC_PERIOD_ENCODINGS_BIT       16
#define CPUID_EAX_BITMAP_OF_SUPPORTED_MTC_PERIOD_ENCODINGS_MASK      0xFFFF
#define CPUID_EAX_BITMAP_OF_SUPPORTED_MTC_PERIOD_ENCODINGS(_)        (((_) >> 16) & 0xFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Bitmap of supported Cycle Threshold value encodings.
       */
      UINT32 BitmapOfSupportedCycleThresholdValueEncodings         : 16;
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CYCLE_THRESHOLD_VALUE_ENCODINGS_BIT 0
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CYCLE_THRESHOLD_VALUE_ENCODINGS_MASK 0xFFFF
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CYCLE_THRESHOLD_VALUE_ENCODINGS(_) (((_) >> 0) & 0xFFFF)

      /**
       * [Bits 31:16] Bitmap of supported Configurable PSB frequency encodings.
       */
      UINT32 BitmapOfSupportedConfigurablePsbFrequencyEncodings    : 16;
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CONFIGURABLE_PSB_FREQUENCY_ENCODINGS_BIT 16
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CONFIGURABLE_PSB_FREQUENCY_ENCODINGS_MASK 0xFFFF
#define CPUID_EBX_BITMAP_OF_SUPPORTED_CONFIGURABLE_PSB_FREQUENCY_ENCODINGS(_) (((_) >> 16) & 0xFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_14_ECX_01;

/**
 * @}
 */

/**
 * @brief Stamp Counter and Nominal Core Crystal Clock Information Leaf
 *
 * When CPUID executes with EAX set to 15H and ECX = 0H, the processor returns information about Time Stamp Counter and
 * Core Crystal Clock.
 *
 * @note If EBX[31:0] is 0, the TSC/"core crystal clock" ratio is not enumerated. EBX[31:0]/EAX[31:0] indicates the ratio
 *       of the TSC frequency and the core crystal clock frequency.
 *       If ECX is 0, the nominal core crystal clock frequency is not enumerated. "TSC frequency" = "core crystal clock
 *       frequency" * EBX/EAX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] An unsigned integer which is the denominator of the TSC/"core crystal clock" ratio.
       */
      UINT32 Denominator                                           : 32;
#define CPUID_EAX_DENOMINATOR_BIT                                    0
#define CPUID_EAX_DENOMINATOR_MASK                                   0xFFFFFFFF
#define CPUID_EAX_DENOMINATOR(_)                                     (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] An unsigned integer which is the numerator of the TSC/"core crystal clock" ratio.
       */
      UINT32 Numerator                                             : 32;
#define CPUID_EBX_NUMERATOR_BIT                                      0
#define CPUID_EBX_NUMERATOR_MASK                                     0xFFFFFFFF
#define CPUID_EBX_NUMERATOR(_)                                       (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] An unsigned integer which is the nominal frequency of the core crystal clock in Hz.
       */
      UINT32 NominalFrequency                                      : 32;
#define CPUID_ECX_NOMINAL_FREQUENCY_BIT                              0
#define CPUID_ECX_NOMINAL_FREQUENCY_MASK                             0xFFFFFFFF
#define CPUID_ECX_NOMINAL_FREQUENCY(_)                               (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_15;

/**
 * @brief Processor Frequency Information Leaf
 *
 * When CPUID executes with EAX set to 16H, the processor returns information about Processor Frequency Information.
 *
 * @note Data is returned from this interface in accordance with the processor's specification and does not reflect actual
 *       values. Suitable use of this data includes the display of processor information in like manner to the processor brand
 *       string and for determining the appropriate range to use when displaying processor information e.g. frequency history
 *       graphs. The returned information should not be used for any other purpose as the returned information does not
 *       accurately correlate to information / counters returned by other processor interfaces.
 *       While a processor may support the Processor Frequency Information leaf, fields that return a value of zero are not
 *       supported.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 15:0] Processor Base Frequency (in MHz).
       */
      UINT32 ProcesorBaseFrequencyMhz                              : 16;
#define CPUID_EAX_PROCESOR_BASE_FREQUENCY_MHZ_BIT                    0
#define CPUID_EAX_PROCESOR_BASE_FREQUENCY_MHZ_MASK                   0xFFFF
#define CPUID_EAX_PROCESOR_BASE_FREQUENCY_MHZ(_)                     (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Maximum Frequency (in MHz).
       */
      UINT32 ProcessorMaximumFrequencyMhz                          : 16;
#define CPUID_EBX_PROCESSOR_MAXIMUM_FREQUENCY_MHZ_BIT                0
#define CPUID_EBX_PROCESSOR_MAXIMUM_FREQUENCY_MHZ_MASK               0xFFFF
#define CPUID_EBX_PROCESSOR_MAXIMUM_FREQUENCY_MHZ(_)                 (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] Bus (Reference) Frequency (in MHz).
       */
      UINT32 BusFrequencyMhz                                       : 16;
#define CPUID_ECX_BUS_FREQUENCY_MHZ_BIT                              0
#define CPUID_ECX_BUS_FREQUENCY_MHZ_MASK                             0xFFFF
#define CPUID_ECX_BUS_FREQUENCY_MHZ(_)                               (((_) >> 0) & 0xFFFF)
      UINT32 Reserved1                                             : 16;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_16;

/**
 * @defgroup CPUID_EAX_17 \
 *           EAX = 0x17
 *
 * When CPUID executes with EAX set to 17H, the processor returns information about the System-On-Chip Vendor Attribute
 * Enumeration.
 * @{
 */
/**
 * @brief System-On-Chip Vendor Attribute Enumeration Main Leaf (EAX = 17H, ECX = 0)
 *
 * @note Leaf 17H main leaf (ECX = 0). Leaf 17H output depends on the initial value in ECX. Leaf 17H sub-leaves 1 through 3
 *       reports SOC Vendor Brand String. Leaf 17H is valid if MaxSOCID_Index >= 3. Leaf 17H sub-leaves 4 and above are reserved.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the maximum input value of supported sub-leaf in leaf 17H.
       */
      UINT32 MaxSocIdIndex                                         : 32;
#define CPUID_EAX_MAX_SOC_ID_INDEX_BIT                               0
#define CPUID_EAX_MAX_SOC_ID_INDEX_MASK                              0xFFFFFFFF
#define CPUID_EAX_MAX_SOC_ID_INDEX(_)                                (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 15:0] SOC Vendor ID.
       */
      UINT32 SocVendorId                                           : 16;
#define CPUID_EBX_SOC_VENDOR_ID_BIT                                  0
#define CPUID_EBX_SOC_VENDOR_ID_MASK                                 0xFFFF
#define CPUID_EBX_SOC_VENDOR_ID(_)                                   (((_) >> 0) & 0xFFFF)

      /**
       * [Bit 16] If 1, the SOC Vendor ID field is assigned via an industry standard enumeration scheme. Otherwise, the SOC
       * Vendor ID field is assigned by Intel.
       */
      UINT32 IsVendorScheme                                        : 1;
#define CPUID_EBX_IS_VENDOR_SCHEME_BIT                               16
#define CPUID_EBX_IS_VENDOR_SCHEME_MASK                              0x01
#define CPUID_EBX_IS_VENDOR_SCHEME(_)                                (((_) >> 16) & 0x01)
      UINT32 Reserved1                                             : 15;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] A unique number an SOC vendor assigns to its SOC projects.
       */
      UINT32 ProjectId                                             : 32;
#define CPUID_ECX_PROJECT_ID_BIT                                     0
#define CPUID_ECX_PROJECT_ID_MASK                                    0xFFFFFFFF
#define CPUID_ECX_PROJECT_ID(_)                                      (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] A unique number within an SOC project that an SOC vendor assigns.
       */
      UINT32 SteppingId                                            : 32;
#define CPUID_EDX_STEPPING_ID_BIT                                    0
#define CPUID_EDX_STEPPING_ID_MASK                                   0xFFFFFFFF
#define CPUID_EDX_STEPPING_ID(_)                                     (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_00;

/**
 * @brief System-On-Chip Vendor Attribute Enumeration Sub-leaf (EAX = 17H, ECX = 1..3)
 *
 * @note Leaf 17H output depends on the initial value in ECX. SOC Vendor Brand String is a UTF-8 encoded string padded with
 *       trailing bytes of 00H. The complete SOC Vendor Brand String is constructed by concatenating in ascending order of
 *       EAX:EBX:ECX:EDX and from the sub-leaf 1 fragment towards sub-leaf 3.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] SOC Vendor Brand String. UTF-8 encoded string.
       */
      UINT32 SocVendorBrandString                                  : 32;
#define CPUID_EAX_SOC_VENDOR_BRAND_STRING_BIT                        0
#define CPUID_EAX_SOC_VENDOR_BRAND_STRING_MASK                       0xFFFFFFFF
#define CPUID_EAX_SOC_VENDOR_BRAND_STRING(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] SOC Vendor Brand String. UTF-8 encoded string.
       */
      UINT32 SocVendorBrandString                                  : 32;
#define CPUID_EBX_SOC_VENDOR_BRAND_STRING_BIT                        0
#define CPUID_EBX_SOC_VENDOR_BRAND_STRING_MASK                       0xFFFFFFFF
#define CPUID_EBX_SOC_VENDOR_BRAND_STRING(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] SOC Vendor Brand String. UTF-8 encoded string.
       */
      UINT32 SocVendorBrandString                                  : 32;
#define CPUID_ECX_SOC_VENDOR_BRAND_STRING_BIT                        0
#define CPUID_ECX_SOC_VENDOR_BRAND_STRING_MASK                       0xFFFFFFFF
#define CPUID_ECX_SOC_VENDOR_BRAND_STRING(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] SOC Vendor Brand String. UTF-8 encoded string.
       */
      UINT32 SocVendorBrandString                                  : 32;
#define CPUID_EDX_SOC_VENDOR_BRAND_STRING_BIT                        0
#define CPUID_EDX_SOC_VENDOR_BRAND_STRING_MASK                       0xFFFFFFFF
#define CPUID_EDX_SOC_VENDOR_BRAND_STRING(_)                         (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_01_03;

/**
 * @brief System-On-Chip Vendor Attribute Enumeration Sub-leaves (EAX = 17H, ECX > MaxSOCID_Index)
 *
 * @note Leaf 17H output depends on the initial value in ECX.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reserved = 0.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reserved = 0.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reserved = 0.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reserved = 0.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_N;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_18 \
 *           EAX = 0x18
 *
 * When CPUID executes with EAX set to 18H, the processor returns information about the Deterministic Address Translation
 * Parameters.
 * @{
 */
/**
 * @brief Deterministic Address Translation Parameters Main Leaf (EAX = 18H, ECX = 0)
 *
 * @note Each sub-leaf enumerates a different address translation structure.
 *       If ECX contains an invalid sub-leaf index, EAX/EBX/ECX/EDX return 0. Sub-leaf index n is invalid if n exceeds the value
 *       that sub-leaf 0 returns in EAX. A sub-leaf index is also invalid if EDX[4:0] returns 0. Valid sub-leaves do not need to
 *       be contiguous or in any particular order. A valid sub-leaf may be in a higher input ECX value than an invalid sub-leaf
 *       or than a valid sub-leaf of a higher or lower-level structure.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Reports the maximum input value of supported sub-leaf in leaf 18H.
       */
      UINT32 MaxSubLeaf                                            : 32;
#define CPUID_EAX_MAX_SUB_LEAF_BIT                                   0
#define CPUID_EAX_MAX_SUB_LEAF_MASK                                  0xFFFFFFFF
#define CPUID_EAX_MAX_SUB_LEAF(_)                                    (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bit 0] 4K page size entries supported by this structure.
       */
      UINT32 PageEntries4KbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED_BIT                     0
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED(_)                      (((_) >> 0) & 0x01)

      /**
       * [Bit 1] 2MB page size entries supported by this structure.
       */
      UINT32 PageEntries2MbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED_BIT                     1
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED(_)                      (((_) >> 1) & 0x01)

      /**
       * [Bit 2] 4MB page size entries supported by this structure.
       */
      UINT32 PageEntries4MbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED_BIT                     2
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED(_)                      (((_) >> 2) & 0x01)

      /**
       * [Bit 3] 1 GB page size entries supported by this structure.
       */
      UINT32 PageEntries1GbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED_BIT                     3
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED(_)                      (((_) >> 3) & 0x01)
      UINT32 Reserved1                                             : 4;

      /**
       * [Bits 10:8] Partitioning (0: Soft partitioning between the logical processors sharing this structure).
       */
      UINT32 Partitioning                                          : 3;
#define CPUID_EBX_PARTITIONING_BIT                                   8
#define CPUID_EBX_PARTITIONING_MASK                                  0x07
#define CPUID_EBX_PARTITIONING(_)                                    (((_) >> 8) & 0x07)
      UINT32 Reserved2                                             : 5;

      /**
       * [Bits 31:16] W = Ways of associativity.
       */
      UINT32 WaysOfAssociativity00                                 : 16;
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_00_BIT                       16
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_00_MASK                      0xFFFF
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_00(_)                        (((_) >> 16) & 0xFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Number of Sets.
       */
      UINT32 NumberOfSets                                          : 32;
#define CPUID_ECX_NUMBER_OF_SETS_BIT                                 0
#define CPUID_ECX_NUMBER_OF_SETS_MASK                                0xFFFFFFFF
#define CPUID_ECX_NUMBER_OF_SETS(_)                                  (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 4:0] Translation cache type field.
       * - 00000b: Null (indicates this sub-leaf is not valid).
       * - 00001b: Data TLB.
       * - 00010b: Instruction TLB.
       * - 00011b: Unified TLB.
       * All other encodings are reserved.
       *
       * @note Some unified TLBs will allow a single TLB entry to satisfy data read/write and instruction fetches. Others will
       *       require separate entries (e.g., one loaded on data read/write and another loaded on an instruction fetch) . Please see
       *       the Intel(R) 64 and IA-32 Architectures Optimization Reference Manual for details of a particular product.
       */
      UINT32 TranslationCacheTypeField                             : 5;
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD_BIT                   0
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD_MASK                  0x1F
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD(_)                    (((_) >> 0) & 0x1F)

      /**
       * [Bits 7:5] Translation cache level (starts at 1).
       */
      UINT32 TranslationCacheLevel                                 : 3;
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL_BIT                        5
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL_MASK                       0x07
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL(_)                         (((_) >> 5) & 0x07)

      /**
       * [Bit 8] Fully associative structure.
       */
      UINT32 FullyAssociativeStructure                             : 1;
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE_BIT                    8
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE_MASK                   0x01
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE(_)                     (((_) >> 8) & 0x01)
      UINT32 Reserved1                                             : 5;

      /**
       * [Bits 25:14] Maximum number of addressable IDs for logical processors sharing this translation cache.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 MaxAddressableIdsForLogicalProcessors                 : 12;
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_BIT     14
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_MASK    0xFFF
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS(_)      (((_) >> 14) & 0xFFF)
      UINT32 Reserved2                                             : 6;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_18_ECX_00;

/**
 * @brief Deterministic Address Translation Parameters Sub-leaf (EAX = 18H, ECX >= 1)
 *
 * @note Each sub-leaf enumerates a different address translation structure.
 *       If ECX contains an invalid sub-leaf index, EAX/EBX/ECX/EDX return 0. Sub-leaf index n is invalid if n exceeds the value
 *       that sub-leaf 0 returns in EAX. A sub-leaf index is also invalid if EDX[4:0] returns 0. Valid sub-leaves do not need to
 *       be contiguous or in any particular order. A valid sub-leaf may be in a higher input ECX value than an invalid sub-leaf
 *       or than a valid sub-leaf of a higher or lower-level structure.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bit 0] 4K page size entries supported by this structure.
       */
      UINT32 PageEntries4KbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED_BIT                     0
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_4KB_SUPPORTED(_)                      (((_) >> 0) & 0x01)

      /**
       * [Bit 1] 2MB page size entries supported by this structure.
       */
      UINT32 PageEntries2MbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED_BIT                     1
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_2MB_SUPPORTED(_)                      (((_) >> 1) & 0x01)

      /**
       * [Bit 2] 4MB page size entries supported by this structure.
       */
      UINT32 PageEntries4MbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED_BIT                     2
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_4MB_SUPPORTED(_)                      (((_) >> 2) & 0x01)

      /**
       * [Bit 3] 1 GB page size entries supported by this structure.
       */
      UINT32 PageEntries1GbSupported                               : 1;
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED_BIT                     3
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED_MASK                    0x01
#define CPUID_EBX_PAGE_ENTRIES_1GB_SUPPORTED(_)                      (((_) >> 3) & 0x01)
      UINT32 Reserved1                                             : 4;

      /**
       * [Bits 10:8] Partitioning (0: Soft partitioning between the logical processors sharing this structure).
       */
      UINT32 Partitioning                                          : 3;
#define CPUID_EBX_PARTITIONING_BIT                                   8
#define CPUID_EBX_PARTITIONING_MASK                                  0x07
#define CPUID_EBX_PARTITIONING(_)                                    (((_) >> 8) & 0x07)
      UINT32 Reserved2                                             : 5;

      /**
       * [Bits 31:16] W = Ways of associativity.
       */
      UINT32 WaysOfAssociativity01                                 : 16;
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_01_BIT                       16
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_01_MASK                      0xFFFF
#define CPUID_EBX_WAYS_OF_ASSOCIATIVITY_01(_)                        (((_) >> 16) & 0xFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Number of Sets.
       */
      UINT32 NumberOfSets                                          : 32;
#define CPUID_ECX_NUMBER_OF_SETS_BIT                                 0
#define CPUID_ECX_NUMBER_OF_SETS_MASK                                0xFFFFFFFF
#define CPUID_ECX_NUMBER_OF_SETS(_)                                  (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 4:0] Translation cache type field.
       * - 00000b: Null (indicates this sub-leaf is not valid).
       * - 00001b: Data TLB.
       * - 00010b: Instruction TLB.
       * - 00011b: Unified TLB.
       * All other encodings are reserved.
       *
       * @note Some unified TLBs will allow a single TLB entry to satisfy data read/write and instruction fetches. Others will
       *       require separate entries (e.g., one loaded on data read/write and another loaded on an instruction fetch) . Please see
       *       the Intel(R) 64 and IA-32 Architectures Optimization Reference Manual for details of a particular product.
       */
      UINT32 TranslationCacheTypeField                             : 5;
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD_BIT                   0
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD_MASK                  0x1F
#define CPUID_EDX_TRANSLATION_CACHE_TYPE_FIELD(_)                    (((_) >> 0) & 0x1F)

      /**
       * [Bits 7:5] Translation cache level (starts at 1).
       */
      UINT32 TranslationCacheLevel                                 : 3;
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL_BIT                        5
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL_MASK                       0x07
#define CPUID_EDX_TRANSLATION_CACHE_LEVEL(_)                         (((_) >> 5) & 0x07)

      /**
       * [Bit 8] Fully associative structure.
       */
      UINT32 FullyAssociativeStructure                             : 1;
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE_BIT                    8
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE_MASK                   0x01
#define CPUID_EDX_FULLY_ASSOCIATIVE_STRUCTURE(_)                     (((_) >> 8) & 0x01)
      UINT32 Reserved1                                             : 5;

      /**
       * [Bits 25:14] Maximum number of addressable IDs for logical processors sharing this translation cache.
       *
       * @note Add one to the return value to get the result.
       */
      UINT32 MaxAddressableIdsForLogicalProcessors                 : 12;
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_BIT     14
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS_MASK    0xFFF
#define CPUID_EDX_MAX_ADDRESSABLE_IDS_FOR_LOGICAL_PROCESSORS(_)      (((_) >> 14) & 0xFFF)
      UINT32 Reserved2                                             : 6;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_18_ECX_01P;

/**
 * @}
 */

/**
 * @brief Extended Function CPUID Information
 *
 * When CPUID executes with EAX set to 80000000H, the processor returns the highest value the processor recognizes for
 * returning extended processor information. The value is returned in the EAX register and is processor specific.
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Maximum Input Value for Extended Function CPUID Information.
       */
      UINT32 MaxExtendedFunctions                                  : 32;
#define CPUID_EAX_MAX_EXTENDED_FUNCTIONS_BIT                         0
#define CPUID_EAX_MAX_EXTENDED_FUNCTIONS_MASK                        0xFFFFFFFF
#define CPUID_EAX_MAX_EXTENDED_FUNCTIONS(_)                          (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000000;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bit 0] LAHF/SAHF available in 64-bit mode.
       */
      UINT32 LahfSahfAvailableIn64BitMode                          : 1;
#define CPUID_ECX_LAHF_SAHF_AVAILABLE_IN_64_BIT_MODE_BIT             0
#define CPUID_ECX_LAHF_SAHF_AVAILABLE_IN_64_BIT_MODE_MASK            0x01
#define CPUID_ECX_LAHF_SAHF_AVAILABLE_IN_64_BIT_MODE(_)              (((_) >> 0) & 0x01)
      UINT32 Reserved1                                             : 4;

      /**
       * [Bit 5] LZCNT.
       */
      UINT32 Lzcnt                                                 : 1;
#define CPUID_ECX_LZCNT_BIT                                          5
#define CPUID_ECX_LZCNT_MASK                                         0x01
#define CPUID_ECX_LZCNT(_)                                           (((_) >> 5) & 0x01)
      UINT32 Reserved2                                             : 2;

      /**
       * [Bit 8] PREFETCHW.
       */
      UINT32 Prefetchw                                             : 1;
#define CPUID_ECX_PREFETCHW_BIT                                      8
#define CPUID_ECX_PREFETCHW_MASK                                     0x01
#define CPUID_ECX_PREFETCHW(_)                                       (((_) >> 8) & 0x01)
      UINT32 Reserved3                                             : 23;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 11;

      /**
       * [Bit 11] SYSCALL/SYSRET available in 64-bit mode.
       */
      UINT32 SyscallSysretAvailableIn64BitMode                     : 1;
#define CPUID_EDX_SYSCALL_SYSRET_AVAILABLE_IN_64_BIT_MODE_BIT        11
#define CPUID_EDX_SYSCALL_SYSRET_AVAILABLE_IN_64_BIT_MODE_MASK       0x01
#define CPUID_EDX_SYSCALL_SYSRET_AVAILABLE_IN_64_BIT_MODE(_)         (((_) >> 11) & 0x01)
      UINT32 Reserved2                                             : 8;

      /**
       * [Bit 20] Execute Disable Bit available.
       */
      UINT32 ExecuteDisableBitAvailable                            : 1;
#define CPUID_EDX_EXECUTE_DISABLE_BIT_AVAILABLE_BIT                  20
#define CPUID_EDX_EXECUTE_DISABLE_BIT_AVAILABLE_MASK                 0x01
#define CPUID_EDX_EXECUTE_DISABLE_BIT_AVAILABLE(_)                   (((_) >> 20) & 0x01)
      UINT32 Reserved3                                             : 5;

      /**
       * [Bit 26] 1-GByte pages are available if 1.
       */
      UINT32 Pages1GbAvailable                                     : 1;
#define CPUID_EDX_PAGES_1GB_AVAILABLE_BIT                            26
#define CPUID_EDX_PAGES_1GB_AVAILABLE_MASK                           0x01
#define CPUID_EDX_PAGES_1GB_AVAILABLE(_)                             (((_) >> 26) & 0x01)

      /**
       * [Bit 27] RDTSCP and IA32_TSC_AUX are available if 1.
       */
      UINT32 RdtscpAvailable                                       : 1;
#define CPUID_EDX_RDTSCP_AVAILABLE_BIT                               27
#define CPUID_EDX_RDTSCP_AVAILABLE_MASK                              0x01
#define CPUID_EDX_RDTSCP_AVAILABLE(_)                                (((_) >> 27) & 0x01)
      UINT32 Reserved4                                             : 1;

      /**
       * [Bit 29] Intel(R) 64 Architecture available if 1.
       */
      UINT32 Ia64Available                                         : 1;
#define CPUID_EDX_IA64_AVAILABLE_BIT                                 29
#define CPUID_EDX_IA64_AVAILABLE_MASK                                0x01
#define CPUID_EDX_IA64_AVAILABLE(_)                                  (((_) >> 29) & 0x01)
      UINT32 Reserved5                                             : 2;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000001;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String.
       */
      UINT32 ProcessorBrandString1                                 : 32;
#define CPUID_EAX_PROCESSOR_BRAND_STRING_1_BIT                       0
#define CPUID_EAX_PROCESSOR_BRAND_STRING_1_MASK                      0xFFFFFFFF
#define CPUID_EAX_PROCESSOR_BRAND_STRING_1(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString2                                 : 32;
#define CPUID_EBX_PROCESSOR_BRAND_STRING_2_BIT                       0
#define CPUID_EBX_PROCESSOR_BRAND_STRING_2_MASK                      0xFFFFFFFF
#define CPUID_EBX_PROCESSOR_BRAND_STRING_2(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString3                                 : 32;
#define CPUID_ECX_PROCESSOR_BRAND_STRING_3_BIT                       0
#define CPUID_ECX_PROCESSOR_BRAND_STRING_3_MASK                      0xFFFFFFFF
#define CPUID_ECX_PROCESSOR_BRAND_STRING_3(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString4                                 : 32;
#define CPUID_EDX_PROCESSOR_BRAND_STRING_4_BIT                       0
#define CPUID_EDX_PROCESSOR_BRAND_STRING_4_MASK                      0xFFFFFFFF
#define CPUID_EDX_PROCESSOR_BRAND_STRING_4(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000002;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString5                                 : 32;
#define CPUID_EAX_PROCESSOR_BRAND_STRING_5_BIT                       0
#define CPUID_EAX_PROCESSOR_BRAND_STRING_5_MASK                      0xFFFFFFFF
#define CPUID_EAX_PROCESSOR_BRAND_STRING_5(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString6                                 : 32;
#define CPUID_EBX_PROCESSOR_BRAND_STRING_6_BIT                       0
#define CPUID_EBX_PROCESSOR_BRAND_STRING_6_MASK                      0xFFFFFFFF
#define CPUID_EBX_PROCESSOR_BRAND_STRING_6(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString7                                 : 32;
#define CPUID_ECX_PROCESSOR_BRAND_STRING_7_BIT                       0
#define CPUID_ECX_PROCESSOR_BRAND_STRING_7_MASK                      0xFFFFFFFF
#define CPUID_ECX_PROCESSOR_BRAND_STRING_7(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString8                                 : 32;
#define CPUID_EDX_PROCESSOR_BRAND_STRING_8_BIT                       0
#define CPUID_EDX_PROCESSOR_BRAND_STRING_8_MASK                      0xFFFFFFFF
#define CPUID_EDX_PROCESSOR_BRAND_STRING_8(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000003;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString9                                 : 32;
#define CPUID_EAX_PROCESSOR_BRAND_STRING_9_BIT                       0
#define CPUID_EAX_PROCESSOR_BRAND_STRING_9_MASK                      0xFFFFFFFF
#define CPUID_EAX_PROCESSOR_BRAND_STRING_9(_)                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString10                                : 32;
#define CPUID_EBX_PROCESSOR_BRAND_STRING_10_BIT                      0
#define CPUID_EBX_PROCESSOR_BRAND_STRING_10_MASK                     0xFFFFFFFF
#define CPUID_EBX_PROCESSOR_BRAND_STRING_10(_)                       (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString11                                : 32;
#define CPUID_ECX_PROCESSOR_BRAND_STRING_11_BIT                      0
#define CPUID_ECX_PROCESSOR_BRAND_STRING_11_MASK                     0xFFFFFFFF
#define CPUID_ECX_PROCESSOR_BRAND_STRING_11(_)                       (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] Processor Brand String Continued.
       */
      UINT32 ProcessorBrandString12                                : 32;
#define CPUID_EDX_PROCESSOR_BRAND_STRING_12_BIT                      0
#define CPUID_EDX_PROCESSOR_BRAND_STRING_12_MASK                     0xFFFFFFFF
#define CPUID_EDX_PROCESSOR_BRAND_STRING_12(_)                       (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000004;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000005;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 7:0] Cache Line size in bytes.
       */
      UINT32 CacheLineSizeInBytes                                  : 8;
#define CPUID_ECX_CACHE_LINE_SIZE_IN_BYTES_BIT                       0
#define CPUID_ECX_CACHE_LINE_SIZE_IN_BYTES_MASK                      0xFF
#define CPUID_ECX_CACHE_LINE_SIZE_IN_BYTES(_)                        (((_) >> 0) & 0xFF)
      UINT32 Reserved1                                             : 4;

      /**
       * [Bits 15:12] L2 Associativity field.
       * L2 associativity field encodings:
       * - 00H - Disabled.
       * - 01H - Direct mapped.
       * - 02H - 2-way.
       * - 04H - 4-way.
       * - 06H - 8-way.
       * - 08H - 16-way.
       * - 0FH - Fully associative.
       */
      UINT32 L2AssociativityField                                  : 4;
#define CPUID_ECX_L2_ASSOCIATIVITY_FIELD_BIT                         12
#define CPUID_ECX_L2_ASSOCIATIVITY_FIELD_MASK                        0x0F
#define CPUID_ECX_L2_ASSOCIATIVITY_FIELD(_)                          (((_) >> 12) & 0x0F)

      /**
       * [Bits 31:16] Cache size in 1K units.
       */
      UINT32 CacheSizeIn1KUnits                                    : 16;
#define CPUID_ECX_CACHE_SIZE_IN_1K_UNITS_BIT                         16
#define CPUID_ECX_CACHE_SIZE_IN_1K_UNITS_MASK                        0xFFFF
#define CPUID_ECX_CACHE_SIZE_IN_1K_UNITS(_)                          (((_) >> 16) & 0xFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EDX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EDX_RESERVED_BIT                                       0
#define CPUID_EDX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EDX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000006;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      /**
       * [Bits 31:0] EAX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EAX_RESERVED_BIT                                       0
#define CPUID_EAX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EAX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] EBX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_EBX_RESERVED_BIT                                       0
#define CPUID_EBX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_EBX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      /**
       * [Bits 31:0] ECX is reserved.
       */
      UINT32 Reserved                                              : 32;
#define CPUID_ECX_RESERVED_BIT                                       0
#define CPUID_ECX_RESERVED_MASK                                      0xFFFFFFFF
#define CPUID_ECX_RESERVED(_)                                        (((_) >> 0) & 0xFFFFFFFF)
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 8;

      /**
       * [Bit 8] Invariant TSC available if 1.
       */
      UINT32 InvariantTscAvailable                                 : 1;
#define CPUID_EDX_INVARIANT_TSC_AVAILABLE_BIT                        8
#define CPUID_EDX_INVARIANT_TSC_AVAILABLE_MASK                       0x01
#define CPUID_EDX_INVARIANT_TSC_AVAILABLE(_)                         (((_) >> 8) & 0x01)
      UINT32 Reserved2                                             : 23;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000007;

/**
 * @}
 */

/**
 * @defgroup MODEL_SPECIFIC_REGISTERS \
 *           Model Specific Registers
 *
 * @see Vol2A[3.2(CPUID)] (reference)
 * @{
 */
/**
 * @defgroup IA32_P5_MC \
 *           IA32_P5_MC_(x)
 *
 * When machine-check exceptions are enabled for the Pentium processor (MCE flag is set in control register CR4), the
 * machine-check exception handler uses the RDMSR instruction to read the error type from the P5_MC_TYPE register and the
 * machine check address from the P5_MC_ADDR register. The handler then normally reports these register values to the
 * system console before aborting execution.
 *
 * @see Vol3B[15.10.2(Pentium Processor Machine-Check Exception Handling)] (reference)
 * @{
 */
/**
 * Machine-check exception address.
 *
 * @remarks 05_01H
 * @see Vol4[2.22(MSRS IN PENTIUM PROCESSORS)]
 */
#define IA32_P5_MC_ADDR                                              0x00000000

/**
 * Machine-check exception type.
 *
 * @remarks 05_01H
 * @see Vol4[2.22(MSRS IN PENTIUM PROCESSORS)]
 */
#define IA32_P5_MC_TYPE                                              0x00000001

/**
 * @}
 */

/**
 * System coherence line size.
 *
 * @remarks 0F_03H
 * @see Vol3A[8.10.5(Monitor/Mwait Address Range Determination)]
 * @see Vol3A[8.10.5(Monitor/Mwait Address Range Determination)] (reference)
 */
#define IA32_MONITOR_FILTER_LINE_SIZE                                0x00000006

/**
 * Value as returned by instruction RDTSC.
 *
 * @remarks 05_01H
 * @see Vol3B[17.17(TIME-STAMP COUNTER)]
 */
#define IA32_TIME_STAMP_COUNTER                                      0x00000010

/**
 * The operating system can use this MSR to determine "slot" information for the processor and the proper microcode update
 * to load.
 *
 * @remarks 06_01H
 */
#define IA32_PLATFORM_ID                                             0x00000017

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 50;

    /**
     * @brief Platform Id <b>(RO)</b>
     *
     * [Bits 52:50] Contains information concerning the intended platform for the processor.
     * 
     * 
     * 52 | 51 | 50 | _
     * --:|:--:|:---|-----------------
     * 0  | 0  | 0  | Processor Flag 0
     * 0  | 0  | 1  | Processor Flag 1
     * 0  | 1  | 0  | Processor Flag 2
     * 0  | 1  | 1  | Processor Flag 3
     * 1  | 0  | 0  | Processor Flag 4
     * 1  | 0  | 1  | Processor Flag 5
     * 1  | 1  | 0  | Processor Flag 6
     * 1  | 1  | 1  | Processor Flag 7
     */
    UINT64 PlatformId                                              : 3;
#define IA32_PLATFORM_ID_REGISTER_PLATFORM_ID_BIT                    50
#define IA32_PLATFORM_ID_REGISTER_PLATFORM_ID_MASK                   0x07
#define IA32_PLATFORM_ID_REGISTER_PLATFORM_ID(_)                     (((_) >> 50) & 0x07)
    UINT64 Reserved2                                               : 11;
  };

  UINT64 Flags;
} IA32_PLATFORM_ID_REGISTER;

/**
 * This register holds the APIC base address, permitting the relocation of the APIC memory map.
 *
 * @remarks 06_01H
 * @see Vol3A[10.4.4(Local APIC Status and Location)]
 * @see Vol3A[10.4.5(Relocating the Local APIC Registers)]
 */
#define IA32_APIC_BASE                                               0x0000001B

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 8;

    /**
     * [Bit 8] BSP flag.
     */
    UINT64 BspFlag                                                 : 1;
#define IA32_APIC_BASE_REGISTER_BSP_FLAG_BIT                         8
#define IA32_APIC_BASE_REGISTER_BSP_FLAG_MASK                        0x01
#define IA32_APIC_BASE_REGISTER_BSP_FLAG(_)                          (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 10] Enable x2APIC mode.
     */
    UINT64 EnableX2ApicMode                                        : 1;
#define IA32_APIC_BASE_REGISTER_ENABLE_X2APIC_MODE_BIT               10
#define IA32_APIC_BASE_REGISTER_ENABLE_X2APIC_MODE_MASK              0x01
#define IA32_APIC_BASE_REGISTER_ENABLE_X2APIC_MODE(_)                (((_) >> 10) & 0x01)

    /**
     * [Bit 11] APIC Global Enable.
     */
    UINT64 ApicGlobalEnable                                        : 1;
#define IA32_APIC_BASE_REGISTER_APIC_GLOBAL_ENABLE_BIT               11
#define IA32_APIC_BASE_REGISTER_APIC_GLOBAL_ENABLE_MASK              0x01
#define IA32_APIC_BASE_REGISTER_APIC_GLOBAL_ENABLE(_)                (((_) >> 11) & 0x01)

    /**
     * [Bits 47:12] APIC Base.
     */
    UINT64 ApicBase                                                : 36;
#define IA32_APIC_BASE_REGISTER_APIC_BASE_BIT                        12
#define IA32_APIC_BASE_REGISTER_APIC_BASE_MASK                       0xFFFFFFFFF
#define IA32_APIC_BASE_REGISTER_APIC_BASE(_)                         (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved3                                               : 16;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_APIC_BASE_REGISTER;

/**
 * Control Features in Intel 64 Processor.
 *
 * @remarks If any one enumeration condition for defined bit field holds.
 */
#define IA32_FEATURE_CONTROL                                         0x0000003A

typedef union
{
  struct
  {
    /**
     * @brief Lock bit <b>(R/WO)</b>
     *
     * [Bit 0] When set, locks this MSR from being written; writes to this bit will result in GP(0).
     *
     * @note Once the Lock bit is set, the contents of this register cannot be modified. Therefore the lock bit must be set
     *       after configuring support for Intel Virtualization Technology and prior to transferring control to an option ROM or the
     *       OS. Hence, once the Lock bit is set, the entire IA32_FEATURE_CONTROL contents are preserved across RESET when PWRGOOD is
     *       not deasserted.
     * @remarks If any one enumeration condition for defined bit field position greater than bit 0 holds.
     */
    UINT64 LockBit                                                 : 1;
#define IA32_FEATURE_CONTROL_REGISTER_LOCK_BIT_BIT                   0
#define IA32_FEATURE_CONTROL_REGISTER_LOCK_BIT_MASK                  0x01
#define IA32_FEATURE_CONTROL_REGISTER_LOCK_BIT(_)                    (((_) >> 0) & 0x01)

    /**
     * @brief Enable VMX inside SMX operation <b>(R/WL)</b>
     *
     * [Bit 1] This bit enables a system executive to use VMX in conjunction with SMX to support Intel(R) Trusted Execution
     * Technology. BIOS must set this bit only when the CPUID function 1 returns VMX feature flag and SMX feature flag set (ECX
     * bits 5 and 6 respectively).
     *
     * @remarks If CPUID.01H:ECX[5] = 1 && CPUID.01H:ECX[6] = 1
     */
    UINT64 EnableVmxInsideSmx                                      : 1;
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_INSIDE_SMX_BIT      1
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_INSIDE_SMX_MASK     0x01
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_INSIDE_SMX(_)       (((_) >> 1) & 0x01)

    /**
     * @brief Enable VMX outside SMX operation <b>(R/WL)</b>
     *
     * [Bit 2] This bit enables VMX for a system executive that does not require SMX. BIOS must set this bit only when the
     * CPUID function 1 returns the VMX feature flag set (ECX bit 5).
     *
     * @remarks If CPUID.01H:ECX[5] = 1
     */
    UINT64 EnableVmxOutsideSmx                                     : 1;
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_OUTSIDE_SMX_BIT     2
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_OUTSIDE_SMX_MASK    0x01
#define IA32_FEATURE_CONTROL_REGISTER_ENABLE_VMX_OUTSIDE_SMX(_)      (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * @brief SENTER Local Function Enable <b>(R/WL)</b>
     *
     * [Bits 14:8] When set, each bit in the field represents an enable control for a corresponding SENTER function. This field
     * is supported only if CPUID.1:ECX.[bit 6] is set.
     *
     * @remarks If CPUID.01H:ECX[6] = 1
     */
    UINT64 SenterLocalFunctionEnables                              : 7;
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_LOCAL_FUNCTION_ENABLES_BIT 8
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_LOCAL_FUNCTION_ENABLES_MASK 0x7F
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_LOCAL_FUNCTION_ENABLES(_) (((_) >> 8) & 0x7F)

    /**
     * @brief SENTER Global Enable <b>(R/WL)</b>
     *
     * [Bit 15] This bit must be set to enable SENTER leaf functions. This bit is supported only if CPUID.1:ECX.[bit 6] is set.
     *
     * @remarks If CPUID.01H:ECX[6] = 1
     */
    UINT64 SenterGlobalEnable                                      : 1;
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_GLOBAL_ENABLE_BIT       15
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_GLOBAL_ENABLE_MASK      0x01
#define IA32_FEATURE_CONTROL_REGISTER_SENTER_GLOBAL_ENABLE(_)        (((_) >> 15) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief SGX Launch Control Enable <b>(R/WL)</b>
     *
     * [Bit 17] This bit must be set to enable runtime reconfiguration of SGX Launch Control via the IA32_SGXLEPUBKEYHASHn MSR.
     *
     * @remarks If CPUID.(EAX=07H, ECX=0H): ECX[30] = 1
     */
    UINT64 SgxLaunchControlEnable                                  : 1;
#define IA32_FEATURE_CONTROL_REGISTER_SGX_LAUNCH_CONTROL_ENABLE_BIT  17
#define IA32_FEATURE_CONTROL_REGISTER_SGX_LAUNCH_CONTROL_ENABLE_MASK 0x01
#define IA32_FEATURE_CONTROL_REGISTER_SGX_LAUNCH_CONTROL_ENABLE(_)   (((_) >> 17) & 0x01)

    /**
     * @brief SGX Global Enable <b>(R/WL)</b>
     *
     * [Bit 18] This bit must be set to enable SGX leaf functions.
     *
     * @remarks If CPUID.(EAX=07H, ECX=0H): EBX[2] = 1
     */
    UINT64 SgxGlobalEnable                                         : 1;
#define IA32_FEATURE_CONTROL_REGISTER_SGX_GLOBAL_ENABLE_BIT          18
#define IA32_FEATURE_CONTROL_REGISTER_SGX_GLOBAL_ENABLE_MASK         0x01
#define IA32_FEATURE_CONTROL_REGISTER_SGX_GLOBAL_ENABLE(_)           (((_) >> 18) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * @brief LMCE On <b>(R/WL)</b>
     *
     * [Bit 20] When set, system software can program the MSRs associated with LMCE to configure delivery of some machine check
     * exceptions to a single logical processor.
     *
     * @remarks If IA32_MCG_CAP[27] = 1
     */
    UINT64 LmceOn                                                  : 1;
#define IA32_FEATURE_CONTROL_REGISTER_LMCE_ON_BIT                    20
#define IA32_FEATURE_CONTROL_REGISTER_LMCE_ON_MASK                   0x01
#define IA32_FEATURE_CONTROL_REGISTER_LMCE_ON(_)                     (((_) >> 20) & 0x01)
    UINT64 Reserved4                                               : 43;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_FEATURE_CONTROL_REGISTER;

/**
 * Per Logical Processor TSC Adjust.
 *
 * @remarks If CPUID.(EAX=07H, ECX=0H): EBX[1] = 1
 */
#define IA32_TSC_ADJUST                                              0x0000003B

typedef struct
{
  UINT64 ThreadAdjust;
} IA32_TSC_ADJUST_REGISTER;

/**
 * @brief BIOS Update Trigger <b>(W)</b>
 *
 * Executing a WRMSR instruction to this MSR causes a microcode update to be loaded into the processor. A processor may
 * prevent writing to this MSR when loading guest states on VM entries or saving guest states on VM exits.
 *
 * @remarks 06_01H
 * @see Vol3A[9.11.6(Microcode Update Loader)]
 */
#define IA32_BIOS_UPDATE_TRIGGER                                     0x00000079

/**
 * @brief BIOS Update Signature <b>(RO)</b>
 *
 * Returns the microcode update signature following the execution of CPUID.01H. A processor may prevent writing to this MSR
 * when loading guest states on VM entries or saving guest states on VM exits.
 *
 * @remarks 06_01H
 */
#define IA32_BIOS_UPDATE_SIGNATURE                                   0x0000008B

typedef struct
{
  UINT32 Reserved;
  UINT32 MicrocodeUpdateSignature;
} IA32_BIOS_UPDATE_SIGNATURE_REGISTER;

/**
 * @defgroup IA32_SGXLEPUBKEYHASH \
 *           IA32_SGXLEPUBKEYHASH[(64*n+63):(64*n)]
 *
 * Bits (64*n+63):(64*n) of the SHA256 digest of the SIGSTRUCT.MODULUS for SGX Launch Enclave. On reset, the default value
 * is the digest of Intel's signing key.
 *
 * @remarks Read permitted If CPUID.(EAX=12H,ECX=0H): EAX[0]=1 && CPUID.(EAX=07H,ECX=0H):ECX[30]=1. Write permitted if
 *          CPUID.(EAX=12H,ECX=0H): EAX[0]=1 && IA32_FEATURE_CONTROL[17] = 1 && IA32_FEATURE_CONTROL[0] = 1.
 * @{
 */
#define IA32_SGXLEPUBKEYHASH0                                        0x0000008C
#define IA32_SGXLEPUBKEYHASH1                                        0x0000008D
#define IA32_SGXLEPUBKEYHASH2                                        0x0000008E
#define IA32_SGXLEPUBKEYHASH3                                        0x0000008F
/**
 * @}
 */

/**
 * SMM Monitor Configuration.
 *
 * @remarks If CPUID.01H: ECX[5]=1 || CPUID.01H: ECX[6] = 1
 */
#define IA32_SMM_MONITOR_CTL                                         0x0000009B

typedef union
{
  struct
  {
    /**
     * @brief Valid <b>(R/W)</b>
     *
     * [Bit 0] The STM may be invoked using VMCALL only if this bit is 1. Because VMCALL is used to activate the dual-monitor
     * treatment, the dual-monitor treatment cannot be activated if the bit is 0. This bit is cleared when the logical
     * processor is reset.
     *
     * @see Vol3C[34.15.6(Activating the Dual-Monitor Treatment)]
     * @see Vol3C[34.15.5(Enabling the Dual-Monitor Treatment)] (reference)
     */
    UINT64 Valid                                                   : 1;
#define IA32_SMM_MONITOR_CTL_REGISTER_VALID_BIT                      0
#define IA32_SMM_MONITOR_CTL_REGISTER_VALID_MASK                     0x01
#define IA32_SMM_MONITOR_CTL_REGISTER_VALID(_)                       (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * @brief Controls SMI unblocking by VMXOFF
     *
     * [Bit 2] Determines whether executions of VMXOFF unblock SMIs under the default treatment of SMIs and SMM. Executions of
     * VMXOFF unblock SMIs unless bit 2 is 1 (the value of bit 0 is irrelevant).
     *
     * @remarks If IA32_VMX_MISC[28]
     * @see Vol3C[34.14.4(VMXOFF and SMI Unblocking)]
     * @see Vol3C[34.15.5(Enabling the Dual-Monitor Treatment)] (reference)
     */
    UINT64 SmiUnblockingByVmxoff                                   : 1;
#define IA32_SMM_MONITOR_CTL_REGISTER_SMI_UNBLOCKING_BY_VMXOFF_BIT   2
#define IA32_SMM_MONITOR_CTL_REGISTER_SMI_UNBLOCKING_BY_VMXOFF_MASK  0x01
#define IA32_SMM_MONITOR_CTL_REGISTER_SMI_UNBLOCKING_BY_VMXOFF(_)    (((_) >> 2) & 0x01)
    UINT64 Reserved2                                               : 9;

    /**
     * @brief MSEG Base <b>(R/W)</b>
     *
     * [Bits 31:12] Value that, when shifted left 12 bits, is the physical address of MSEG (the MSEG base address).
     *
     * @see Vol3C[34.15.5(Enabling the Dual-Monitor Treatment)] (reference)
     */
    UINT64 MsegBase                                                : 20;
#define IA32_SMM_MONITOR_CTL_REGISTER_MSEG_BASE_BIT                  12
#define IA32_SMM_MONITOR_CTL_REGISTER_MSEG_BASE_MASK                 0xFFFFF
#define IA32_SMM_MONITOR_CTL_REGISTER_MSEG_BASE(_)                   (((_) >> 12) & 0xFFFFF)
    UINT64 Reserved3                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMM_MONITOR_CTL_REGISTER;

typedef struct
{
  UINT32 MsegHeaderRevision;
  UINT32 MonitorFeatures;

  /**
   * Define values for the MonitorFeatures field of MSEG_HEADER.
   */
#define IA32_STM_FEATURES_IA32E                                      0x00000001

  UINT32 GdtrLimit;
  UINT32 GdtrBaseOffset;
  UINT32 CsSelector;
  UINT32 EipOffset;
  UINT32 EspOffset;
  UINT32 Cr3Offset;
} IA32_MSEG_HEADER;

/**
 * Base address of the logical processor's SMRAM image.
 *
 * @remarks If IA32_VMX_MISC[15]
 */
#define IA32_SMBASE                                                  0x0000009E

/**
 * @defgroup IA32_PMC \
 *           IA32_PMC(n)
 *
 * General Performance Counters.
 *
 * @remarks If CPUID.0AH: EAX[15:8] > n
 * @{
 */
#define IA32_PMC0                                                    0x000000C1
#define IA32_PMC1                                                    0x000000C2
#define IA32_PMC2                                                    0x000000C3
#define IA32_PMC3                                                    0x000000C4
#define IA32_PMC4                                                    0x000000C5
#define IA32_PMC5                                                    0x000000C6
#define IA32_PMC6                                                    0x000000C7
#define IA32_PMC7                                                    0x000000C8
/**
 * @}
 */

/**
 * TSC Frequency Clock Counter.
 *
 * @remarks If CPUID.06H: ECX[0] = 1
 */
#define IA32_MPERF                                                   0x000000E7

typedef struct
{
  UINT64 C0Mcnt;
} IA32_MPERF_REGISTER;

/**
 * Actual Performance Clock Counter
 *
 * @remarks If CPUID.06H: ECX[0] = 1
 */
#define IA32_APERF                                                   0x000000E8

typedef struct
{
  UINT64 C0Acnt;
} IA32_APERF_REGISTER;

/**
 * MTRR Capability.
 *
 * @see Vol3A[11.11.2.1(IA32_MTRR_DEF_TYPE MSR)]
 * @see Vol3A[11.11.1(MTRR Feature Identification)] (reference)
 */
#define IA32_MTRR_CAPABILITIES                                       0x000000FE

typedef union
{
  struct
  {
    /**
     * @brief VCNT (variable range registers count) field
     *
     * [Bits 7:0] Indicates the number of variable ranges implemented on the processor.
     */
    UINT64 VariableRangeCount                                      : 8;
#define IA32_MTRR_CAPABILITIES_REGISTER_VARIABLE_RANGE_COUNT_BIT     0
#define IA32_MTRR_CAPABILITIES_REGISTER_VARIABLE_RANGE_COUNT_MASK    0xFF
#define IA32_MTRR_CAPABILITIES_REGISTER_VARIABLE_RANGE_COUNT(_)      (((_) >> 0) & 0xFF)

    /**
     * @brief FIX (fixed range registers supported) flag
     *
     * [Bit 8] Fixed range MTRRs (IA32_MTRR_FIX64K_00000 through IA32_MTRR_FIX4K_0F8000) are supported when set; no fixed range
     * registers are supported when clear.
     */
    UINT64 FixedRangeSupported                                     : 1;
#define IA32_MTRR_CAPABILITIES_REGISTER_FIXED_RANGE_SUPPORTED_BIT    8
#define IA32_MTRR_CAPABILITIES_REGISTER_FIXED_RANGE_SUPPORTED_MASK   0x01
#define IA32_MTRR_CAPABILITIES_REGISTER_FIXED_RANGE_SUPPORTED(_)     (((_) >> 8) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * @brief WC (write combining) flag
     *
     * [Bit 10] The write-combining (WC) memory type is supported when set; the WC type is not supported when clear.
     */
    UINT64 WcSupported                                             : 1;
#define IA32_MTRR_CAPABILITIES_REGISTER_WC_SUPPORTED_BIT             10
#define IA32_MTRR_CAPABILITIES_REGISTER_WC_SUPPORTED_MASK            0x01
#define IA32_MTRR_CAPABILITIES_REGISTER_WC_SUPPORTED(_)              (((_) >> 10) & 0x01)

    /**
     * @brief SMRR (System-Management Range Register) flag
     *
     * [Bit 11] The system-management range register (SMRR) interface is supported when bit 11 is set; the SMRR interface is
     * not supported when clear.
     */
    UINT64 SmrrSupported                                           : 1;
#define IA32_MTRR_CAPABILITIES_REGISTER_SMRR_SUPPORTED_BIT           11
#define IA32_MTRR_CAPABILITIES_REGISTER_SMRR_SUPPORTED_MASK          0x01
#define IA32_MTRR_CAPABILITIES_REGISTER_SMRR_SUPPORTED(_)            (((_) >> 11) & 0x01)
    UINT64 Reserved2                                               : 52;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MTRR_CAPABILITIES_REGISTER;

/**
 * @brief SYSENTER_CS_MSR <b>(R/W)</b>
 *
 * The lower 16 bits of this MSR are the segment selector for the privilege level 0 code segment. This value is also used
 * to determine the segment selector of the privilege level 0 stack segment. This value cannot indicate a null selector.
 *
 * @remarks 06_01H
 * @see Vol2B[4.3(Instructions (M-U) | SYSCALL - Fast System Call)] (reference)
 */
#define IA32_SYSENTER_CS                                             0x00000174

typedef struct
{
  UINT16 CsSelector;
  UINT16 NotUsed1;
  UINT32 NotUsed2;
} IA32_SYSENTER_CS_REGISTER;

/**
 * @brief SYSENTER_ESP_MSR <b>(R/W)</b>
 *
 * The value of this MSR is loaded into RSP (thus, this value contains the stack pointer for the privilege level 0 stack).
 * This value cannot represent a non-canonical address. In protected mode, only bits 31:0 are loaded.
 *
 * @remarks 06_01H
 * @see Vol2B[4.3(Instructions (M-U) | SYSCALL - Fast System Call)] (reference)
 */
#define IA32_SYSENTER_ESP                                            0x00000175

/**
 * @brief SYSENTER_EIP_MSR <b>(R/W)</b>
 *
 * The value of this MSR is loaded into RIP (thus, this value references the first instruction of the selected operating
 * procedure or routine). In protected mode, only bits 31:0 are loaded.
 *
 * @remarks 06_01H
 * @see Vol2B[4.3(Instructions (M-U) | SYSCALL - Fast System Call)] (reference)
 */
#define IA32_SYSENTER_EIP                                            0x00000176

/**
 * Global Machine Check Capability.
 *
 * @remarks 06_01H
 */
#define IA32_MCG_CAP                                                 0x00000179

typedef union
{
  struct
  {
    /**
     * [Bits 7:0] Number of reporting banks.
     */
    UINT64 Count                                                   : 8;
#define IA32_MCG_CAP_REGISTER_COUNT_BIT                              0
#define IA32_MCG_CAP_REGISTER_COUNT_MASK                             0xFF
#define IA32_MCG_CAP_REGISTER_COUNT(_)                               (((_) >> 0) & 0xFF)

    /**
     * [Bit 8] IA32_MCG_CTL is present if this bit is set.
     */
    UINT64 McgCtlP                                                 : 1;
#define IA32_MCG_CAP_REGISTER_MCG_CTL_P_BIT                          8
#define IA32_MCG_CAP_REGISTER_MCG_CTL_P_MASK                         0x01
#define IA32_MCG_CAP_REGISTER_MCG_CTL_P(_)                           (((_) >> 8) & 0x01)

    /**
     * [Bit 9] Extended machine check state registers are present if this bit is set.
     */
    UINT64 McgExtP                                                 : 1;
#define IA32_MCG_CAP_REGISTER_MCG_EXT_P_BIT                          9
#define IA32_MCG_CAP_REGISTER_MCG_EXT_P_MASK                         0x01
#define IA32_MCG_CAP_REGISTER_MCG_EXT_P(_)                           (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Support for corrected MC error event is present.
     *
     * @remarks 06_01H
     */
    UINT64 McpCmciP                                                : 1;
#define IA32_MCG_CAP_REGISTER_MCP_CMCI_P_BIT                         10
#define IA32_MCG_CAP_REGISTER_MCP_CMCI_P_MASK                        0x01
#define IA32_MCG_CAP_REGISTER_MCP_CMCI_P(_)                          (((_) >> 10) & 0x01)

    /**
     * [Bit 11] Threshold-based error status register are present if this bit is set.
     */
    UINT64 McgTesP                                                 : 1;
#define IA32_MCG_CAP_REGISTER_MCG_TES_P_BIT                          11
#define IA32_MCG_CAP_REGISTER_MCG_TES_P_MASK                         0x01
#define IA32_MCG_CAP_REGISTER_MCG_TES_P(_)                           (((_) >> 11) & 0x01)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 23:16] Number of extended machine check state registers present.
     */
    UINT64 McgExtCnt                                               : 8;
#define IA32_MCG_CAP_REGISTER_MCG_EXT_CNT_BIT                        16
#define IA32_MCG_CAP_REGISTER_MCG_EXT_CNT_MASK                       0xFF
#define IA32_MCG_CAP_REGISTER_MCG_EXT_CNT(_)                         (((_) >> 16) & 0xFF)

    /**
     * [Bit 24] The processor supports software error recovery if this bit is set.
     */
    UINT64 McgSerP                                                 : 1;
#define IA32_MCG_CAP_REGISTER_MCG_SER_P_BIT                          24
#define IA32_MCG_CAP_REGISTER_MCG_SER_P_MASK                         0x01
#define IA32_MCG_CAP_REGISTER_MCG_SER_P(_)                           (((_) >> 24) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 26] Indicates that the processor allows platform firmware to be invoked when an error is detected so that it may
     * provide additional platform specific information in an ACPI format "Generic Error Data Entry" that augments the data
     * included in machine check bank registers.
     *
     * @remarks 06_3EH
     */
    UINT64 McgElogP                                                : 1;
#define IA32_MCG_CAP_REGISTER_MCG_ELOG_P_BIT                         26
#define IA32_MCG_CAP_REGISTER_MCG_ELOG_P_MASK                        0x01
#define IA32_MCG_CAP_REGISTER_MCG_ELOG_P(_)                          (((_) >> 26) & 0x01)

    /**
     * [Bit 27] Indicates that the processor supports extended state in IA32_MCG_STATUS and associated MSR necessary to
     * configure Local Machine Check Exception (LMCE).
     *
     * @remarks 06_3EH
     */
    UINT64 McgLmceP                                                : 1;
#define IA32_MCG_CAP_REGISTER_MCG_LMCE_P_BIT                         27
#define IA32_MCG_CAP_REGISTER_MCG_LMCE_P_MASK                        0x01
#define IA32_MCG_CAP_REGISTER_MCG_LMCE_P(_)                          (((_) >> 27) & 0x01)
    UINT64 Reserved3                                               : 36;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MCG_CAP_REGISTER;

/**
 * Global Machine Check Status.
 *
 * @remarks 06_01H
 */
#define IA32_MCG_STATUS                                              0x0000017A

typedef union
{
  struct
  {
    /**
     * [Bit 0] Restart IP valid.
     *
     * @remarks 06_01H
     */
    UINT64 Ripv                                                    : 1;
#define IA32_MCG_STATUS_REGISTER_RIPV_BIT                            0
#define IA32_MCG_STATUS_REGISTER_RIPV_MASK                           0x01
#define IA32_MCG_STATUS_REGISTER_RIPV(_)                             (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Error IP valid.
     *
     * @remarks 06_01H
     */
    UINT64 Eipv                                                    : 1;
#define IA32_MCG_STATUS_REGISTER_EIPV_BIT                            1
#define IA32_MCG_STATUS_REGISTER_EIPV_MASK                           0x01
#define IA32_MCG_STATUS_REGISTER_EIPV(_)                             (((_) >> 1) & 0x01)

    /**
     * [Bit 2] Machine check in progress.
     *
     * @remarks 06_01H
     */
    UINT64 Mcip                                                    : 1;
#define IA32_MCG_STATUS_REGISTER_MCIP_BIT                            2
#define IA32_MCG_STATUS_REGISTER_MCIP_MASK                           0x01
#define IA32_MCG_STATUS_REGISTER_MCIP(_)                             (((_) >> 2) & 0x01)

    /**
     * [Bit 3] If IA32_MCG_CAP.LMCE_P[27] = 1.
     */
    UINT64 LmceS                                                   : 1;
#define IA32_MCG_STATUS_REGISTER_LMCE_S_BIT                          3
#define IA32_MCG_STATUS_REGISTER_LMCE_S_MASK                         0x01
#define IA32_MCG_STATUS_REGISTER_LMCE_S(_)                           (((_) >> 3) & 0x01)
    UINT64 Reserved1                                               : 60;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MCG_STATUS_REGISTER;

/**
 * Global Machine Check Control.
 *
 * @remarks If IA32_MCG_CAP.CTL_P[8] = 1
 */
#define IA32_MCG_CTL                                                 0x0000017B

/**
 * @defgroup IA32_PERFEVTSEL \
 *           IA32_PERFEVTSEL(n)
 *
 * Performance Event Select Register n.
 *
 * @remarks If CPUID.0AH: EAX[15:8] > n
 * @{
 */
#define IA32_PERFEVTSEL0                                             0x00000186
#define IA32_PERFEVTSEL1                                             0x00000187
#define IA32_PERFEVTSEL2                                             0x00000188
#define IA32_PERFEVTSEL3                                             0x00000189
typedef union
{
  struct
  {
    /**
     * [Bits 7:0] Selects a performance event logic unit.
     */
    UINT64 EventSelect                                             : 8;
#define IA32_PERFEVTSEL_REGISTER_EVENT_SELECT_BIT                    0
#define IA32_PERFEVTSEL_REGISTER_EVENT_SELECT_MASK                   0xFF
#define IA32_PERFEVTSEL_REGISTER_EVENT_SELECT(_)                     (((_) >> 0) & 0xFF)

    /**
     * [Bits 15:8] Qualifies the microarchitectural condition to detect on the selected event logic.
     */
    UINT64 UMask                                                   : 8;
#define IA32_PERFEVTSEL_REGISTER_U_MASK_BIT                          8
#define IA32_PERFEVTSEL_REGISTER_U_MASK_MASK                         0xFF
#define IA32_PERFEVTSEL_REGISTER_U_MASK(_)                           (((_) >> 8) & 0xFF)

    /**
     * [Bit 16] Counts while in privilege level is not ring 0.
     */
    UINT64 Usr                                                     : 1;
#define IA32_PERFEVTSEL_REGISTER_USR_BIT                             16
#define IA32_PERFEVTSEL_REGISTER_USR_MASK                            0x01
#define IA32_PERFEVTSEL_REGISTER_USR(_)                              (((_) >> 16) & 0x01)

    /**
     * [Bit 17] Counts while in privilege level is ring 0.
     */
    UINT64 Os                                                      : 1;
#define IA32_PERFEVTSEL_REGISTER_OS_BIT                              17
#define IA32_PERFEVTSEL_REGISTER_OS_MASK                             0x01
#define IA32_PERFEVTSEL_REGISTER_OS(_)                               (((_) >> 17) & 0x01)

    /**
     * [Bit 18] Enables edge detection if set.
     */
    UINT64 Edge                                                    : 1;
#define IA32_PERFEVTSEL_REGISTER_EDGE_BIT                            18
#define IA32_PERFEVTSEL_REGISTER_EDGE_MASK                           0x01
#define IA32_PERFEVTSEL_REGISTER_EDGE(_)                             (((_) >> 18) & 0x01)

    /**
     * [Bit 19] Enables pin control.
     */
    UINT64 Pc                                                      : 1;
#define IA32_PERFEVTSEL_REGISTER_PC_BIT                              19
#define IA32_PERFEVTSEL_REGISTER_PC_MASK                             0x01
#define IA32_PERFEVTSEL_REGISTER_PC(_)                               (((_) >> 19) & 0x01)

    /**
     * [Bit 20] Enables interrupt on counter overflow.
     */
    UINT64 Intr                                                    : 1;
#define IA32_PERFEVTSEL_REGISTER_INTR_BIT                            20
#define IA32_PERFEVTSEL_REGISTER_INTR_MASK                           0x01
#define IA32_PERFEVTSEL_REGISTER_INTR(_)                             (((_) >> 20) & 0x01)

    /**
     * [Bit 21] When set to 1, it enables counting the associated event conditions occurring across all logical processors
     * sharing a processor core. When set to 0, the counter only increments the associated event conditions occurring in the
     * logical processor which programmed the MSR.
     */
    UINT64 AnyThread                                               : 1;
#define IA32_PERFEVTSEL_REGISTER_ANY_THREAD_BIT                      21
#define IA32_PERFEVTSEL_REGISTER_ANY_THREAD_MASK                     0x01
#define IA32_PERFEVTSEL_REGISTER_ANY_THREAD(_)                       (((_) >> 21) & 0x01)

    /**
     * [Bit 22] Enables the corresponding performance counter to commence counting when this bit is set.
     */
    UINT64 En                                                      : 1;
#define IA32_PERFEVTSEL_REGISTER_EN_BIT                              22
#define IA32_PERFEVTSEL_REGISTER_EN_MASK                             0x01
#define IA32_PERFEVTSEL_REGISTER_EN(_)                               (((_) >> 22) & 0x01)

    /**
     * [Bit 23] Invert the CMASK.
     */
    UINT64 Inv                                                     : 1;
#define IA32_PERFEVTSEL_REGISTER_INV_BIT                             23
#define IA32_PERFEVTSEL_REGISTER_INV_MASK                            0x01
#define IA32_PERFEVTSEL_REGISTER_INV(_)                              (((_) >> 23) & 0x01)

    /**
     * [Bits 31:24] When CMASK is not zero, the corresponding performance counter increments each cycle if the event count is
     * greater than or equal to the CMASK.
     */
    UINT64 Cmask                                                   : 8;
#define IA32_PERFEVTSEL_REGISTER_CMASK_BIT                           24
#define IA32_PERFEVTSEL_REGISTER_CMASK_MASK                          0xFF
#define IA32_PERFEVTSEL_REGISTER_CMASK(_)                            (((_) >> 24) & 0xFF)
    UINT64 Reserved1                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERFEVTSEL_REGISTER;

/**
 * @}
 */

/**
 * Current Performance Status.
 *
 * @remarks 0F_03H
 * @see Vol3B[14.1.1(Software Interface For Initiating Performance State Transitions)]
 */
#define IA32_PERF_STATUS                                             0x00000198

typedef struct
{
  UINT16 StateValue;
} IA32_PERF_STATUS_REGISTER;

/**
 * @brief Performance Control <b>(R/W)</b>
 *
 * Performance Control. Software makes a request for a new Performance state (P-State) by writing this MSR.
 *
 * @remarks 0F_03H
 * @see Vol3B[14.1.1(Software Interface For Initiating Performance State Transitions)]
 */
#define IA32_PERF_CTL                                                0x00000199

typedef union
{
  struct
  {
    /**
     * [Bits 15:0] Target performance State Value.
     */
    UINT64 TargetStateValue                                        : 16;
#define IA32_PERF_CTL_REGISTER_TARGET_STATE_VALUE_BIT                0
#define IA32_PERF_CTL_REGISTER_TARGET_STATE_VALUE_MASK               0xFFFF
#define IA32_PERF_CTL_REGISTER_TARGET_STATE_VALUE(_)                 (((_) >> 0) & 0xFFFF)
    UINT64 Reserved1                                               : 16;

    /**
     * [Bit 32] IDA Engage.
     *
     * @remarks 06_0FH (Mobile only)
     */
    UINT64 IdaEngage                                               : 1;
#define IA32_PERF_CTL_REGISTER_IDA_ENGAGE_BIT                        32
#define IA32_PERF_CTL_REGISTER_IDA_ENGAGE_MASK                       0x01
#define IA32_PERF_CTL_REGISTER_IDA_ENGAGE(_)                         (((_) >> 32) & 0x01)
    UINT64 Reserved2                                               : 31;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERF_CTL_REGISTER;

/**
 * Clock Modulation Control.
 *
 * @remarks If CPUID.01H:EDX[22] = 1
 * @see Vol3B[14.7.3(Software Controlled Clock Modulation)]
 */
#define IA32_CLOCK_MODULATION                                        0x0000019A

typedef union
{
  struct
  {
    /**
     * [Bit 0] Extended On-Demand Clock Modulation Duty Cycle.
     *
     * @remarks If CPUID.06H:EAX[5] = 1
     */
    UINT64 ExtendedOnDemandClockModulationDutyCycle                : 1;
#define IA32_CLOCK_MODULATION_REGISTER_EXTENDED_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE_BIT 0
#define IA32_CLOCK_MODULATION_REGISTER_EXTENDED_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE_MASK 0x01
#define IA32_CLOCK_MODULATION_REGISTER_EXTENDED_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE(_) (((_) >> 0) & 0x01)

    /**
     * @brief On-Demand Clock Modulation Duty Cycle
     *
     * [Bits 3:1] On-Demand Clock Modulation Duty Cycle: Specific encoded values for target duty cycle modulation.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 OnDemandClockModulationDutyCycle                        : 3;
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE_BIT 1
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE_MASK 0x07
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_DUTY_CYCLE(_) (((_) >> 1) & 0x07)

    /**
     * @brief On-Demand Clock Modulation Enable
     *
     * [Bit 4] On-Demand Clock Modulation Enable: Set 1 to enable modulation.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 OnDemandClockModulationEnable                           : 1;
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_ENABLE_BIT 4
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_ENABLE_MASK 0x01
#define IA32_CLOCK_MODULATION_REGISTER_ON_DEMAND_CLOCK_MODULATION_ENABLE(_) (((_) >> 4) & 0x01)
    UINT64 Reserved1                                               : 59;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_CLOCK_MODULATION_REGISTER;

/**
 * @brief Thermal Interrupt Control <b>(R/W)</b>
 *
 * Thermal Interrupt Control. Enables and disables the generation of an interrupt on temperature transitions detected with
 * the processor's thermal sensors and thermal monitor.
 *
 * @remarks If CPUID.01H:EDX[22] = 1
 * @see Vol3B[14.7.2(Thermal Monitor)]
 */
#define IA32_THERM_INTERRUPT                                         0x0000019B

typedef union
{
  struct
  {
    /**
     * [Bit 0] High-Temperature Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 HighTemperatureInterruptEnable                          : 1;
#define IA32_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE_BIT 0
#define IA32_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE(_) (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Low-Temperature Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 LowTemperatureInterruptEnable                           : 1;
#define IA32_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE_BIT 1
#define IA32_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE(_) (((_) >> 1) & 0x01)

    /**
     * [Bit 2] PROCHOT\# Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ProchotInterruptEnable                                  : 1;
#define IA32_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE_BIT   2
#define IA32_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE_MASK  0x01
#define IA32_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE(_)    (((_) >> 2) & 0x01)

    /**
     * [Bit 3] FORCEPR\# Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ForceprInterruptEnable                                  : 1;
#define IA32_THERM_INTERRUPT_REGISTER_FORCEPR_INTERRUPT_ENABLE_BIT   3
#define IA32_THERM_INTERRUPT_REGISTER_FORCEPR_INTERRUPT_ENABLE_MASK  0x01
#define IA32_THERM_INTERRUPT_REGISTER_FORCEPR_INTERRUPT_ENABLE(_)    (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Critical Temperature Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 CriticalTemperatureInterruptEnable                      : 1;
#define IA32_THERM_INTERRUPT_REGISTER_CRITICAL_TEMPERATURE_INTERRUPT_ENABLE_BIT 4
#define IA32_THERM_INTERRUPT_REGISTER_CRITICAL_TEMPERATURE_INTERRUPT_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_CRITICAL_TEMPERATURE_INTERRUPT_ENABLE(_) (((_) >> 4) & 0x01)
    UINT64 Reserved1                                               : 3;

    /**
     * [Bits 14:8] Threshold \#1 Value
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 Threshold1Value                                         : 7;
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE_BIT           8
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE_MASK          0x7F
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE(_)            (((_) >> 8) & 0x7F)

    /**
     * [Bit 15] Threshold \#1 Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 Threshold1InterruptEnable                               : 1;
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE_BIT 15
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE(_) (((_) >> 15) & 0x01)

    /**
     * [Bits 22:16] Threshold \#2 Value.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 Threshold2Value                                         : 7;
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE_BIT           16
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE_MASK          0x7F
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE(_)            (((_) >> 16) & 0x7F)

    /**
     * [Bit 23] Threshold \#2 Interrupt Enable.
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 Threshold2InterruptEnable                               : 1;
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE_BIT 23
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE(_) (((_) >> 23) & 0x01)

    /**
     * [Bit 24] Power Limit Notification Enable.
     *
     * @remarks If CPUID.06H:EAX[4] = 1
     */
    UINT64 PowerLimitNotificationEnable                            : 1;
#define IA32_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE_BIT 24
#define IA32_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE_MASK 0x01
#define IA32_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE(_) (((_) >> 24) & 0x01)
    UINT64 Reserved2                                               : 39;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_THERM_INTERRUPT_REGISTER;

/**
 * @brief Thermal Status Information <b>(RO)</b>
 *
 * Thermal Status Information. Contains status information about the processor's thermal sensor and automatic thermal
 * monitoring facilities.
 *
 * @remarks If CPUID.01H:EDX[22] = 1
 * @see Vol3B[14.7.2(Thermal Monitor)]
 */
#define IA32_THERM_STATUS                                            0x0000019C

typedef union
{
  struct
  {
    /**
     * [Bit 0] Thermal Status
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ThermalStatus                                           : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS_BIT                0
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS_MASK               0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS(_)                 (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Thermal Status Log
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ThermalStatusLog                                        : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG_BIT            1
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG_MASK           0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG(_)             (((_) >> 1) & 0x01)

    /**
     * [Bit 2] PROCHOT \# or FORCEPR\# event
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ProchotForceprEvent                                     : 1;
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_EVENT_BIT         2
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_EVENT_MASK        0x01
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_EVENT(_)          (((_) >> 2) & 0x01)

    /**
     * [Bit 3] PROCHOT \# or FORCEPR\# log
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 ProchotForceprLog                                       : 1;
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_LOG_BIT           3
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_LOG_MASK          0x01
#define IA32_THERM_STATUS_REGISTER_PROCHOT_FORCEPR_LOG(_)            (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Critical Temperature Status
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 CriticalTemperatureStatus                               : 1;
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_BIT   4
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_MASK  0x01
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS(_)    (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Critical Temperature Status log
     *
     * @remarks If CPUID.01H:EDX[22] = 1
     */
    UINT64 CriticalTemperatureStatusLog                            : 1;
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG_BIT 5
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG_MASK 0x01
#define IA32_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG(_) (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Thermal Threshold \#1 Status
     *
     * @remarks If CPUID.01H:ECX[8] = 1
     */
    UINT64 ThermalThreshold1Status                                 : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS_BIT     6
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS_MASK    0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS(_)      (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Thermal Threshold \#1 log
     *
     * @remarks If CPUID.01H:ECX[8] = 1
     */
    UINT64 ThermalThreshold1Log                                    : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG_BIT        7
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG_MASK       0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG(_)         (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Thermal Threshold \#2 Status
     *
     * @remarks If CPUID.01H:ECX[8] = 1
     */
    UINT64 ThermalThreshold2Status                                 : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS_BIT     8
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS_MASK    0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS(_)      (((_) >> 8) & 0x01)

    /**
     * [Bit 9] Thermal Threshold \#2 log
     *
     * @remarks If CPUID.01H:ECX[8] = 1
     */
    UINT64 ThermalThreshold2Log                                    : 1;
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG_BIT        9
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG_MASK       0x01
#define IA32_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG(_)         (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Power Limitation Status
     *
     * @remarks If CPUID.06H:EAX[4] = 1
     */
    UINT64 PowerLimitationStatus                                   : 1;
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS_BIT       10
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS_MASK      0x01
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS(_)        (((_) >> 10) & 0x01)

    /**
     * [Bit 11] Power Limitation log
     *
     * @remarks If CPUID.06H:EAX[4] = 1
     */
    UINT64 PowerLimitationLog                                      : 1;
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG_BIT          11
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG_MASK         0x01
#define IA32_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG(_)           (((_) >> 11) & 0x01)

    /**
     * [Bit 12] Current Limit Status
     *
     * @remarks If CPUID.06H:EAX[7] = 1
     */
    UINT64 CurrentLimitStatus                                      : 1;
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_STATUS_BIT          12
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_STATUS_MASK         0x01
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_STATUS(_)           (((_) >> 12) & 0x01)

    /**
     * [Bit 13] Current Limit log
     *
     * @remarks If CPUID.06H:EAX[7] = 1
     */
    UINT64 CurrentLimitLog                                         : 1;
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_LOG_BIT             13
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_LOG_MASK            0x01
#define IA32_THERM_STATUS_REGISTER_CURRENT_LIMIT_LOG(_)              (((_) >> 13) & 0x01)

    /**
     * [Bit 14] Cross Domain Limit Status
     *
     * @remarks If CPUID.06H:EAX[7] = 1
     */
    UINT64 CrossDomainLimitStatus                                  : 1;
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_STATUS_BIT     14
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_STATUS_MASK    0x01
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_STATUS(_)      (((_) >> 14) & 0x01)

    /**
     * [Bit 15] Cross Domain Limit log
     *
     * @remarks If CPUID.06H:EAX[7] = 1
     */
    UINT64 CrossDomainLimitLog                                     : 1;
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_LOG_BIT        15
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_LOG_MASK       0x01
#define IA32_THERM_STATUS_REGISTER_CROSS_DOMAIN_LIMIT_LOG(_)         (((_) >> 15) & 0x01)

    /**
     * [Bits 22:16] Digital Readout
     *
     * @remarks If CPUID.06H:EAX[0] = 1
     */
    UINT64 DigitalReadout                                          : 7;
#define IA32_THERM_STATUS_REGISTER_DIGITAL_READOUT_BIT               16
#define IA32_THERM_STATUS_REGISTER_DIGITAL_READOUT_MASK              0x7F
#define IA32_THERM_STATUS_REGISTER_DIGITAL_READOUT(_)                (((_) >> 16) & 0x7F)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 30:27] Resolution in Degrees Celsius
     *
     * @remarks If CPUID.06H:EAX[0] = 1
     */
    UINT64 ResolutionInDegreesCelsius                              : 4;
#define IA32_THERM_STATUS_REGISTER_RESOLUTION_IN_DEGREES_CELSIUS_BIT 27
#define IA32_THERM_STATUS_REGISTER_RESOLUTION_IN_DEGREES_CELSIUS_MASK 0x0F
#define IA32_THERM_STATUS_REGISTER_RESOLUTION_IN_DEGREES_CELSIUS(_)  (((_) >> 27) & 0x0F)

    /**
     * [Bit 31] Reading Valid
     *
     * @remarks If CPUID.06H:EAX[0] = 1
     */
    UINT64 ReadingValid                                            : 1;
#define IA32_THERM_STATUS_REGISTER_READING_VALID_BIT                 31
#define IA32_THERM_STATUS_REGISTER_READING_VALID_MASK                0x01
#define IA32_THERM_STATUS_REGISTER_READING_VALID(_)                  (((_) >> 31) & 0x01)
    UINT64 Reserved2                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_THERM_STATUS_REGISTER;

/**
 * @brief Enable Misc. Processor Features <b>(R/W)</b>
 *
 * Allows a variety of processor functions to be enabled and disabled.
 */
#define IA32_MISC_ENABLE                                             0x000001A0

typedef union
{
  struct
  {
    /**
     * @brief Fast-Strings Enable
     *
     * [Bit 0] When set, the fast-strings feature (for REP MOVS and REP STORS) is enabled (default). When clear, fast-strings
     * are disabled.
     *
     * @remarks 0F_0H
     */
    UINT64 FastStringsEnable                                       : 1;
#define IA32_MISC_ENABLE_REGISTER_FAST_STRINGS_ENABLE_BIT            0
#define IA32_MISC_ENABLE_REGISTER_FAST_STRINGS_ENABLE_MASK           0x01
#define IA32_MISC_ENABLE_REGISTER_FAST_STRINGS_ENABLE(_)             (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 2;

    /**
     * @brief Automatic Thermal Control Circuit Enable <b>(R/W)</b>
     *
     * [Bit 3] - 1 = Setting this bit enables the thermal control circuit (TCC) portion of the Intel Thermal Monitor feature.
     * This allows the processor to automatically reduce power consumption in response to TCC activation.
     * - 0 = Disabled.
     *
     * @note In some products clearing this bit might be ignored in critical thermal conditions, and TM1, TM2 and adaptive
     *       thermal throttling will still be activated. The default value of this field varies with product.
     * @remarks 0F_0H
     */
    UINT64 AutomaticThermalControlCircuitEnable                    : 1;
#define IA32_MISC_ENABLE_REGISTER_AUTOMATIC_THERMAL_CONTROL_CIRCUIT_ENABLE_BIT 3
#define IA32_MISC_ENABLE_REGISTER_AUTOMATIC_THERMAL_CONTROL_CIRCUIT_ENABLE_MASK 0x01
#define IA32_MISC_ENABLE_REGISTER_AUTOMATIC_THERMAL_CONTROL_CIRCUIT_ENABLE(_) (((_) >> 3) & 0x01)
    UINT64 Reserved2                                               : 3;

    /**
     * @brief Performance Monitoring Available <b>(R)</b>
     *
     * [Bit 7] - 1 = Performance monitoring enabled.
     * - 0 = Performance monitoring disabled.
     *
     * @remarks 0F_0H
     */
    UINT64 PerformanceMonitoringAvailable                          : 1;
#define IA32_MISC_ENABLE_REGISTER_PERFORMANCE_MONITORING_AVAILABLE_BIT 7
#define IA32_MISC_ENABLE_REGISTER_PERFORMANCE_MONITORING_AVAILABLE_MASK 0x01
#define IA32_MISC_ENABLE_REGISTER_PERFORMANCE_MONITORING_AVAILABLE(_) (((_) >> 7) & 0x01)
    UINT64 Reserved3                                               : 3;

    /**
     * @brief Branch Trace Storage Unavailable <b>(RO)</b>
     *
     * [Bit 11] - 1 = Processor doesn't support branch trace storage (BTS).
     * - 0 = BTS is supported.
     *
     * @remarks 0F_0H
     */
    UINT64 BranchTraceStorageUnavailable                           : 1;
#define IA32_MISC_ENABLE_REGISTER_BRANCH_TRACE_STORAGE_UNAVAILABLE_BIT 11
#define IA32_MISC_ENABLE_REGISTER_BRANCH_TRACE_STORAGE_UNAVAILABLE_MASK 0x01
#define IA32_MISC_ENABLE_REGISTER_BRANCH_TRACE_STORAGE_UNAVAILABLE(_) (((_) >> 11) & 0x01)

    /**
     * @brief Processor Event Based Sampling (PEBS) Unavailable <b>(RO)</b>
     *
     * [Bit 12] - 1 = PEBS is not supported.
     * - 0 = PEBS is supported.
     *
     * @remarks 06_0FH
     */
    UINT64 ProcessorEventBasedSamplingUnavailable                  : 1;
#define IA32_MISC_ENABLE_REGISTER_PROCESSOR_EVENT_BASED_SAMPLING_UNAVAILABLE_BIT 12
#define IA32_MISC_ENABLE_REGISTER_PROCESSOR_EVENT_BASED_SAMPLING_UNAVAILABLE_MASK 0x01
#define IA32_MISC_ENABLE_REGISTER_PROCESSOR_EVENT_BASED_SAMPLING_UNAVAILABLE(_) (((_) >> 12) & 0x01)
    UINT64 Reserved4                                               : 3;

    /**
     * @brief Enhanced Intel SpeedStep Technology Enable <b>(R/W)</b>
     *
     * [Bit 16] - 0 = Enhanced Intel SpeedStep Technology disabled.
     * - 1 = Enhanced Intel SpeedStep Technology enabled.
     *
     * @remarks If CPUID.01H: ECX[7] = 1
     */
    UINT64 EnhancedIntelSpeedstepTechnologyEnable                  : 1;
#define IA32_MISC_ENABLE_REGISTER_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY_ENABLE_BIT 16
#define IA32_MISC_ENABLE_REGISTER_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY_ENABLE_MASK 0x01
#define IA32_MISC_ENABLE_REGISTER_ENHANCED_INTEL_SPEEDSTEP_TECHNOLOGY_ENABLE(_) (((_) >> 16) & 0x01)
    UINT64 Reserved5                                               : 1;

    /**
     * @brief ENABLE MONITOR FSM <b>(R/W)</b>
     *
     * [Bit 18] When this bit is set to 0, the MONITOR feature flag is not set (CPUID.01H:ECX[bit3] = 0). This indicates that
     * MONITOR/MWAIT are not supported. Software attempts to execute MONITOR/MWAIT will cause \#UD when this bit is 0.
     * When this bit is set to 1 (default), MONITOR/MWAIT are supported (CPUID.01H:ECX[bit 3] = 1). If the SSE3 feature flag
     * ECX[0] is not set (CPUID.01H:ECX[bit 0] = 0), the OS must not attempt to alter this bit. BIOS must leave it in the
     * default state. Writing this bit when the SSE3 feature flag is set to 0 may generate a \#GP exception.
     *
     * @remarks 0F_03H
     */
    UINT64 EnableMonitorFsm                                        : 1;
#define IA32_MISC_ENABLE_REGISTER_ENABLE_MONITOR_FSM_BIT             18
#define IA32_MISC_ENABLE_REGISTER_ENABLE_MONITOR_FSM_MASK            0x01
#define IA32_MISC_ENABLE_REGISTER_ENABLE_MONITOR_FSM(_)              (((_) >> 18) & 0x01)
    UINT64 Reserved6                                               : 3;

    /**
     * @brief Limit CPUID Maxval <b>(R/W)</b>
     *
     * [Bit 22] When this bit is set to 1, CPUID.00H returns a maximum value in EAX[7:0] of 2. BIOS should contain a setup
     * question that allows users to specify when the installed OS does not support CPUID functions greater than 2.
     * Before setting this bit, BIOS must execute the CPUID.0H and examine the maximum value returned in EAX[7:0]. If the
     * maximum value is greater than 2, this bit is supported.
     * Otherwise, this bit is not supported. Setting this bit when the maximum value is not greater than 2 may generate a \#GP
     * exception. Setting this bit may cause unexpected behavior in software that depends on the availability of CPUID leaves
     * greater than 2.
     *
     * @remarks 0F_03H
     */
    UINT64 LimitCpuidMaxval                                        : 1;
#define IA32_MISC_ENABLE_REGISTER_LIMIT_CPUID_MAXVAL_BIT             22
#define IA32_MISC_ENABLE_REGISTER_LIMIT_CPUID_MAXVAL_MASK            0x01
#define IA32_MISC_ENABLE_REGISTER_LIMIT_CPUID_MAXVAL(_)              (((_) >> 22) & 0x01)

    /**
     * @brief xTPR Message Disable <b>(R/W)</b>
     *
     * [Bit 23] When set to 1, xTPR messages are disabled. xTPR messages are optional messages that allow the processor to
     * inform the chipset of its priority.
     *
     * @remarks If CPUID.01H:ECX[14] = 1
     */
    UINT64 XtprMessageDisable                                      : 1;
#define IA32_MISC_ENABLE_REGISTER_XTPR_MESSAGE_DISABLE_BIT           23
#define IA32_MISC_ENABLE_REGISTER_XTPR_MESSAGE_DISABLE_MASK          0x01
#define IA32_MISC_ENABLE_REGISTER_XTPR_MESSAGE_DISABLE(_)            (((_) >> 23) & 0x01)
    UINT64 Reserved7                                               : 10;

    /**
     * @brief XD Bit Disable <b>(R/W)</b>
     *
     * [Bit 34] When set to 1, the Execute Disable Bit feature (XD Bit) is disabled and the XD Bit extended feature flag will
     * be clear (CPUID.80000001H: EDX[20]=0).
     * When set to a 0 (default), the Execute Disable Bit feature (if available) allows the OS to enable PAE paging and take
     * advantage of data only pages.
     * BIOS must not alter the contents of this bit location, if XD bit is not supported. Writing this bit to 1 when the XD Bit
     * extended feature flag is set to 0 may generate a \#GP exception.
     *
     * @remarks If CPUID.80000001H:EDX[20] = 1
     */
    UINT64 XdBitDisable                                            : 1;
#define IA32_MISC_ENABLE_REGISTER_XD_BIT_DISABLE_BIT                 34
#define IA32_MISC_ENABLE_REGISTER_XD_BIT_DISABLE_MASK                0x01
#define IA32_MISC_ENABLE_REGISTER_XD_BIT_DISABLE(_)                  (((_) >> 34) & 0x01)
    UINT64 Reserved8                                               : 29;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MISC_ENABLE_REGISTER;

/**
 * Performance Energy Bias Hint.
 *
 * @remarks If CPUID.6H:ECX[3] = 1
 */
#define IA32_ENERGY_PERF_BIAS                                        0x000001B0

typedef union
{
  struct
  {
    /**
     * @brief Power Policy Preference
     *
     * [Bits 3:0] - 0 indicates preference to highest performance.
     * - 15 indicates preference to maximize energy saving.
     */
    UINT64 PowerPolicyPreference                                   : 4;
#define IA32_ENERGY_PERF_BIAS_REGISTER_POWER_POLICY_PREFERENCE_BIT   0
#define IA32_ENERGY_PERF_BIAS_REGISTER_POWER_POLICY_PREFERENCE_MASK  0x0F
#define IA32_ENERGY_PERF_BIAS_REGISTER_POWER_POLICY_PREFERENCE(_)    (((_) >> 0) & 0x0F)
    UINT64 Reserved1                                               : 60;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_ENERGY_PERF_BIAS_REGISTER;

/**
 * @brief Package Thermal Status Information <b>(RO)</b>
 *
 * Package Thermal Status Information. Contains status information about the package's thermal sensor.
 *
 * @remarks If CPUID.06H: EAX[6] = 1
 * @see Vol3B[14.8(PACKAGE LEVEL THERMAL MANAGEMENT)]
 */
#define IA32_PACKAGE_THERM_STATUS                                    0x000001B1

typedef union
{
  struct
  {
    /**
     * [Bit 0] Pkg Thermal Status
     */
    UINT64 ThermalStatus                                           : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS_BIT        0
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS_MASK       0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS(_)         (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Pkg Thermal Status Log
     */
    UINT64 ThermalStatusLog                                        : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG_BIT    1
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG_MASK   0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_STATUS_LOG(_)     (((_) >> 1) & 0x01)

    /**
     * [Bit 2] Pkg PROCHOT \# event
     */
    UINT64 ProchotEvent                                            : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_EVENT_BIT         2
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_EVENT_MASK        0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_EVENT(_)          (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Pkg PROCHOT \# log
     */
    UINT64 ProchotLog                                              : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_LOG_BIT           3
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_LOG_MASK          0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_PROCHOT_LOG(_)            (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Pkg Critical Temperature Status
     */
    UINT64 CriticalTemperatureStatus                               : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_BIT 4
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS(_) (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Pkg Critical Temperature Status Log
     */
    UINT64 CriticalTemperatureStatusLog                            : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG_BIT 5
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_CRITICAL_TEMPERATURE_STATUS_LOG(_) (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Pkg Thermal Threshold \#1 Status
     */
    UINT64 ThermalThreshold1Status                                 : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS_BIT 6
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_STATUS(_) (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Pkg Thermal Threshold \#1 log
     */
    UINT64 ThermalThreshold1Log                                    : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG_BIT 7
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD1_LOG(_) (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Pkg Thermal Threshold \#2 Status
     */
    UINT64 ThermalThreshold2Status                                 : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS_BIT 8
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_STATUS(_) (((_) >> 8) & 0x01)

    /**
     * [Bit 9] Pkg Thermal Threshold \#2 log
     */
    UINT64 ThermalThreshold2Log                                    : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG_BIT 9
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_THERMAL_THRESHOLD2_LOG(_) (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Pkg Power Limitation Status
     */
    UINT64 PowerLimitationStatus                                   : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS_BIT 10
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_STATUS(_) (((_) >> 10) & 0x01)

    /**
     * [Bit 11] Pkg Power Limitation log
     */
    UINT64 PowerLimitationLog                                      : 1;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG_BIT  11
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG_MASK 0x01
#define IA32_PACKAGE_THERM_STATUS_REGISTER_POWER_LIMITATION_LOG(_)   (((_) >> 11) & 0x01)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 22:16] Pkg Digital Readout
     */
    UINT64 DigitalReadout                                          : 7;
#define IA32_PACKAGE_THERM_STATUS_REGISTER_DIGITAL_READOUT_BIT       16
#define IA32_PACKAGE_THERM_STATUS_REGISTER_DIGITAL_READOUT_MASK      0x7F
#define IA32_PACKAGE_THERM_STATUS_REGISTER_DIGITAL_READOUT(_)        (((_) >> 16) & 0x7F)
    UINT64 Reserved2                                               : 41;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PACKAGE_THERM_STATUS_REGISTER;

/**
 * @brief Package Thermal Interrupt Control <b>(RO)</b>
 *
 * Enables and disables the generation of an interrupt on temperature transitions detected with the package's thermal
 * sensor.
 *
 * @remarks If CPUID.06H: EAX[6] = 1
 * @see Vol3B[14.8(PACKAGE LEVEL THERMAL MANAGEMENT)]
 */
#define IA32_PACKAGE_THERM_INTERRUPT                                 0x000001B2

typedef union
{
  struct
  {
    /**
     * [Bit 0] Pkg High-Temperature Interrupt Enable.
     */
    UINT64 HighTemperatureInterruptEnable                          : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE_BIT 0
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_HIGH_TEMPERATURE_INTERRUPT_ENABLE(_) (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Pkg Low-Temperature Interrupt Enable.
     */
    UINT64 LowTemperatureInterruptEnable                           : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE_BIT 1
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_LOW_TEMPERATURE_INTERRUPT_ENABLE(_) (((_) >> 1) & 0x01)

    /**
     * [Bit 2] Pkg PROCHOT\# Interrupt Enable.
     */
    UINT64 ProchotInterruptEnable                                  : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE_BIT 2
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_PROCHOT_INTERRUPT_ENABLE(_) (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 4] Pkg Overheat Interrupt Enable.
     */
    UINT64 OverheatInterruptEnable                                 : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_OVERHEAT_INTERRUPT_ENABLE_BIT 4
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_OVERHEAT_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_OVERHEAT_INTERRUPT_ENABLE(_) (((_) >> 4) & 0x01)
    UINT64 Reserved2                                               : 3;

    /**
     * [Bits 14:8] Pkg Threshold \#1 Value
     */
    UINT64 Threshold1Value                                         : 7;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE_BIT   8
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE_MASK  0x7F
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_VALUE(_)    (((_) >> 8) & 0x7F)

    /**
     * [Bit 15] Pkg Threshold \#1 Interrupt Enable.
     */
    UINT64 Threshold1InterruptEnable                               : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE_BIT 15
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD1_INTERRUPT_ENABLE(_) (((_) >> 15) & 0x01)

    /**
     * [Bits 22:16] Pkg Threshold \#2 Value.
     */
    UINT64 Threshold2Value                                         : 7;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE_BIT   16
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE_MASK  0x7F
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_VALUE(_)    (((_) >> 16) & 0x7F)

    /**
     * [Bit 23] Pkg Threshold \#2 Interrupt Enable.
     */
    UINT64 Threshold2InterruptEnable                               : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE_BIT 23
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_THRESHOLD2_INTERRUPT_ENABLE(_) (((_) >> 23) & 0x01)

    /**
     * [Bit 24] Pkg Power Limit Notification Enable.
     */
    UINT64 PowerLimitNotificationEnable                            : 1;
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE_BIT 24
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE_MASK 0x01
#define IA32_PACKAGE_THERM_INTERRUPT_REGISTER_POWER_LIMIT_NOTIFICATION_ENABLE(_) (((_) >> 24) & 0x01)
    UINT64 Reserved3                                               : 39;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PACKAGE_THERM_INTERRUPT_REGISTER;

/**
 * Trace/Profile Resource Control.
 *
 * @remarks 06_0EH
 */
#define IA32_DEBUGCTL                                                0x000001D9

typedef union
{
  struct
  {
    /**
     * [Bit 0] Setting this bit to 1 enables the processor to record a running trace of the most recent branches taken by the
     * processor in the LBR stack.
     *
     * @remarks 06_01H
     */
    UINT64 Lbr                                                     : 1;
#define IA32_DEBUGCTL_REGISTER_LBR_BIT                               0
#define IA32_DEBUGCTL_REGISTER_LBR_MASK                              0x01
#define IA32_DEBUGCTL_REGISTER_LBR(_)                                (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Setting this bit to 1 enables the processor to treat EFLAGS.TF as single-step on branches instead of single-step
     * on instructions.
     *
     * @remarks 06_01H
     */
    UINT64 Btf                                                     : 1;
#define IA32_DEBUGCTL_REGISTER_BTF_BIT                               1
#define IA32_DEBUGCTL_REGISTER_BTF_MASK                              0x01
#define IA32_DEBUGCTL_REGISTER_BTF(_)                                (((_) >> 1) & 0x01)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bit 6] Setting this bit to 1 enables branch trace messages to be sent.
     *
     * @remarks 06_0EH
     */
    UINT64 Tr                                                      : 1;
#define IA32_DEBUGCTL_REGISTER_TR_BIT                                6
#define IA32_DEBUGCTL_REGISTER_TR_MASK                               0x01
#define IA32_DEBUGCTL_REGISTER_TR(_)                                 (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Setting this bit enables branch trace messages (BTMs) to be logged in a BTS buffer.
     *
     * @remarks 06_0EH
     */
    UINT64 Bts                                                     : 1;
#define IA32_DEBUGCTL_REGISTER_BTS_BIT                               7
#define IA32_DEBUGCTL_REGISTER_BTS_MASK                              0x01
#define IA32_DEBUGCTL_REGISTER_BTS(_)                                (((_) >> 7) & 0x01)

    /**
     * [Bit 8] When clear, BTMs are logged in a BTS buffer in circular fashion. When this bit is set, an interrupt is generated
     * by the BTS facility when the BTS buffer is full.
     *
     * @remarks 06_0EH
     */
    UINT64 Btint                                                   : 1;
#define IA32_DEBUGCTL_REGISTER_BTINT_BIT                             8
#define IA32_DEBUGCTL_REGISTER_BTINT_MASK                            0x01
#define IA32_DEBUGCTL_REGISTER_BTINT(_)                              (((_) >> 8) & 0x01)

    /**
     * [Bit 9] When set, BTS or BTM is skipped if CPL = 0.
     *
     * @remarks 06_0FH
     */
    UINT64 BtsOffOs                                                : 1;
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_OS_BIT                        9
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_OS_MASK                       0x01
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_OS(_)                         (((_) >> 9) & 0x01)

    /**
     * [Bit 10] When set, BTS or BTM is skipped if CPL > 0.
     *
     * @remarks 06_0FH
     */
    UINT64 BtsOffUsr                                               : 1;
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_USR_BIT                       10
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_USR_MASK                      0x01
#define IA32_DEBUGCTL_REGISTER_BTS_OFF_USR(_)                        (((_) >> 10) & 0x01)

    /**
     * [Bit 11] When set, the LBR stack is frozen on a PMI request.
     *
     * @remarks If CPUID.01H: ECX[15] = 1 && CPUID.0AH: EAX[7:0] > 1
     */
    UINT64 FreezeLbrsOnPmi                                         : 1;
#define IA32_DEBUGCTL_REGISTER_FREEZE_LBRS_ON_PMI_BIT                11
#define IA32_DEBUGCTL_REGISTER_FREEZE_LBRS_ON_PMI_MASK               0x01
#define IA32_DEBUGCTL_REGISTER_FREEZE_LBRS_ON_PMI(_)                 (((_) >> 11) & 0x01)

    /**
     * [Bit 12] When set, each ENABLE bit of the global counter control MSR are frozen (address 38FH) on a PMI request.
     *
     * @remarks If CPUID.01H: ECX[15] = 1 && CPUID.0AH: EAX[7:0] > 1
     */
    UINT64 FreezePerfmonOnPmi                                      : 1;
#define IA32_DEBUGCTL_REGISTER_FREEZE_PERFMON_ON_PMI_BIT             12
#define IA32_DEBUGCTL_REGISTER_FREEZE_PERFMON_ON_PMI_MASK            0x01
#define IA32_DEBUGCTL_REGISTER_FREEZE_PERFMON_ON_PMI(_)              (((_) >> 12) & 0x01)

    /**
     * [Bit 13] When set, enables the logical processor to receive and generate PMI on behalf of the uncore.
     *
     * @remarks 06_1AH
     */
    UINT64 EnableUncorePmi                                         : 1;
#define IA32_DEBUGCTL_REGISTER_ENABLE_UNCORE_PMI_BIT                 13
#define IA32_DEBUGCTL_REGISTER_ENABLE_UNCORE_PMI_MASK                0x01
#define IA32_DEBUGCTL_REGISTER_ENABLE_UNCORE_PMI(_)                  (((_) >> 13) & 0x01)

    /**
     * [Bit 14] When set, freezes perfmon and trace messages while in SMM.
     *
     * @remarks If IA32_PERF_CAPABILITIES[12] = 1
     */
    UINT64 FreezeWhileSmm                                          : 1;
#define IA32_DEBUGCTL_REGISTER_FREEZE_WHILE_SMM_BIT                  14
#define IA32_DEBUGCTL_REGISTER_FREEZE_WHILE_SMM_MASK                 0x01
#define IA32_DEBUGCTL_REGISTER_FREEZE_WHILE_SMM(_)                   (((_) >> 14) & 0x01)

    /**
     * [Bit 15] When set, enables DR7 debug bit on XBEGIN.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[11] = 1)
     */
    UINT64 RtmDebug                                                : 1;
#define IA32_DEBUGCTL_REGISTER_RTM_DEBUG_BIT                         15
#define IA32_DEBUGCTL_REGISTER_RTM_DEBUG_MASK                        0x01
#define IA32_DEBUGCTL_REGISTER_RTM_DEBUG(_)                          (((_) >> 15) & 0x01)
    UINT64 Reserved2                                               : 48;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_DEBUGCTL_REGISTER;

/**
 * @brief SMRR Base Address <b>(Writeable only in SMM)</b>
 *
 * SMRR Base Address. Base address of SMM memory range.
 *
 * @remarks If IA32_MTRRCAP.SMRR[11] = 1
 */
#define IA32_SMRR_PHYSBASE                                           0x000001F2

typedef union
{
  struct
  {
    /**
     * @brief Type
     *
     * [Bits 7:0] Type. Specifies memory type of the range.
     */
    UINT64 Type                                                    : 8;
#define IA32_SMRR_PHYSBASE_REGISTER_TYPE_BIT                         0
#define IA32_SMRR_PHYSBASE_REGISTER_TYPE_MASK                        0xFF
#define IA32_SMRR_PHYSBASE_REGISTER_TYPE(_)                          (((_) >> 0) & 0xFF)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 31:12] SMRR physical Base Address.
     */
    UINT64 SmrrPhysicalBaseAddress                                 : 20;
#define IA32_SMRR_PHYSBASE_REGISTER_SMRR_PHYSICAL_BASE_ADDRESS_BIT   12
#define IA32_SMRR_PHYSBASE_REGISTER_SMRR_PHYSICAL_BASE_ADDRESS_MASK  0xFFFFF
#define IA32_SMRR_PHYSBASE_REGISTER_SMRR_PHYSICAL_BASE_ADDRESS(_)    (((_) >> 12) & 0xFFFFF)
    UINT64 Reserved2                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMRR_PHYSBASE_REGISTER;

/**
 * @brief SMRR Range Mask <b>(Writeable only in SMM)</b>
 *
 * Range Mask of SMM memory range.
 *
 * @remarks If IA32_MTRRCAP[SMRR] = 1
 */
#define IA32_SMRR_PHYSMASK                                           0x000001F3

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 11;

    /**
     * [Bit 11] Enable range mask.
     */
    UINT64 EnableRangeMask                                         : 1;
#define IA32_SMRR_PHYSMASK_REGISTER_ENABLE_RANGE_MASK_BIT            11
#define IA32_SMRR_PHYSMASK_REGISTER_ENABLE_RANGE_MASK_MASK           0x01
#define IA32_SMRR_PHYSMASK_REGISTER_ENABLE_RANGE_MASK(_)             (((_) >> 11) & 0x01)

    /**
     * [Bits 31:12] SMRR address range mask.
     */
    UINT64 SmrrAddressRangeMask                                    : 20;
#define IA32_SMRR_PHYSMASK_REGISTER_SMRR_ADDRESS_RANGE_MASK_BIT      12
#define IA32_SMRR_PHYSMASK_REGISTER_SMRR_ADDRESS_RANGE_MASK_MASK     0xFFFFF
#define IA32_SMRR_PHYSMASK_REGISTER_SMRR_ADDRESS_RANGE_MASK(_)       (((_) >> 12) & 0xFFFFF)
    UINT64 Reserved2                                               : 32;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMRR_PHYSMASK_REGISTER;

/**
 * DCA Capability.
 *
 * @remarks If CPUID.01H: ECX[18] = 1
 */
#define IA32_PLATFORM_DCA_CAP                                        0x000001F8

/**
 * If set, CPU supports Prefetch-Hint type.
 *
 * @remarks If CPUID.01H: ECX[18] = 1
 */
#define IA32_CPU_DCA_CAP                                             0x000001F9

/**
 * DCA type 0 Status and Control register.
 *
 * @remarks If CPUID.01H: ECX[18] = 1
 */
#define IA32_DCA_0_CAP                                               0x000001FA

typedef union
{
  struct
  {
    /**
     * [Bit 0] Set by HW when DCA is fuseenabled and no defeatures are set.
     */
    UINT64 DcaActive                                               : 1;
#define IA32_DCA_0_CAP_REGISTER_DCA_ACTIVE_BIT                       0
#define IA32_DCA_0_CAP_REGISTER_DCA_ACTIVE_MASK                      0x01
#define IA32_DCA_0_CAP_REGISTER_DCA_ACTIVE(_)                        (((_) >> 0) & 0x01)

    /**
     * [Bits 2:1] TRANSACTION.
     */
    UINT64 Transaction                                             : 2;
#define IA32_DCA_0_CAP_REGISTER_TRANSACTION_BIT                      1
#define IA32_DCA_0_CAP_REGISTER_TRANSACTION_MASK                     0x03
#define IA32_DCA_0_CAP_REGISTER_TRANSACTION(_)                       (((_) >> 1) & 0x03)

    /**
     * [Bits 6:3] DCA_TYPE.
     */
    UINT64 DcaType                                                 : 4;
#define IA32_DCA_0_CAP_REGISTER_DCA_TYPE_BIT                         3
#define IA32_DCA_0_CAP_REGISTER_DCA_TYPE_MASK                        0x0F
#define IA32_DCA_0_CAP_REGISTER_DCA_TYPE(_)                          (((_) >> 3) & 0x0F)

    /**
     * [Bits 10:7] DCA_QUEUE_SIZE.
     */
    UINT64 DcaQueueSize                                            : 4;
#define IA32_DCA_0_CAP_REGISTER_DCA_QUEUE_SIZE_BIT                   7
#define IA32_DCA_0_CAP_REGISTER_DCA_QUEUE_SIZE_MASK                  0x0F
#define IA32_DCA_0_CAP_REGISTER_DCA_QUEUE_SIZE(_)                    (((_) >> 7) & 0x0F)
    UINT64 Reserved1                                               : 2;

    /**
     * [Bits 16:13] Writes will update the register but have no HW side-effect.
     */
    UINT64 DcaDelay                                                : 4;
#define IA32_DCA_0_CAP_REGISTER_DCA_DELAY_BIT                        13
#define IA32_DCA_0_CAP_REGISTER_DCA_DELAY_MASK                       0x0F
#define IA32_DCA_0_CAP_REGISTER_DCA_DELAY(_)                         (((_) >> 13) & 0x0F)
    UINT64 Reserved2                                               : 7;

    /**
     * [Bit 24] SW can request DCA block by setting this bit.
     */
    UINT64 SwBlock                                                 : 1;
#define IA32_DCA_0_CAP_REGISTER_SW_BLOCK_BIT                         24
#define IA32_DCA_0_CAP_REGISTER_SW_BLOCK_MASK                        0x01
#define IA32_DCA_0_CAP_REGISTER_SW_BLOCK(_)                          (((_) >> 24) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * [Bit 26] Set when DCA is blocked by HW (e.g. CR0.CD = 1).
     */
    UINT64 HwBlock                                                 : 1;
#define IA32_DCA_0_CAP_REGISTER_HW_BLOCK_BIT                         26
#define IA32_DCA_0_CAP_REGISTER_HW_BLOCK_MASK                        0x01
#define IA32_DCA_0_CAP_REGISTER_HW_BLOCK(_)                          (((_) >> 26) & 0x01)
    UINT64 Reserved4                                               : 37;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_DCA_0_CAP_REGISTER;

/**
 * @defgroup IA32_MTRR_PHYSBASE \
 *           IA32_MTRR_PHYSBASE(n)
 *
 * IA32_MTRR_PHYSBASE(0-9).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.3(Variable Range MTRRs)]
 * @{
 */
#define IA32_MTRR_PHYSBASE0                                          0x00000200
#define IA32_MTRR_PHYSBASE1                                          0x00000202
#define IA32_MTRR_PHYSBASE2                                          0x00000204
#define IA32_MTRR_PHYSBASE3                                          0x00000206
#define IA32_MTRR_PHYSBASE4                                          0x00000208
#define IA32_MTRR_PHYSBASE5                                          0x0000020A
#define IA32_MTRR_PHYSBASE6                                          0x0000020C
#define IA32_MTRR_PHYSBASE7                                          0x0000020E
#define IA32_MTRR_PHYSBASE8                                          0x00000210
#define IA32_MTRR_PHYSBASE9                                          0x00000212
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_PHYSMASK \
 *           IA32_MTRR_PHYSMASK(n)
 *
 * IA32_MTRR_PHYSMASK(0-9).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.3(Variable Range MTRRs)]
 * @{
 */
#define IA32_MTRR_PHYSMASK0                                          0x00000201
#define IA32_MTRR_PHYSMASK1                                          0x00000203
#define IA32_MTRR_PHYSMASK2                                          0x00000205
#define IA32_MTRR_PHYSMASK3                                          0x00000207
#define IA32_MTRR_PHYSMASK4                                          0x00000209
#define IA32_MTRR_PHYSMASK5                                          0x0000020B
#define IA32_MTRR_PHYSMASK6                                          0x0000020D
#define IA32_MTRR_PHYSMASK7                                          0x0000020F
#define IA32_MTRR_PHYSMASK8                                          0x00000211
#define IA32_MTRR_PHYSMASK9                                          0x00000213
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX \
 *           IA32_MTRR_FIX(x)
 *
 * IA32_MTRR_FIX(x).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.2(Fixed Range MTRRs)]
 * @{
 */
/**
 * @defgroup IA32_MTRR_FIX64K \
 *           IA32_MTRR_FIX64K(x)
 *
 * IA32_MTRR_FIX64K(x).
 * @{
 */
#define IA32_MTRR_FIX64K_BASE                                        0x00000000
#define IA32_MTRR_FIX64K_SIZE                                        0x00010000
#define IA32_MTRR_FIX64K_00000                                       0x00000250
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX16K \
 *           IA32_MTRR_FIX16K(x)
 *
 * IA32_MTRR_FIX16K(x).
 * @{
 */
#define IA32_MTRR_FIX16K_BASE                                        0x00080000
#define IA32_MTRR_FIX16K_SIZE                                        0x00004000
#define IA32_MTRR_FIX16K_80000                                       0x00000258
#define IA32_MTRR_FIX16K_A0000                                       0x00000259
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX4K \
 *           IA32_MTRR_FIX4K(x)
 *
 * IA32_MTRR_FIX4K(x).
 * @{
 */
#define IA32_MTRR_FIX4K_BASE                                         0x000C0000
#define IA32_MTRR_FIX4K_SIZE                                         0x00001000
#define IA32_MTRR_FIX4K_C0000                                        0x00000268
#define IA32_MTRR_FIX4K_C8000                                        0x00000269
#define IA32_MTRR_FIX4K_D0000                                        0x0000026A
#define IA32_MTRR_FIX4K_D8000                                        0x0000026B
#define IA32_MTRR_FIX4K_E0000                                        0x0000026C
#define IA32_MTRR_FIX4K_E8000                                        0x0000026D
#define IA32_MTRR_FIX4K_F0000                                        0x0000026E
#define IA32_MTRR_FIX4K_F8000                                        0x0000026F
/**
 * @}
 */

/**
 * Architecture defined number of fixed range MTRRs (1 for 64k, 2 for 16k, 8 for 4k).
 */
#define IA32_MTRR_FIX_COUNT                                          (1 + 2 + 8)

/**
 * Architecture defined number of variable range MTRRs.
 */
#define IA32_MTRR_VARIABLE_COUNT                                     0x000000FF

/**
 * A size of array to store all possible MTRRs.
 */
#define IA32_MTRR_COUNT                                              (IA32_MTRR_FIX_COUNT + IA32_MTRR_VARIABLE_COUNT)

/**
 * @}
 */

/**
 * IA32_PAT.
 *
 * @remarks If CPUID.01H: EDX.MTRR[16] = 1
 */
#define IA32_PAT                                                     0x00000277

typedef union
{
  struct
  {
    /**
     * [Bits 2:0] PA0.
     */
    UINT64 Pa0                                                     : 3;
#define IA32_PAT_REGISTER_PA0_BIT                                    0
#define IA32_PAT_REGISTER_PA0_MASK                                   0x07
#define IA32_PAT_REGISTER_PA0(_)                                     (((_) >> 0) & 0x07)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bits 10:8] PA1.
     */
    UINT64 Pa1                                                     : 3;
#define IA32_PAT_REGISTER_PA1_BIT                                    8
#define IA32_PAT_REGISTER_PA1_MASK                                   0x07
#define IA32_PAT_REGISTER_PA1(_)                                     (((_) >> 8) & 0x07)
    UINT64 Reserved2                                               : 5;

    /**
     * [Bits 18:16] PA2.
     */
    UINT64 Pa2                                                     : 3;
#define IA32_PAT_REGISTER_PA2_BIT                                    16
#define IA32_PAT_REGISTER_PA2_MASK                                   0x07
#define IA32_PAT_REGISTER_PA2(_)                                     (((_) >> 16) & 0x07)
    UINT64 Reserved3                                               : 5;

    /**
     * [Bits 26:24] PA3.
     */
    UINT64 Pa3                                                     : 3;
#define IA32_PAT_REGISTER_PA3_BIT                                    24
#define IA32_PAT_REGISTER_PA3_MASK                                   0x07
#define IA32_PAT_REGISTER_PA3(_)                                     (((_) >> 24) & 0x07)
    UINT64 Reserved4                                               : 5;

    /**
     * [Bits 34:32] PA4.
     */
    UINT64 Pa4                                                     : 3;
#define IA32_PAT_REGISTER_PA4_BIT                                    32
#define IA32_PAT_REGISTER_PA4_MASK                                   0x07
#define IA32_PAT_REGISTER_PA4(_)                                     (((_) >> 32) & 0x07)
    UINT64 Reserved5                                               : 5;

    /**
     * [Bits 42:40] PA5.
     */
    UINT64 Pa5                                                     : 3;
#define IA32_PAT_REGISTER_PA5_BIT                                    40
#define IA32_PAT_REGISTER_PA5_MASK                                   0x07
#define IA32_PAT_REGISTER_PA5(_)                                     (((_) >> 40) & 0x07)
    UINT64 Reserved6                                               : 5;

    /**
     * [Bits 50:48] PA6.
     */
    UINT64 Pa6                                                     : 3;
#define IA32_PAT_REGISTER_PA6_BIT                                    48
#define IA32_PAT_REGISTER_PA6_MASK                                   0x07
#define IA32_PAT_REGISTER_PA6(_)                                     (((_) >> 48) & 0x07)
    UINT64 Reserved7                                               : 5;

    /**
     * [Bits 58:56] PA7.
     */
    UINT64 Pa7                                                     : 3;
#define IA32_PAT_REGISTER_PA7_BIT                                    56
#define IA32_PAT_REGISTER_PA7_MASK                                   0x07
#define IA32_PAT_REGISTER_PA7(_)                                     (((_) >> 56) & 0x07)
    UINT64 Reserved8                                               : 5;
  };

  UINT64 Flags;
} IA32_PAT_REGISTER;

/**
 * @defgroup IA32_MC_CTL2 \
 *           IA32_MC(i)_CTL2
 *
 * MSR to enable/disable CMCI capability for bank n.
 *
 * @remarks If IA32_MCG_CAP[10] = 1 && IA32_MCG_CAP[7:0] > n
 * @see Vol3B[15.3.2.5(IA32_MCi_CTL2 MSRs)]
 * @{
 */
#define IA32_MC0_CTL2                                                0x00000280
#define IA32_MC1_CTL2                                                0x00000281
#define IA32_MC2_CTL2                                                0x00000282
#define IA32_MC3_CTL2                                                0x00000283
#define IA32_MC4_CTL2                                                0x00000284
#define IA32_MC5_CTL2                                                0x00000285
#define IA32_MC6_CTL2                                                0x00000286
#define IA32_MC7_CTL2                                                0x00000287
#define IA32_MC8_CTL2                                                0x00000288
#define IA32_MC9_CTL2                                                0x00000289
#define IA32_MC10_CTL2                                               0x0000028A
#define IA32_MC11_CTL2                                               0x0000028B
#define IA32_MC12_CTL2                                               0x0000028C
#define IA32_MC13_CTL2                                               0x0000028D
#define IA32_MC14_CTL2                                               0x0000028E
#define IA32_MC15_CTL2                                               0x0000028F
#define IA32_MC16_CTL2                                               0x00000290
#define IA32_MC17_CTL2                                               0x00000291
#define IA32_MC18_CTL2                                               0x00000292
#define IA32_MC19_CTL2                                               0x00000293
#define IA32_MC20_CTL2                                               0x00000294
#define IA32_MC21_CTL2                                               0x00000295
#define IA32_MC22_CTL2                                               0x00000296
#define IA32_MC23_CTL2                                               0x00000297
#define IA32_MC24_CTL2                                               0x00000298
#define IA32_MC25_CTL2                                               0x00000299
#define IA32_MC26_CTL2                                               0x0000029A
#define IA32_MC27_CTL2                                               0x0000029B
#define IA32_MC28_CTL2                                               0x0000029C
#define IA32_MC29_CTL2                                               0x0000029D
#define IA32_MC30_CTL2                                               0x0000029E
#define IA32_MC31_CTL2                                               0x0000029F
typedef union
{
  struct
  {
    /**
     * [Bits 14:0] Corrected error count threshold.
     */
    UINT64 CorrectedErrorCountThreshold                            : 15;
#define IA32_MC_CTL2_REGISTER_CORRECTED_ERROR_COUNT_THRESHOLD_BIT    0
#define IA32_MC_CTL2_REGISTER_CORRECTED_ERROR_COUNT_THRESHOLD_MASK   0x7FFF
#define IA32_MC_CTL2_REGISTER_CORRECTED_ERROR_COUNT_THRESHOLD(_)     (((_) >> 0) & 0x7FFF)
    UINT64 Reserved1                                               : 15;

    /**
     * [Bit 30] CMCI_EN.
     */
    UINT64 CmciEn                                                  : 1;
#define IA32_MC_CTL2_REGISTER_CMCI_EN_BIT                            30
#define IA32_MC_CTL2_REGISTER_CMCI_EN_MASK                           0x01
#define IA32_MC_CTL2_REGISTER_CMCI_EN(_)                             (((_) >> 30) & 0x01)
    UINT64 Reserved2                                               : 33;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MC_CTL2_REGISTER;

/**
 * @}
 */

/**
 * IA32_MTRR_DEF_TYPE.
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 */
#define IA32_MTRR_DEF_TYPE                                           0x000002FF

typedef union
{
  struct
  {
    /**
     * [Bits 2:0] Default Memory Type.
     */
    UINT64 DefaultMemoryType                                       : 3;
#define IA32_MTRR_DEF_TYPE_REGISTER_DEFAULT_MEMORY_TYPE_BIT          0
#define IA32_MTRR_DEF_TYPE_REGISTER_DEFAULT_MEMORY_TYPE_MASK         0x07
#define IA32_MTRR_DEF_TYPE_REGISTER_DEFAULT_MEMORY_TYPE(_)           (((_) >> 0) & 0x07)
    UINT64 Reserved1                                               : 7;

    /**
     * [Bit 10] Fixed Range MTRR Enable.
     */
    UINT64 FixedRangeMtrrEnable                                    : 1;
#define IA32_MTRR_DEF_TYPE_REGISTER_FIXED_RANGE_MTRR_ENABLE_BIT      10
#define IA32_MTRR_DEF_TYPE_REGISTER_FIXED_RANGE_MTRR_ENABLE_MASK     0x01
#define IA32_MTRR_DEF_TYPE_REGISTER_FIXED_RANGE_MTRR_ENABLE(_)       (((_) >> 10) & 0x01)

    /**
     * [Bit 11] MTRR Enable.
     */
    UINT64 MtrrEnable                                              : 1;
#define IA32_MTRR_DEF_TYPE_REGISTER_MTRR_ENABLE_BIT                  11
#define IA32_MTRR_DEF_TYPE_REGISTER_MTRR_ENABLE_MASK                 0x01
#define IA32_MTRR_DEF_TYPE_REGISTER_MTRR_ENABLE(_)                   (((_) >> 11) & 0x01)
    UINT64 Reserved2                                               : 52;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MTRR_DEF_TYPE_REGISTER;

/**
 * @defgroup IA32_FIXED_CTR \
 *           IA32_FIXED_CTR(n)
 *
 * Fixed-Function Performance Counter n.
 *
 * @remarks If CPUID.0AH: EDX[4:0] > n
 * @{
 */
/**
 * Counts Instr_Retired.Any.
 */
#define IA32_FIXED_CTR0                                              0x00000309

/**
 * Counts CPU_CLK_Unhalted.Core
 */
#define IA32_FIXED_CTR1                                              0x0000030A

/**
 * Counts CPU_CLK_Unhalted.Ref
 */
#define IA32_FIXED_CTR2                                              0x0000030B

/**
 * @}
 */

/**
 * Read Only MSR that enumerates the existence of performance monitoring features.
 *
 * @remarks If CPUID.01H: ECX[15] = 1
 */
#define IA32_PERF_CAPABILITIES                                       0x00000345

typedef union
{
  struct
  {
    /**
     * [Bits 5:0] LBR format.
     */
    UINT64 LbrFormat                                               : 6;
#define IA32_PERF_CAPABILITIES_REGISTER_LBR_FORMAT_BIT               0
#define IA32_PERF_CAPABILITIES_REGISTER_LBR_FORMAT_MASK              0x3F
#define IA32_PERF_CAPABILITIES_REGISTER_LBR_FORMAT(_)                (((_) >> 0) & 0x3F)

    /**
     * [Bit 6] PEBS Trap.
     */
    UINT64 PebsTrap                                                : 1;
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_TRAP_BIT                6
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_TRAP_MASK               0x01
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_TRAP(_)                 (((_) >> 6) & 0x01)

    /**
     * [Bit 7] PEBSSaveArchRegs.
     */
    UINT64 PebsSaveArchRegs                                        : 1;
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_SAVE_ARCH_REGS_BIT      7
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_SAVE_ARCH_REGS_MASK     0x01
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_SAVE_ARCH_REGS(_)       (((_) >> 7) & 0x01)

    /**
     * [Bits 11:8] PEBS Record Format.
     */
    UINT64 PebsRecordFormat                                        : 4;
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_RECORD_FORMAT_BIT       8
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_RECORD_FORMAT_MASK      0x0F
#define IA32_PERF_CAPABILITIES_REGISTER_PEBS_RECORD_FORMAT(_)        (((_) >> 8) & 0x0F)

    /**
     * [Bit 12] Freeze while SMM is supported.
     */
    UINT64 FreezeWhileSmmIsSupported                               : 1;
#define IA32_PERF_CAPABILITIES_REGISTER_FREEZE_WHILE_SMM_IS_SUPPORTED_BIT 12
#define IA32_PERF_CAPABILITIES_REGISTER_FREEZE_WHILE_SMM_IS_SUPPORTED_MASK 0x01
#define IA32_PERF_CAPABILITIES_REGISTER_FREEZE_WHILE_SMM_IS_SUPPORTED(_) (((_) >> 12) & 0x01)

    /**
     * [Bit 13] Full width of counter writable via IA32_A_PMCx.
     */
    UINT64 FullWidthCounterWrite                                   : 1;
#define IA32_PERF_CAPABILITIES_REGISTER_FULL_WIDTH_COUNTER_WRITE_BIT 13
#define IA32_PERF_CAPABILITIES_REGISTER_FULL_WIDTH_COUNTER_WRITE_MASK 0x01
#define IA32_PERF_CAPABILITIES_REGISTER_FULL_WIDTH_COUNTER_WRITE(_)  (((_) >> 13) & 0x01)
    UINT64 Reserved1                                               : 50;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERF_CAPABILITIES_REGISTER;

/**
 * @brief Fixed-Function Performance Counter Control <b>(R/W)</b>
 *
 * Fixed-Function Performance Counter Control. Counter increments while the results of ANDing respective enable bit in
 * IA32_PERF_GLOBAL_CTRL with the corresponding OS or USR bits in this MSR is true.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 1
 */
#define IA32_FIXED_CTR_CTRL                                          0x0000038D

typedef union
{
  struct
  {
    /**
     * [Bit 0] EN0_OS: Enable Fixed Counter 0 to count while CPL = 0.
     */
    UINT64 En0Os                                                   : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_OS_BIT                      0
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_OS_MASK                     0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_OS(_)                       (((_) >> 0) & 0x01)

    /**
     * [Bit 1] EN0_Usr: Enable Fixed Counter 0 to count while CPL > 0.
     */
    UINT64 En0Usr                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_USR_BIT                     1
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_USR_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_USR(_)                      (((_) >> 1) & 0x01)

    /**
     * [Bit 2] AnyThread: When set to 1, it enables counting the associated event conditions occurring across all logical
     * processors sharing a processor core. When set to 0, the counter only increments the associated event conditions
     * occurring in the logical processor which programmed the MSR.
     */
    UINT64 AnyThread0                                              : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD0_BIT                 2
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD0_MASK                0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD0(_)                  (((_) >> 2) & 0x01)

    /**
     * [Bit 3] EN0_PMI: Enable PMI when fixed counter 0 overflows.
     */
    UINT64 En0Pmi                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_PMI_BIT                     3
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_PMI_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN0_PMI(_)                      (((_) >> 3) & 0x01)

    /**
     * [Bit 4] EN1_OS: Enable Fixed Counter 1 to count while CPL = 0.
     */
    UINT64 En1Os                                                   : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_OS_BIT                      4
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_OS_MASK                     0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_OS(_)                       (((_) >> 4) & 0x01)

    /**
     * [Bit 5] EN1_Usr: Enable Fixed Counter 1 to count while CPL > 0.
     */
    UINT64 En1Usr                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_USR_BIT                     5
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_USR_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_USR(_)                      (((_) >> 5) & 0x01)

    /**
     * [Bit 6] AnyThread: When set to 1, it enables counting the associated event conditions occurring across all logical
     * processors sharing a processor core. When set to 0, the counter only increments the associated event conditions
     * occurring in the logical processor which programmed the MSR.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 2
     */
    UINT64 AnyThread1                                              : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD1_BIT                 6
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD1_MASK                0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD1(_)                  (((_) >> 6) & 0x01)

    /**
     * [Bit 7] EN1_PMI: Enable PMI when fixed counter 1 overflows.
     */
    UINT64 En1Pmi                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_PMI_BIT                     7
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_PMI_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN1_PMI(_)                      (((_) >> 7) & 0x01)

    /**
     * [Bit 8] EN2_OS: Enable Fixed Counter 2 to count while CPL = 0.
     */
    UINT64 En2Os                                                   : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_OS_BIT                      8
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_OS_MASK                     0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_OS(_)                       (((_) >> 8) & 0x01)

    /**
     * [Bit 9] EN2_Usr: Enable Fixed Counter 2 to count while CPL > 0.
     */
    UINT64 En2Usr                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_USR_BIT                     9
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_USR_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_USR(_)                      (((_) >> 9) & 0x01)

    /**
     * [Bit 10] AnyThread: When set to 1, it enables counting the associated event conditions occurring across all logical
     * processors sharing a processor core. When set to 0, the counter only increments the associated event conditions
     * occurring in the logical processor which programmed the MSR.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 2
     */
    UINT64 AnyThread2                                              : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD2_BIT                 10
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD2_MASK                0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_ANY_THREAD2(_)                  (((_) >> 10) & 0x01)

    /**
     * [Bit 11] EN2_PMI: Enable PMI when fixed counter 2 overflows.
     */
    UINT64 En2Pmi                                                  : 1;
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_PMI_BIT                     11
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_PMI_MASK                    0x01
#define IA32_FIXED_CTR_CTRL_REGISTER_EN2_PMI(_)                      (((_) >> 11) & 0x01)
    UINT64 Reserved1                                               : 52;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_FIXED_CTR_CTRL_REGISTER;

/**
 * Global Performance Counter Status.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 0
 */
#define IA32_PERF_GLOBAL_STATUS                                      0x0000038E

typedef union
{
  struct
  {
    /**
     * [Bit 0] Ovf_PMC0: Overflow status of IA32_PMC0.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > 0
     */
    UINT64 OvfPmc0                                                 : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC0_BIT                0
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC0_MASK               0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC0(_)                 (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Ovf_PMC1: Overflow status of IA32_PMC1.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > 1
     */
    UINT64 OvfPmc1                                                 : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC1_BIT                1
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC1_MASK               0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC1(_)                 (((_) >> 1) & 0x01)

    /**
     * [Bit 2] Ovf_PMC2: Overflow status of IA32_PMC2.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > 2
     */
    UINT64 OvfPmc2                                                 : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC2_BIT                2
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC2_MASK               0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC2(_)                 (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Ovf_PMC3: Overflow status of IA32_PMC3.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > 3
     */
    UINT64 OvfPmc3                                                 : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC3_BIT                3
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC3_MASK               0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_PMC3(_)                 (((_) >> 3) & 0x01)
    UINT64 Reserved1                                               : 28;

    /**
     * [Bit 32] Ovf_FixedCtr0: Overflow status of IA32_FIXED_CTR0.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 1
     */
    UINT64 OvfFixedctr0                                            : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR0_BIT           32
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR0_MASK          0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR0(_)            (((_) >> 32) & 0x01)

    /**
     * [Bit 33] Ovf_FixedCtr1: Overflow status of IA32_FIXED_CTR1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 1
     */
    UINT64 OvfFixedctr1                                            : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR1_BIT           33
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR1_MASK          0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR1(_)            (((_) >> 33) & 0x01)

    /**
     * [Bit 34] Ovf_FixedCtr2: Overflow status of IA32_FIXED_CTR2.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 1
     */
    UINT64 OvfFixedctr2                                            : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR2_BIT           34
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR2_MASK          0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_FIXEDCTR2(_)            (((_) >> 34) & 0x01)
    UINT64 Reserved2                                               : 20;

    /**
     * [Bit 55] Trace_ToPA_PMI: A PMI occurred due to a ToPA entry memory buffer that was completely filled.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[25] = 1) && IA32_RTIT_CTL.ToPA = 1
     */
    UINT64 TraceTopaPmi                                            : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_TRACE_TOPA_PMI_BIT          55
#define IA32_PERF_GLOBAL_STATUS_REGISTER_TRACE_TOPA_PMI_MASK         0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_TRACE_TOPA_PMI(_)           (((_) >> 55) & 0x01)
    UINT64 Reserved3                                               : 2;

    /**
     * [Bit 58] LBR_Frz. LBRs are frozen due to:
     * * IA32_DEBUGCTL.FREEZE_LBR_ON_PMI=1.
     * * The LBR stack overflowed.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 LbrFrz                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_LBR_FRZ_BIT                 58
#define IA32_PERF_GLOBAL_STATUS_REGISTER_LBR_FRZ_MASK                0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_LBR_FRZ(_)                  (((_) >> 58) & 0x01)

    /**
     * [Bit 59] CTR_Frz. Performance counters in the core PMU are frozen due to:
     * * IA32_DEBUGCTL.FREEZE_PERFMON_ON_PMI=1.
     * * One or more core PMU counters overflowed.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 CtrFrz                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_CTR_FRZ_BIT                 59
#define IA32_PERF_GLOBAL_STATUS_REGISTER_CTR_FRZ_MASK                0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_CTR_FRZ(_)                  (((_) >> 59) & 0x01)

    /**
     * [Bit 60] ASCI: Data in the performance counters in the core PMU may include contributions from the direct or indirect
     * operation Intel SGX to protect an enclave.
     *
     * @remarks If CPUID.(EAX=07H, ECX=0):EBX[2] = 1
     */
    UINT64 Asci                                                    : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_ASCI_BIT                    60
#define IA32_PERF_GLOBAL_STATUS_REGISTER_ASCI_MASK                   0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_ASCI(_)                     (((_) >> 60) & 0x01)

    /**
     * [Bit 61] Uncore counter overflow status.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 2
     */
    UINT64 OvfUncore                                               : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_UNCORE_BIT              61
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_UNCORE_MASK             0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_UNCORE(_)               (((_) >> 61) & 0x01)

    /**
     * [Bit 62] OvfBuf: DS SAVE area Buffer overflow status.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 0
     */
    UINT64 OvfBuf                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_BUF_BIT                 62
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_BUF_MASK                0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_OVF_BUF(_)                  (((_) >> 62) & 0x01)

    /**
     * [Bit 63] CondChgd: Status bits of this register have changed.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 0
     */
    UINT64 CondChgd                                                : 1;
#define IA32_PERF_GLOBAL_STATUS_REGISTER_COND_CHGD_BIT               63
#define IA32_PERF_GLOBAL_STATUS_REGISTER_COND_CHGD_MASK              0x01
#define IA32_PERF_GLOBAL_STATUS_REGISTER_COND_CHGD(_)                (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_REGISTER;

/**
 * @brief Global Performance Counter Control <b>(R/W)</b>
 *
 * Global Performance Counter Control. Counter increments while the result of ANDing the respective enable bit in this MSR
 * with the corresponding OS or USR bits in the general-purpose or fixed counter control MSR is true.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 0
 */
#define IA32_PERF_GLOBAL_CTRL                                        0x0000038F

typedef struct
{
  UINT32 EnPmcn;
  UINT32 EnFixedCtrn;
} IA32_PERF_GLOBAL_CTRL_REGISTER;

/**
 * Global Performance Counter Overflow Reset Control.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 3
 */
#define IA32_PERF_GLOBAL_STATUS_RESET                                0x00000390

typedef union
{
  struct
  {
    /**
     * [Bits 31:0] Set 1 to clear Ovf_PMC(n) bit. Clear bitmask. Only the first n-1 bits are valid. Bits 31:n are reserved.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > n
     */
    UINT64 ClearOvfPmcn                                            : 32;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_PMCN_BIT    0
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_PMCN_MASK   0xFFFFFFFF
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_PMCN(_)     (((_) >> 0) & 0xFFFFFFFF)

    /**
     * [Bits 34:32] Set 1 to clear Ovf_FIXED_CTR(n) bit. Clear bitmask. Only the first n-1 bits are valid. Bits 31:n are
     * reserved.
     *
     * @remarks If CPUID.0AH: EDX[4:0] > n
     */
    UINT64 ClearOvfFixedCtrn                                       : 3;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_FIXED_CTRN_BIT 32
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_FIXED_CTRN_MASK 0x07
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_FIXED_CTRN(_) (((_) >> 32) & 0x07)
    UINT64 Reserved1                                               : 20;

    /**
     * [Bit 55] Set 1 to clear Trace_ToPA_PMI bit.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[25] = 1) && IA32_RTIT_CTL.ToPA = 1
     */
    UINT64 ClearTraceTopaPmi                                       : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_TRACE_TOPA_PMI_BIT 55
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_TRACE_TOPA_PMI_MASK 0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_TRACE_TOPA_PMI(_) (((_) >> 55) & 0x01)
    UINT64 Reserved2                                               : 2;

    /**
     * [Bit 58] Set 1 to clear LBR_Frz bit.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 ClearLbrFrz                                             : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_LBR_FRZ_BIT     58
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_LBR_FRZ_MASK    0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_LBR_FRZ(_)      (((_) >> 58) & 0x01)

    /**
     * [Bit 59] Set 1 to clear CTR_Frz bit.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 ClearCtrFrz                                             : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_CTR_FRZ_BIT     59
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_CTR_FRZ_MASK    0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_CTR_FRZ(_)      (((_) >> 59) & 0x01)

    /**
     * [Bit 60] Set 1 to clear ASCI bit.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 ClearAsci                                               : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_ASCI_BIT        60
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_ASCI_MASK       0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_ASCI(_)         (((_) >> 60) & 0x01)

    /**
     * [Bit 61] Set 1 to clear Ovf_Uncore bit.
     *
     * @remarks 06_2EH
     */
    UINT64 ClearOvfUncore                                          : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_UNCORE_BIT  61
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_UNCORE_MASK 0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_UNCORE(_)   (((_) >> 61) & 0x01)

    /**
     * [Bit 62] Set 1 to clear OvfBuf bit.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 0
     */
    UINT64 ClearOvfBuf                                             : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_BUF_BIT     62
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_BUF_MASK    0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_OVF_BUF(_)      (((_) >> 62) & 0x01)

    /**
     * [Bit 63] Set 1 to clear CondChgd bit.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 0
     */
    UINT64 ClearCondChgd                                           : 1;
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_COND_CHGD_BIT   63
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_COND_CHGD_MASK  0x01
#define IA32_PERF_GLOBAL_STATUS_RESET_REGISTER_CLEAR_COND_CHGD(_)    (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_RESET_REGISTER;

/**
 * Global Performance Counter Overflow Set Control.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 3
 */
#define IA32_PERF_GLOBAL_STATUS_SET                                  0x00000391

typedef union
{
  struct
  {
    /**
     * [Bits 31:0] Set 1 to cause Ovf_PMC(n) = 1. Set bitmask. Only the first n-1 bits are valid. Bits 31:n are reserved.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > n
     */
    UINT64 OvfPmcn                                                 : 32;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_PMCN_BIT            0
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_PMCN_MASK           0xFFFFFFFF
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_PMCN(_)             (((_) >> 0) & 0xFFFFFFFF)

    /**
     * [Bits 34:32] Set 1 to cause Ovf_FIXED_CTR(n) = 1. Set bitmask. Only the first n-1 bits are valid. Bits 31:n are
     * reserved.
     *
     * @remarks If CPUID.0AH: EDX[4:0] > n
     */
    UINT64 OvfFixedCtrn                                            : 3;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_FIXED_CTRN_BIT      32
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_FIXED_CTRN_MASK     0x07
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_FIXED_CTRN(_)       (((_) >> 32) & 0x07)
    UINT64 Reserved1                                               : 20;

    /**
     * [Bit 55] Set 1 to cause Trace_ToPA_PMI = 1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 TraceTopaPmi                                            : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_TRACE_TOPA_PMI_BIT      55
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_TRACE_TOPA_PMI_MASK     0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_TRACE_TOPA_PMI(_)       (((_) >> 55) & 0x01)
    UINT64 Reserved2                                               : 2;

    /**
     * [Bit 58] Set 1 to cause LBR_Frz = 1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 LbrFrz                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_LBR_FRZ_BIT             58
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_LBR_FRZ_MASK            0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_LBR_FRZ(_)              (((_) >> 58) & 0x01)

    /**
     * [Bit 59] Set 1 to cause CTR_Frz = 1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 CtrFrz                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_CTR_FRZ_BIT             59
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_CTR_FRZ_MASK            0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_CTR_FRZ(_)              (((_) >> 59) & 0x01)

    /**
     * [Bit 60] Set 1 to cause ASCI = 1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 Asci                                                    : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_ASCI_BIT                60
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_ASCI_MASK               0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_ASCI(_)                 (((_) >> 60) & 0x01)

    /**
     * [Bit 61] Set 1 to cause Ovf_Uncore = 1.
     *
     * @remarks 06_2EH
     */
    UINT64 OvfUncore                                               : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_UNCORE_BIT          61
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_UNCORE_MASK         0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_UNCORE(_)           (((_) >> 61) & 0x01)

    /**
     * [Bit 62] Set 1 to cause OvfBuf = 1.
     *
     * @remarks If CPUID.0AH: EAX[7:0] > 3
     */
    UINT64 OvfBuf                                                  : 1;
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_BUF_BIT             62
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_BUF_MASK            0x01
#define IA32_PERF_GLOBAL_STATUS_SET_REGISTER_OVF_BUF(_)              (((_) >> 62) & 0x01)
    UINT64 Reserved3                                               : 1;
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_SET_REGISTER;

/**
 * Indicator that core perfmon interface is in use.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 3
 */
#define IA32_PERF_GLOBAL_INUSE                                       0x00000392

typedef union
{
  struct
  {
    /**
     * [Bits 31:0] IA32_PERFEVTSEL(n) in use. Status bitmask. Only the first n-1 bits are valid. Bits 31:n are reserved.
     *
     * @remarks If CPUID.0AH: EAX[15:8] > n
     */
    UINT64 Ia32PerfevtselnInUse                                    : 32;
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_PERFEVTSELN_IN_USE_BIT  0
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_PERFEVTSELN_IN_USE_MASK 0xFFFFFFFF
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_PERFEVTSELN_IN_USE(_)   (((_) >> 0) & 0xFFFFFFFF)

    /**
     * [Bits 34:32] IA32_FIXED_CTR(n) in use. Status bitmask. Only the first n-1 bits are valid. Bits 31:n are reserved.
     */
    UINT64 Ia32FixedCtrnInUse                                      : 3;
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_FIXED_CTRN_IN_USE_BIT   32
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_FIXED_CTRN_IN_USE_MASK  0x07
#define IA32_PERF_GLOBAL_INUSE_REGISTER_IA32_FIXED_CTRN_IN_USE(_)    (((_) >> 32) & 0x07)
    UINT64 Reserved1                                               : 28;

    /**
     * [Bit 63] PMI in use.
     */
    UINT64 PmiInUse                                                : 1;
#define IA32_PERF_GLOBAL_INUSE_REGISTER_PMI_IN_USE_BIT               63
#define IA32_PERF_GLOBAL_INUSE_REGISTER_PMI_IN_USE_MASK              0x01
#define IA32_PERF_GLOBAL_INUSE_REGISTER_PMI_IN_USE(_)                (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_INUSE_REGISTER;

/**
 * PEBS Control.
 *
 * @remarks If CPUID.0AH: EAX[7:0] > 3
 */
#define IA32_PEBS_ENABLE                                             0x000003F1

typedef union
{
  struct
  {
    /**
     * [Bit 0] Enable PEBS on IA32_PMC0.
     *
     * @remarks 06_0FH
     */
    UINT64 EnablePebs                                              : 1;
#define IA32_PEBS_ENABLE_REGISTER_ENABLE_PEBS_BIT                    0
#define IA32_PEBS_ENABLE_REGISTER_ENABLE_PEBS_MASK                   0x01
#define IA32_PEBS_ENABLE_REGISTER_ENABLE_PEBS(_)                     (((_) >> 0) & 0x01)

    /**
     * [Bits 3:1] Reserved or model specific.
     */
    UINT64 Reservedormodelspecific1                                : 3;
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC1_BIT       1
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC1_MASK      0x07
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC1(_)        (((_) >> 1) & 0x07)
    UINT64 Reserved1                                               : 28;

    /**
     * [Bits 35:32] Reserved or model specific.
     */
    UINT64 Reservedormodelspecific2                                : 4;
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC2_BIT       32
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC2_MASK      0x0F
#define IA32_PEBS_ENABLE_REGISTER_RESERVEDORMODELSPECIFIC2(_)        (((_) >> 32) & 0x0F)
    UINT64 Reserved2                                               : 28;
  };

  UINT64 Flags;
} IA32_PEBS_ENABLE_REGISTER;

/**
 * @defgroup IA32_MC_CTL \
 *           IA32_MC(i)_CTL
 *
 * IA32_MC(0-28)_CTL.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_CTL                                                 0x00000400
#define IA32_MC1_CTL                                                 0x00000404
#define IA32_MC2_CTL                                                 0x00000408
#define IA32_MC3_CTL                                                 0x0000040C
#define IA32_MC4_CTL                                                 0x00000410
#define IA32_MC5_CTL                                                 0x00000414
#define IA32_MC6_CTL                                                 0x00000418
#define IA32_MC7_CTL                                                 0x0000041C
#define IA32_MC8_CTL                                                 0x00000420
#define IA32_MC9_CTL                                                 0x00000424
#define IA32_MC10_CTL                                                0x00000428
#define IA32_MC11_CTL                                                0x0000042C
#define IA32_MC12_CTL                                                0x00000430
#define IA32_MC13_CTL                                                0x00000434
#define IA32_MC14_CTL                                                0x00000438
#define IA32_MC15_CTL                                                0x0000043C
#define IA32_MC16_CTL                                                0x00000440
#define IA32_MC17_CTL                                                0x00000444
#define IA32_MC18_CTL                                                0x00000448
#define IA32_MC19_CTL                                                0x0000044C
#define IA32_MC20_CTL                                                0x00000450
#define IA32_MC21_CTL                                                0x00000454
#define IA32_MC22_CTL                                                0x00000458
#define IA32_MC23_CTL                                                0x0000045C
#define IA32_MC24_CTL                                                0x00000460
#define IA32_MC25_CTL                                                0x00000464
#define IA32_MC26_CTL                                                0x00000468
#define IA32_MC27_CTL                                                0x0000046C
#define IA32_MC28_CTL                                                0x00000470
/**
 * @}
 */

/**
 * @defgroup IA32_MC_STATUS \
 *           IA32_MC(i)_STATUS
 *
 * IA32_MC(0-28)_STATUS.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_STATUS                                              0x00000401
#define IA32_MC1_STATUS                                              0x00000405
#define IA32_MC2_STATUS                                              0x00000409
#define IA32_MC3_STATUS                                              0x0000040D
#define IA32_MC4_STATUS                                              0x00000411
#define IA32_MC5_STATUS                                              0x00000415
#define IA32_MC6_STATUS                                              0x00000419
#define IA32_MC7_STATUS                                              0x0000041D
#define IA32_MC8_STATUS                                              0x00000421
#define IA32_MC9_STATUS                                              0x00000425
#define IA32_MC10_STATUS                                             0x00000429
#define IA32_MC11_STATUS                                             0x0000042D
#define IA32_MC12_STATUS                                             0x00000431
#define IA32_MC13_STATUS                                             0x00000435
#define IA32_MC14_STATUS                                             0x00000439
#define IA32_MC15_STATUS                                             0x0000043D
#define IA32_MC16_STATUS                                             0x00000441
#define IA32_MC17_STATUS                                             0x00000445
#define IA32_MC18_STATUS                                             0x00000449
#define IA32_MC19_STATUS                                             0x0000044D
#define IA32_MC20_STATUS                                             0x00000451
#define IA32_MC21_STATUS                                             0x00000455
#define IA32_MC22_STATUS                                             0x00000459
#define IA32_MC23_STATUS                                             0x0000045D
#define IA32_MC24_STATUS                                             0x00000461
#define IA32_MC25_STATUS                                             0x00000465
#define IA32_MC26_STATUS                                             0x00000469
#define IA32_MC27_STATUS                                             0x0000046D
#define IA32_MC28_STATUS                                             0x00000471
/**
 * @}
 */

/**
 * @defgroup IA32_MC_ADDR \
 *           IA32_MC(i)_ADDR
 *
 * IA32_MC(0-28)_ADDR.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_ADDR                                                0x00000402
#define IA32_MC1_ADDR                                                0x00000406
#define IA32_MC2_ADDR                                                0x0000040A
#define IA32_MC3_ADDR                                                0x0000040E
#define IA32_MC4_ADDR                                                0x00000412
#define IA32_MC5_ADDR                                                0x00000416
#define IA32_MC6_ADDR                                                0x0000041A
#define IA32_MC7_ADDR                                                0x0000041E
#define IA32_MC8_ADDR                                                0x00000422
#define IA32_MC9_ADDR                                                0x00000426
#define IA32_MC10_ADDR                                               0x0000042A
#define IA32_MC11_ADDR                                               0x0000042E
#define IA32_MC12_ADDR                                               0x00000432
#define IA32_MC13_ADDR                                               0x00000436
#define IA32_MC14_ADDR                                               0x0000043A
#define IA32_MC15_ADDR                                               0x0000043E
#define IA32_MC16_ADDR                                               0x00000442
#define IA32_MC17_ADDR                                               0x00000446
#define IA32_MC18_ADDR                                               0x0000044A
#define IA32_MC19_ADDR                                               0x0000044E
#define IA32_MC20_ADDR                                               0x00000452
#define IA32_MC21_ADDR                                               0x00000456
#define IA32_MC22_ADDR                                               0x0000045A
#define IA32_MC23_ADDR                                               0x0000045E
#define IA32_MC24_ADDR                                               0x00000462
#define IA32_MC25_ADDR                                               0x00000466
#define IA32_MC26_ADDR                                               0x0000046A
#define IA32_MC27_ADDR                                               0x0000046E
#define IA32_MC28_ADDR                                               0x00000472
/**
 * @}
 */

/**
 * @defgroup IA32_MC_MISC \
 *           IA32_MC(i)_MISC
 *
 * IA32_MC(0-28)_MISC.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_MISC                                                0x00000403
#define IA32_MC1_MISC                                                0x00000407
#define IA32_MC2_MISC                                                0x0000040B
#define IA32_MC3_MISC                                                0x0000040F
#define IA32_MC4_MISC                                                0x00000413
#define IA32_MC5_MISC                                                0x00000417
#define IA32_MC6_MISC                                                0x0000041B
#define IA32_MC7_MISC                                                0x0000041F
#define IA32_MC8_MISC                                                0x00000423
#define IA32_MC9_MISC                                                0x00000427
#define IA32_MC10_MISC                                               0x0000042B
#define IA32_MC11_MISC                                               0x0000042F
#define IA32_MC12_MISC                                               0x00000433
#define IA32_MC13_MISC                                               0x00000437
#define IA32_MC14_MISC                                               0x0000043B
#define IA32_MC15_MISC                                               0x0000043F
#define IA32_MC16_MISC                                               0x00000443
#define IA32_MC17_MISC                                               0x00000447
#define IA32_MC18_MISC                                               0x0000044B
#define IA32_MC19_MISC                                               0x0000044F
#define IA32_MC20_MISC                                               0x00000453
#define IA32_MC21_MISC                                               0x00000457
#define IA32_MC22_MISC                                               0x0000045B
#define IA32_MC23_MISC                                               0x0000045F
#define IA32_MC24_MISC                                               0x00000463
#define IA32_MC25_MISC                                               0x00000467
#define IA32_MC26_MISC                                               0x0000046B
#define IA32_MC27_MISC                                               0x0000046F
#define IA32_MC28_MISC                                               0x00000473
/**
 * @}
 */

/**
 * Reporting Register of Basic VMX Capabilities.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.1(BASIC VMX INFORMATION)]
 * @see Vol3D[A.1(Basic VMX Information)] (reference)
 */
#define IA32_VMX_BASIC                                               0x00000480

typedef union
{
  struct
  {
    /**
     * @brief VMCS revision identifier used by the processor
     *
     * [Bits 30:0] 31-bit VMCS revision identifier used by the processor. Processors that use the same VMCS revision identifier
     * use the same size for VMCS regions.
     */
    UINT64 VmcsRevisionId                                          : 31;
#define IA32_VMX_BASIC_REGISTER_VMCS_REVISION_ID_BIT                 0
#define IA32_VMX_BASIC_REGISTER_VMCS_REVISION_ID_MASK                0x7FFFFFFF
#define IA32_VMX_BASIC_REGISTER_VMCS_REVISION_ID(_)                  (((_) >> 0) & 0x7FFFFFFF)

    /**
     * [Bit 31] Bit 31 is always 0.
     */
    UINT64 MustBeZero                                              : 1;
#define IA32_VMX_BASIC_REGISTER_MUST_BE_ZERO_BIT                     31
#define IA32_VMX_BASIC_REGISTER_MUST_BE_ZERO_MASK                    0x01
#define IA32_VMX_BASIC_REGISTER_MUST_BE_ZERO(_)                      (((_) >> 31) & 0x01)

    /**
     * @brief Size of the VMCS
     *
     * [Bits 44:32] Report the number of bytes that software should allocate for the VMXON region and any VMCS region. It is a
     * value greater than 0 and at most 4096 (bit 44 is set if and only if bits 43:32 are clear).
     */
    UINT64 VmcsSizeInBytes                                         : 13;
#define IA32_VMX_BASIC_REGISTER_VMCS_SIZE_IN_BYTES_BIT               32
#define IA32_VMX_BASIC_REGISTER_VMCS_SIZE_IN_BYTES_MASK              0x1FFF
#define IA32_VMX_BASIC_REGISTER_VMCS_SIZE_IN_BYTES(_)                (((_) >> 32) & 0x1FFF)
    UINT64 Reserved1                                               : 3;

    /**
     * @brief Width of physical address used for the VMCS
     *        - 0 -> limited to the available amount of physical RAM
     *        - 1 -> within the first 4 GB
     *
     * [Bit 48] Indicates the width of the physical addresses that may be used for the VMXON region, each VMCS, and data
     * structures referenced by pointers in a VMCS (I/O bitmaps, virtual-APIC page, MSR areas for VMX transitions). If the bit
     * is 0, these addresses are limited to the processor's physical-address width.2 If the bit is 1, these addresses are
     * limited to 32 bits. This bit is always 0 for processors that support Intel 64 architecture.
     */
    UINT64 VmcsPhysicalAddressWidth                                : 1;
#define IA32_VMX_BASIC_REGISTER_VMCS_PHYSICAL_ADDRESS_WIDTH_BIT      48
#define IA32_VMX_BASIC_REGISTER_VMCS_PHYSICAL_ADDRESS_WIDTH_MASK     0x01
#define IA32_VMX_BASIC_REGISTER_VMCS_PHYSICAL_ADDRESS_WIDTH(_)       (((_) >> 48) & 0x01)

    /**
     * @brief Whether the processor supports the dual-monitor treatment of system-management interrupts and system-management
     *        code (always 1)
     *
     * [Bit 49] Read as 1, the logical processor supports the dual-monitor treatment of system-management interrupts and
     * system-management mode.
     *
     * @see Vol3C[34.15(DUAL-MONITOR TREATMENT OF SMIs AND SMM)]
     */
    UINT64 DualMonitorSupport                                      : 1;
#define IA32_VMX_BASIC_REGISTER_DUAL_MONITOR_SUPPORT_BIT             49
#define IA32_VMX_BASIC_REGISTER_DUAL_MONITOR_SUPPORT_MASK            0x01
#define IA32_VMX_BASIC_REGISTER_DUAL_MONITOR_SUPPORT(_)              (((_) >> 49) & 0x01)

    /**
     * @brief Memory type that must be used for the VMCS
     *
     * [Bits 53:50] Report the memory type that should be used for the VMCS, for data structures referenced by pointers in the
     * VMCS (I/O bitmaps, virtual-APIC page, MSR areas for VMX transitions), and for the MSEG header. If software needs to
     * access these data structures (e.g., to modify the contents of the MSR bitmaps), it can configure the paging structures
     * to map them into the linear-address space. If it does so, it should establish mappings that use the memory type reported
     * bits 53:50 in this MSR.
     * As of this writing, all processors that support VMX operation indicate the write-back type.
     */
    UINT64 MemoryType                                              : 4;
#define IA32_VMX_BASIC_REGISTER_MEMORY_TYPE_BIT                      50
#define IA32_VMX_BASIC_REGISTER_MEMORY_TYPE_MASK                     0x0F
#define IA32_VMX_BASIC_REGISTER_MEMORY_TYPE(_)                       (((_) >> 50) & 0x0F)

    /**
     * @brief Whether the processor provides additional information for exits due to INS/OUTS
     *
     * [Bit 54] When set to 1, the processor reports information in the VM-exit instruction-information field on VM exits due
     * to execution of the INS and OUTS instructions. This reporting is done only if this bit is read as 1.
     *
     * @see Vol3C[27.2.4(Information for VM Exits Due to Instruction Execution)]
     */
    UINT64 InsOutsReporting                                        : 1;
#define IA32_VMX_BASIC_REGISTER_INS_OUTS_REPORTING_BIT               54
#define IA32_VMX_BASIC_REGISTER_INS_OUTS_REPORTING_MASK              0x01
#define IA32_VMX_BASIC_REGISTER_INS_OUTS_REPORTING(_)                (((_) >> 54) & 0x01)

    /**
     * @brief Whether default 1 bits in control MSRs (pin/proc/exit/entry) may be cleared to 0 and that 'true' control MSRs are
     *        supported
     *
     * [Bit 55] Is read as 1 if any VMX controls that default to 1 may be cleared to 0. It also reports support for the VMX
     * capability MSRs IA32_VMX_TRUE_PINBASED_CTLS, IA32_VMX_TRUE_PROCBASED_CTLS, IA32_VMX_TRUE_EXIT_CTLS, and
     * IA32_VMX_TRUE_ENTRY_CTLS.
     *
     * @see Vol3D[A.2(RESERVED CONTROLS AND DEFAULT SETTINGS)]
     * @see Vol3D[A.3.1(Pin-Based VM-Execution Controls)]
     * @see Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)]
     * @see Vol3D[A.4(VM-EXIT CONTROLS)]
     * @see Vol3D[A.5(VM-ENTRY CONTROLS)]
     */
    UINT64 VmxControls                                             : 1;
#define IA32_VMX_BASIC_REGISTER_VMX_CONTROLS_BIT                     55
#define IA32_VMX_BASIC_REGISTER_VMX_CONTROLS_MASK                    0x01
#define IA32_VMX_BASIC_REGISTER_VMX_CONTROLS(_)                      (((_) >> 55) & 0x01)
    UINT64 Reserved2                                               : 8;
  };

  UINT64 Flags;
} IA32_VMX_BASIC_REGISTER;

/**
 * Capability Reporting Register of Pin-Based VM-Execution Controls.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.3.1(Pin-Based VM-Execution Controls)]
 * @see Vol3C[24.6.1(Pin-Based VM-Execution Controls)] (reference)
 */
#define IA32_VMX_PINBASED_CTLS                                       0x00000481

typedef union
{
  struct
  {
    /**
     * @brief External interrupts cause VM-exits if set; otherwise dispatched through the guest's IDT
     *
     * [Bit 0] If this control is 1, external interrupts cause VM exits. Otherwise, they are delivered normally through the
     * guest interrupt-descriptor table (IDT). If this control is 1, the value of RFLAGS.IF does not affect interrupt blocking.
     */
    UINT64 ExternalInterruptExiting                                : 1;
#define IA32_VMX_PINBASED_CTLS_REGISTER_EXTERNAL_INTERRUPT_EXITING_BIT 0
#define IA32_VMX_PINBASED_CTLS_REGISTER_EXTERNAL_INTERRUPT_EXITING_MASK 0x01
#define IA32_VMX_PINBASED_CTLS_REGISTER_EXTERNAL_INTERRUPT_EXITING(_) (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 2;

    /**
     * @brief Non-maskable interrupts cause VM-exits if set; otherwise dispatched through the guest's IDT
     *
     * [Bit 3] If this control is 1, non-maskable interrupts (NMIs) cause VM exits. Otherwise, they are delivered normally
     * using descriptor 2 of the IDT. This control also determines interactions between IRET and blocking by NMI.
     *
     * @see Vol3C[25.3(CHANGES TO INSTRUCTION BEHAVIOR IN VMX NON-ROOT OPERATION)]
     */
    UINT64 NmiExiting                                              : 1;
#define IA32_VMX_PINBASED_CTLS_REGISTER_NMI_EXITING_BIT              3
#define IA32_VMX_PINBASED_CTLS_REGISTER_NMI_EXITING_MASK             0x01
#define IA32_VMX_PINBASED_CTLS_REGISTER_NMI_EXITING(_)               (((_) >> 3) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief Virtual NMIs
     *
     * [Bit 5] If this control is 1, NMIs are never blocked and the "blocking by NMI" bit (bit 3) in the interruptibility-state
     * field indicates "virtual-NMI blocking". This control also interacts with the "NMI-window exiting" VM-execution control.
     *
     * @see Vol3C[24.6.2(Processor-Based VM-Execution Controls)]
     */
    UINT64 VirtualNmi                                              : 1;
#define IA32_VMX_PINBASED_CTLS_REGISTER_VIRTUAL_NMI_BIT              5
#define IA32_VMX_PINBASED_CTLS_REGISTER_VIRTUAL_NMI_MASK             0x01
#define IA32_VMX_PINBASED_CTLS_REGISTER_VIRTUAL_NMI(_)               (((_) >> 5) & 0x01)

    /**
     * @brief Activate VMX preemption timer
     *
     * [Bit 6] If this control is 1, the VMX-preemption timer counts down in VMX non-root operation. A VM exit occurs when the
     * timer counts down to zero.
     *
     * @see Vol3C[25.5.1(VMX-Preemption Timer)]
     * @see Vol3C[25.2(OTHER CAUSES OF VM EXITS)]
     */
    UINT64 ActivateVmxPreemptionTimer                              : 1;
#define IA32_VMX_PINBASED_CTLS_REGISTER_ACTIVATE_VMX_PREEMPTION_TIMER_BIT 6
#define IA32_VMX_PINBASED_CTLS_REGISTER_ACTIVATE_VMX_PREEMPTION_TIMER_MASK 0x01
#define IA32_VMX_PINBASED_CTLS_REGISTER_ACTIVATE_VMX_PREEMPTION_TIMER(_) (((_) >> 6) & 0x01)

    /**
     * @brief Process interrupts with the posted-interrupt notification vector
     *
     * [Bit 7] If this control is 1, the processor treats interrupts with the posted-interrupt notification vector specially,
     * updating the virtual-APIC page with posted-interrupt requests.
     *
     * @see Vol3C[24.6.8(Controls for APIC Virtualization)]
     * @see Vol3C[29.6(POSTED-INTERRUPT PROCESSING)]
     */
    UINT64 ProcessPostedInterrupts                                 : 1;
#define IA32_VMX_PINBASED_CTLS_REGISTER_PROCESS_POSTED_INTERRUPTS_BIT 7
#define IA32_VMX_PINBASED_CTLS_REGISTER_PROCESS_POSTED_INTERRUPTS_MASK 0x01
#define IA32_VMX_PINBASED_CTLS_REGISTER_PROCESS_POSTED_INTERRUPTS(_) (((_) >> 7) & 0x01)
    UINT64 Reserved3                                               : 56;
  };

  UINT64 Flags;
} IA32_VMX_PINBASED_CTLS_REGISTER;

/**
 * Capability Reporting Register of Primary Processor-Based VM-Execution Controls.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)]
 * @see Vol3C[24.6.2(Processor-Based VM-Execution Controls)] (reference)
 */
#define IA32_VMX_PROCBASED_CTLS                                      0x00000482

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;

    /**
     * @brief VM-exit as soon as RFLAGS.IF=1 and no blocking is active
     *
     * [Bit 2] If this control is 1, a VM exit occurs at the beginning of any instruction if RFLAGS.IF = 1 and there are no
     * other blocking of interrupts.
     *
     * @see Vol3C[24.4.2(Guest Non-Register State)]
     */
    UINT64 InterruptWindowExiting                                  : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INTERRUPT_WINDOW_EXITING_BIT 2
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INTERRUPT_WINDOW_EXITING_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INTERRUPT_WINDOW_EXITING(_) (((_) >> 2) & 0x01)

    /**
     * @brief Use timestamp counter offset
     *
     * [Bit 3] This control determines whether executions of RDTSC, executions of RDTSCP, and executions of RDMSR that read
     * from the IA32_TIME_STAMP_COUNTER MSR return a value modified by the TSC offset field.
     *
     * @see Vol3C[24.6.5(Time-Stamp Counter Offset and Multiplier)]
     * @see Vol3C[25.3(CHANGES TO INSTRUCTION BEHAVIOR IN VMX NON-ROOT OPERATION)]
     */
    UINT64 UseTscOffsetting                                        : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TSC_OFFSETTING_BIT      3
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TSC_OFFSETTING_MASK     0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TSC_OFFSETTING(_)       (((_) >> 3) & 0x01)
    UINT64 Reserved2                                               : 3;

    /**
     * @brief VM-exit when executing the HLT instruction
     *
     * [Bit 7] This control determines whether executions of HLT cause VM exits.
     */
    UINT64 HltExiting                                              : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_HLT_EXITING_BIT             7
#define IA32_VMX_PROCBASED_CTLS_REGISTER_HLT_EXITING_MASK            0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_HLT_EXITING(_)              (((_) >> 7) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * @brief VM-exit when executing the INVLPG instruction
     *
     * [Bit 9] This control determines whether executions of INVLPG cause VM exits.
     */
    UINT64 InvlpgExiting                                           : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INVLPG_EXITING_BIT          9
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INVLPG_EXITING_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_INVLPG_EXITING(_)           (((_) >> 9) & 0x01)

    /**
     * @brief VM-exit when executing the MWAIT instruction
     *
     * [Bit 10] This control determines whether executions of MWAIT cause VM exits.
     */
    UINT64 MwaitExiting                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MWAIT_EXITING_BIT           10
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MWAIT_EXITING_MASK          0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MWAIT_EXITING(_)            (((_) >> 10) & 0x01)

    /**
     * @brief VM-exit when executing the RDPMC instruction
     *
     * [Bit 11] This control determines whether executions of RDPMC cause VM exits.
     */
    UINT64 RdpmcExiting                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDPMC_EXITING_BIT           11
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDPMC_EXITING_MASK          0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDPMC_EXITING(_)            (((_) >> 11) & 0x01)

    /**
     * @brief VM-exit when executing the RDTSC/RDTSCP instruction
     *
     * [Bit 12] This control determines whether executions of RDTSC and RDTSCP cause VM exits.
     */
    UINT64 RdtscExiting                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDTSC_EXITING_BIT           12
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDTSC_EXITING_MASK          0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_RDTSC_EXITING(_)            (((_) >> 12) & 0x01)
    UINT64 Reserved4                                               : 2;

    /**
     * @brief VM-exit when executing the MOV to CR3 instruction (forced to 1 on the 'first' VT-x capable CPUs; this actually
     *        includes the newest Nehalem CPUs)
     *
     * [Bit 15] In conjunction with the CR3-target controls, this control determines whether executions of MOV to CR3 cause VM
     * exits. The first processors to support the virtual-machine extensions supported only the 1-setting of this control.
     *
     * @see Vol3C[24.6.7(CR3-Target Controls)]
     * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
     */
    UINT64 Cr3LoadExiting                                          : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_LOAD_EXITING_BIT        15
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_LOAD_EXITING_MASK       0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_LOAD_EXITING(_)         (((_) >> 15) & 0x01)

    /**
     * @brief VM-exit when executing the MOV from CR3 instruction (forced to 1 on the 'first' VT-x capable CPUs; this actually
     *        includes the newest Nehalem CPUs)
     *
     * [Bit 16] This control determines whether executions of MOV from CR3 cause VM exits. The first processors to support the
     * virtual-machine extensions supported only the 1-setting of this control.
     */
    UINT64 Cr3StoreExiting                                         : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_STORE_EXITING_BIT       16
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_STORE_EXITING_MASK      0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR3_STORE_EXITING(_)        (((_) >> 16) & 0x01)
    UINT64 Reserved5                                               : 2;

    /**
     * @brief VM-exit on CR8 loads
     *
     * [Bit 19] This control determines whether executions of MOV to CR8 cause VM exits.
     */
    UINT64 Cr8LoadExiting                                          : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_LOAD_EXITING_BIT        19
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_LOAD_EXITING_MASK       0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_LOAD_EXITING(_)         (((_) >> 19) & 0x01)

    /**
     * @brief VM-exit on CR8 stores
     *
     * [Bit 20] This control determines whether executions of MOV from CR8 cause VM exits.
     */
    UINT64 Cr8StoreExiting                                         : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_STORE_EXITING_BIT       20
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_STORE_EXITING_MASK      0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_CR8_STORE_EXITING(_)        (((_) >> 20) & 0x01)

    /**
     * @brief Use TPR shadow
     *
     * [Bit 21] Setting this control to 1 enables TPR virtualization and other APIC-virtualization features.
     *
     * @see Vol3C[29(APIC VIRTUALIZATION AND VIRTUAL INTERRUPTS)]
     */
    UINT64 UseTprShadow                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TPR_SHADOW_BIT          21
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TPR_SHADOW_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_TPR_SHADOW(_)           (((_) >> 21) & 0x01)

    /**
     * @brief VM-exit when virtual NMI blocking is disabled
     *
     * [Bit 22] If this control is 1, a VM exit occurs at the beginning of any instruction if there is no virtual-NMI blocking.
     *
     * @see Vol3C[24.4.2(Guest Non-Register State)]
     */
    UINT64 NmiWindowExiting                                        : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_NMI_WINDOW_EXITING_BIT      22
#define IA32_VMX_PROCBASED_CTLS_REGISTER_NMI_WINDOW_EXITING_MASK     0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_NMI_WINDOW_EXITING(_)       (((_) >> 22) & 0x01)

    /**
     * @brief VM-exit when executing a MOV DRx instruction
     *
     * [Bit 23] This control determines whether executions of MOV DR cause VM exits.
     */
    UINT64 MovDrExiting                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MOV_DR_EXITING_BIT          23
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MOV_DR_EXITING_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MOV_DR_EXITING(_)           (((_) >> 23) & 0x01)

    /**
     * @brief VM-exit when executing IO instructions
     *
     * [Bit 24] This control determines whether executions of I/O instructions (IN, INS/INSB/INSW/INSD, OUT, and
     * OUTS/OUTSB/OUTSW/OUTSD) cause VM exits.
     */
    UINT64 UnconditionalIoExiting                                  : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_UNCONDITIONAL_IO_EXITING_BIT 24
#define IA32_VMX_PROCBASED_CTLS_REGISTER_UNCONDITIONAL_IO_EXITING_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_UNCONDITIONAL_IO_EXITING(_) (((_) >> 24) & 0x01)

    /**
     * @brief Use IO bitmaps
     *
     * [Bit 25] This control determines whether I/O bitmaps are used to restrict executions of I/O instructions For this
     * control, "0" means "do not use I/O bitmaps" and "1" means "use I/O bitmaps." If the I/O bitmaps are used, the setting of
     * the "unconditional I/O exiting" control is ignored.
     *
     * @see Vol3C[24.6.4(I/O-Bitmap Addresses)]
     * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
     */
    UINT64 UseIoBitmaps                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_IO_BITMAPS_BIT          25
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_IO_BITMAPS_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_IO_BITMAPS(_)           (((_) >> 25) & 0x01)
    UINT64 Reserved6                                               : 1;

    /**
     * @brief Monitor trap flag
     *
     * [Bit 27] If this control is 1, the monitor trap flag debugging feature is enabled.
     *
     * @see Vol3C[25.5.2(Monitor Trap Flag)]
     */
    UINT64 MonitorTrapFlag                                         : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_TRAP_FLAG_BIT       27
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_TRAP_FLAG_MASK      0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_TRAP_FLAG(_)        (((_) >> 27) & 0x01)

    /**
     * @brief Use MSR bitmaps
     *
     * [Bit 28] This control determines whether MSR bitmaps are used to control execution of the RDMSR and WRMSR instructions.
     * For this control, "0" means "do not use MSR bitmaps" and "1" means "use MSR bitmaps." If the MSR bitmaps are not used,
     * all executions of the RDMSR and WRMSR instructions cause VM exits.
     *
     * @see Vol3C[24.6.9(MSR-Bitmap Address)]
     * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
     */
    UINT64 UseMsrBitmaps                                           : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_MSR_BITMAPS_BIT         28
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_MSR_BITMAPS_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_USE_MSR_BITMAPS(_)          (((_) >> 28) & 0x01)

    /**
     * @brief VM-exit when executing the MONITOR instruction
     *
     * [Bit 29] This control determines whether executions of MONITOR cause VM exits.
     */
    UINT64 MonitorExiting                                          : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_EXITING_BIT         29
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_EXITING_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_MONITOR_EXITING(_)          (((_) >> 29) & 0x01)

    /**
     * @brief VM-exit when executing the PAUSE instruction
     *
     * [Bit 30] This control determines whether executions of PAUSE cause VM exits.
     */
    UINT64 PauseExiting                                            : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_PAUSE_EXITING_BIT           30
#define IA32_VMX_PROCBASED_CTLS_REGISTER_PAUSE_EXITING_MASK          0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_PAUSE_EXITING(_)            (((_) >> 30) & 0x01)

    /**
     * @brief Determines whether the secondary processor based VM-execution controls are used
     *
     * [Bit 31] This control determines whether the secondary processor-based VM-execution controls are used. If this control
     * is 0, the logical processor operates as if all the secondary processor-based VM-execution controls were also 0.
     */
    UINT64 ActivateSecondaryControls                               : 1;
#define IA32_VMX_PROCBASED_CTLS_REGISTER_ACTIVATE_SECONDARY_CONTROLS_BIT 31
#define IA32_VMX_PROCBASED_CTLS_REGISTER_ACTIVATE_SECONDARY_CONTROLS_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS_REGISTER_ACTIVATE_SECONDARY_CONTROLS(_) (((_) >> 31) & 0x01)
    UINT64 Reserved7                                               : 32;
  };

  UINT64 Flags;
} IA32_VMX_PROCBASED_CTLS_REGISTER;

/**
 * Capability Reporting Register of VM-Exit Controls.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.4(VM-EXIT CONTROLS)]
 * @see Vol3C[24.7.1(VM-Exit Controls)] (reference)
 */
#define IA32_VMX_EXIT_CTLS                                           0x00000483

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;

    /**
     * @brief Save guest debug controls (dr7 & IA32_DEBUGCTL_MSR) (forced to 1 on the 'first' VT-x capable CPUs; this actually
     *        includes the newest Nehalem CPUs)
     *
     * [Bit 2] This control determines whether DR7 and the IA32_DEBUGCTL MSR are saved on VM exit. The first processors to
     * support the virtual-machine extensions supported only the 1-setting of this control.
     */
    UINT64 SaveDebugControls                                       : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_DEBUG_CONTROLS_BIT          2
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_DEBUG_CONTROLS_MASK         0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_DEBUG_CONTROLS(_)           (((_) >> 2) & 0x01)
    UINT64 Reserved2                                               : 6;

    /**
     * @brief Return to long mode after a VM-exit
     *
     * [Bit 9] On processors that support Intel 64 architecture, this control determines whether a logical processor is in
     * 64-bit mode after the next VM exit. Its value is loaded into CS.L, IA32_EFER.LME, and IA32_EFER.LMA on every VM exit.1
     * This control must be 0 on processors that do not support Intel 64 architecture.
     */
    UINT64 HostAddressSpaceSize                                    : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_HOST_ADDRESS_SPACE_SIZE_BIT      9
#define IA32_VMX_EXIT_CTLS_REGISTER_HOST_ADDRESS_SPACE_SIZE_MASK     0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_HOST_ADDRESS_SPACE_SIZE(_)       (((_) >> 9) & 0x01)
    UINT64 Reserved3                                               : 2;

    /**
     * @brief Whether the IA32_PERF_GLOBAL_CTRL MSR is loaded on VM-exit
     *
     * [Bit 12] This control determines whether the IA32_PERF_GLOBAL_CTRL MSR is loaded on VM exit.
     */
    UINT64 LoadIa32PerfGlobalCtrl                                  : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL_BIT   12
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL_MASK  0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL(_)    (((_) >> 12) & 0x01)
    UINT64 Reserved4                                               : 2;

    /**
     * @brief Acknowledge external interrupts with the irq controller if one caused a VM-exit
     *
     * [Bit 15] This control affects VM exits due to external interrupts:
     * - If such a VM exit occurs and this control is 1, the logical processor acknowledges the interrupt controller, acquiring
     * the interrupt's vector. The vector is stored in the VM-exit interruption-information field, which is marked valid.
     * - If such a VM exit occurs and this control is 0, the interrupt is not acknowledged and the VM-exit
     * interruption-information field is marked invalid.
     */
    UINT64 AcknowledgeInterruptOnExit                              : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_ACKNOWLEDGE_INTERRUPT_ON_EXIT_BIT 15
#define IA32_VMX_EXIT_CTLS_REGISTER_ACKNOWLEDGE_INTERRUPT_ON_EXIT_MASK 0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_ACKNOWLEDGE_INTERRUPT_ON_EXIT(_) (((_) >> 15) & 0x01)
    UINT64 Reserved5                                               : 2;

    /**
     * @brief Whether the guest IA32_PAT MSR is saved on VM-exit
     *
     * [Bit 18] This control determines whether the IA32_PAT MSR is saved on VM exit.
     */
    UINT64 SaveIa32Pat                                             : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_PAT_BIT                18
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_PAT_MASK               0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_PAT(_)                 (((_) >> 18) & 0x01)

    /**
     * @brief Whether the host IA32_PAT MSR is loaded on VM-exit
     *
     * [Bit 19] This control determines whether the IA32_PAT MSR is loaded on VM exit.
     */
    UINT64 LoadIa32Pat                                             : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PAT_BIT                19
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PAT_MASK               0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_PAT(_)                 (((_) >> 19) & 0x01)

    /**
     * @brief Whether the guest IA32_EFER MSR is saved on VM-exit
     *
     * [Bit 20] This control determines whether the IA32_EFER MSR is saved on VM exit.
     */
    UINT64 SaveIa32Efer                                            : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_EFER_BIT               20
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_EFER_MASK              0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_IA32_EFER(_)                (((_) >> 20) & 0x01)

    /**
     * @brief Whether the host IA32_EFER MSR is loaded on VM-exit
     *
     * [Bit 21] This control determines whether the IA32_EFER MSR is loaded on VM exit.
     */
    UINT64 LoadIa32Efer                                            : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_EFER_BIT               21
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_EFER_MASK              0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_LOAD_IA32_EFER(_)                (((_) >> 21) & 0x01)

    /**
     * @brief Whether the value of the VMX preemption timer is saved on every VM-exit
     *
     * [Bit 22] This control determines whether the value of the VMX-preemption timer is saved on VM exit.
     */
    UINT64 SaveVmxPreemptionTimerValue                             : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_VMX_PREEMPTION_TIMER_VALUE_BIT 22
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_VMX_PREEMPTION_TIMER_VALUE_MASK 0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_SAVE_VMX_PREEMPTION_TIMER_VALUE(_) (((_) >> 22) & 0x01)

    /**
     * [Bit 23] This control determines whether the IA32_BNDCFGS MSR is cleared on VM exit.
     */
    UINT64 ClearIa32Bndcfgs                                        : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_CLEAR_IA32_BNDCFGS_BIT           23
#define IA32_VMX_EXIT_CTLS_REGISTER_CLEAR_IA32_BNDCFGS_MASK          0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_CLEAR_IA32_BNDCFGS(_)            (((_) >> 23) & 0x01)

    /**
     * [Bit 24] If this control is 1, Intel Processor Trace does not produce a paging information packet (PIP) on a VM exit or
     * a VMCS packet on an SMM VM exit.
     *
     * @see Vol3C[35(INTEL(R) PROCESSOR TRACE)]
     */
    UINT64 ConcealVmxFromPt                                        : 1;
#define IA32_VMX_EXIT_CTLS_REGISTER_CONCEAL_VMX_FROM_PT_BIT          24
#define IA32_VMX_EXIT_CTLS_REGISTER_CONCEAL_VMX_FROM_PT_MASK         0x01
#define IA32_VMX_EXIT_CTLS_REGISTER_CONCEAL_VMX_FROM_PT(_)           (((_) >> 24) & 0x01)
    UINT64 Reserved6                                               : 39;
  };

  UINT64 Flags;
} IA32_VMX_EXIT_CTLS_REGISTER;

/**
 * Capability Reporting Register of VM-Entry Controls.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.5(VM-ENTRY CONTROLS)]
 * @see Vol3D[24.8.1(VM-Entry Controls)] (reference)
 */
#define IA32_VMX_ENTRY_CTLS                                          0x00000484

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;

    /**
     * @brief Load guest debug controls (dr7 & IA32_DEBUGCTL_MSR) (forced to 1 on the 'first' VT-x capable CPUs; this actually
     *        includes the newest Nehalem CPUs)
     *
     * [Bit 2] This control determines whether DR7 and the IA32_DEBUGCTL MSR are loaded on VM entry. The first processors to
     * support the virtual-machine extensions supported only the 1-setting of this control.
     */
    UINT64 LoadDebugControls                                       : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_DEBUG_CONTROLS_BIT         2
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_DEBUG_CONTROLS_MASK        0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_DEBUG_CONTROLS(_)          (((_) >> 2) & 0x01)
    UINT64 Reserved2                                               : 6;

    /**
     * @brief 64 bits guest mode. Must be 0 for CPUs that don't support AMD64
     *
     * [Bit 9] On processors that support Intel 64 architecture, this control determines whether the logical processor is in
     * IA-32e mode after VM entry. Its value is loaded into IA32_EFER.LMA as part of VM entry. This control must be 0 on
     * processors that do not support Intel 64 architecture.
     */
    UINT64 Ia32EModeGuest                                          : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_IA32E_MODE_GUEST_BIT            9
#define IA32_VMX_ENTRY_CTLS_REGISTER_IA32E_MODE_GUEST_MASK           0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_IA32E_MODE_GUEST(_)             (((_) >> 9) & 0x01)

    /**
     * @brief In SMM mode after VM-entry
     *
     * [Bit 10] This control determines whether the logical processor is in system-management mode (SMM) after VM entry. This
     * control must be 0 for any VM entry from outside SMM.
     */
    UINT64 EntryToSmm                                              : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_ENTRY_TO_SMM_BIT                10
#define IA32_VMX_ENTRY_CTLS_REGISTER_ENTRY_TO_SMM_MASK               0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_ENTRY_TO_SMM(_)                 (((_) >> 10) & 0x01)

    /**
     * @brief Disable dual treatment of SMI and SMM; must be zero for VM-entry outside of SMM
     *
     * [Bit 11] If set to 1, the default treatment of SMIs and SMM is in effect after the VM entry. This control must be 0 for
     * any VM entry from outside SMM
     *
     * @see Vol3C[34.15.7(Deactivating the Dual-Monitor Treatment)]
     */
    UINT64 DeactivateDualMonitorTreatment                          : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_DEACTIVATE_DUAL_MONITOR_TREATMENT_BIT 11
#define IA32_VMX_ENTRY_CTLS_REGISTER_DEACTIVATE_DUAL_MONITOR_TREATMENT_MASK 0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_DEACTIVATE_DUAL_MONITOR_TREATMENT(_) (((_) >> 11) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * @brief Whether the guest IA32_PERF_GLOBAL_CTRL MSR is loaded on VM-entry
     *
     * [Bit 13] This control determines whether the IA32_PERF_GLOBAL_CTRL MSR is loaded on VM entry.
     */
    UINT64 LoadIa32PerfGlobalCtrl                                  : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL_BIT  13
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL_MASK 0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PERF_GLOBAL_CTRL(_)   (((_) >> 13) & 0x01)

    /**
     * @brief Whether the guest IA32_PAT MSR is loaded on VM-entry
     *
     * [Bit 14] This control determines whether the IA32_PAT MSR is loaded on VM entry.
     */
    UINT64 LoadIa32Pat                                             : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PAT_BIT               14
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PAT_MASK              0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_PAT(_)                (((_) >> 14) & 0x01)

    /**
     * @brief Whether the guest IA32_EFER MSR is loaded on VM-entry
     *
     * [Bit 15] This control determines whether the IA32_EFER MSR is loaded on VM entry.
     */
    UINT64 LoadIa32Efer                                            : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_EFER_BIT              15
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_EFER_MASK             0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_EFER(_)               (((_) >> 15) & 0x01)

    /**
     * [Bit 16] This control determines whether the IA32_BNDCFGS MSR is loaded on VM entry.
     */
    UINT64 LoadIa32Bndcfgs                                         : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_BNDCFGS_BIT           16
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_BNDCFGS_MASK          0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_LOAD_IA32_BNDCFGS(_)            (((_) >> 16) & 0x01)

    /**
     * [Bit 17] If this control is 1, Intel Processor Trace does not produce a paging information packet (PIP) on a VM entry or
     * a VMCS packet on a VM entry that returns from SMM.
     *
     * @see Vol3C[35(INTEL(R) PROCESSOR TRACE)]
     */
    UINT64 ConcealVmxFromPt                                        : 1;
#define IA32_VMX_ENTRY_CTLS_REGISTER_CONCEAL_VMX_FROM_PT_BIT         17
#define IA32_VMX_ENTRY_CTLS_REGISTER_CONCEAL_VMX_FROM_PT_MASK        0x01
#define IA32_VMX_ENTRY_CTLS_REGISTER_CONCEAL_VMX_FROM_PT(_)          (((_) >> 17) & 0x01)
    UINT64 Reserved4                                               : 46;
  };

  UINT64 Flags;
} IA32_VMX_ENTRY_CTLS_REGISTER;

/**
 * Reporting Register of Miscellaneous VMX Capabilities.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.6(MISCELLANEOUS DATA)]
 * @see Vol3D[A.6(Miscellaneous Data)] (reference)
 */
#define IA32_VMX_MISC                                                0x00000485

typedef union
{
  struct
  {
    /**
     * @brief Relationship between the preemption timer and tsc; count down every time bit x of the tsc changes
     *
     * [Bits 4:0] Report a value X that specifies the relationship between the rate of the VMX-preemption timer and that of the
     * timestamp counter (TSC). Specifically, the VMX-preemption timer (if it is active) counts down by 1 every time bit X in
     * the TSC changes due to a TSC increment.
     */
    UINT64 PreemptionTimerTscRelationship                          : 5;
#define IA32_VMX_MISC_REGISTER_PREEMPTION_TIMER_TSC_RELATIONSHIP_BIT 0
#define IA32_VMX_MISC_REGISTER_PREEMPTION_TIMER_TSC_RELATIONSHIP_MASK 0x1F
#define IA32_VMX_MISC_REGISTER_PREEMPTION_TIMER_TSC_RELATIONSHIP(_)  (((_) >> 0) & 0x1F)

    /**
     * @brief Whether VM-exit stores EFER.LMA into the "IA32e mode guest" field
     *
     * [Bit 5] When set to 1, VM exits store the value of IA32_EFER.LMA into the "IA-32e mode guest" VM-entry control. This bit
     * is read as 1 on any logical processor that supports the 1-setting of the "unrestricted guest" VM-execution control.
     *
     * @see Vol3C[27.2(RECORDING VM-EXIT INFORMATION AND UPDATING VM-ENTRY CONTROL FIELDS)]
     */
    UINT64 StoreEferLmaOnVmexit                                    : 1;
#define IA32_VMX_MISC_REGISTER_STORE_EFER_LMA_ON_VMEXIT_BIT          5
#define IA32_VMX_MISC_REGISTER_STORE_EFER_LMA_ON_VMEXIT_MASK         0x01
#define IA32_VMX_MISC_REGISTER_STORE_EFER_LMA_ON_VMEXIT(_)           (((_) >> 5) & 0x01)

    /**
     * @brief Activity states supported by the implementation
     *
     * [Bits 8:6] Report, as a bitmap, the activity states supported by the implementation:
     * - Bit 6 reports (if set) the support for activity state 1 (HLT).
     * - Bit 7 reports (if set) the support for activity state 2 (shutdown).
     * - Bit 8 reports (if set) the support for activity state 3 (wait-for-SIPI).
     * If an activity state is not supported, the implementation causes a VM entry to fail if it attempts to establish that
     * activity state. All implementations support VM entry to activity state 0 (active).
     */
    UINT64 ActivityStates                                          : 3;
#define IA32_VMX_MISC_REGISTER_ACTIVITY_STATES_BIT                   6
#define IA32_VMX_MISC_REGISTER_ACTIVITY_STATES_MASK                  0x07
#define IA32_VMX_MISC_REGISTER_ACTIVITY_STATES(_)                    (((_) >> 6) & 0x07)
    UINT64 Reserved1                                               : 5;

    /**
     * @brief Intel Processor Trace (Intel PT) can be used in VMX operation
     *
     * [Bit 14] When set to 1, Intel(R) Processor Trace (Intel PT) can be used in VMX operation. If the processor supports Intel
     * PT but does not allow it to be used in VMX operation, execution of VMXON clears IA32_RTIT_CTL.TraceEn; any attempt to
     * write IA32_RTIT_CTL while in VMX operation (including VMX root operation) causes a general-protection exception.
     *
     * @see Vol3C[30.3(VMX INSTRUCTIONS | VMXON-Enter VMX Operation)]
     */
    UINT64 IntelPtAvailableInVmx                                   : 1;
#define IA32_VMX_MISC_REGISTER_INTEL_PT_AVAILABLE_IN_VMX_BIT         14
#define IA32_VMX_MISC_REGISTER_INTEL_PT_AVAILABLE_IN_VMX_MASK        0x01
#define IA32_VMX_MISC_REGISTER_INTEL_PT_AVAILABLE_IN_VMX(_)          (((_) >> 14) & 0x01)

    /**
     * @brief Whether RDMSR can be used to read IA32_SMBASE_MSR in SMM
     *
     * [Bit 15] When set to 1, the RDMSR instruction can be used in system-management mode (SMM) to read the IA32_SMBASE MSR
     * (MSR address 9EH).
     *
     * @see Vol3C[34.15.6.3(Saving Guest State)]
     */
    UINT64 RdmsrCanReadIa32SmbaseMsrInSmm                          : 1;
#define IA32_VMX_MISC_REGISTER_RDMSR_CAN_READ_IA32_SMBASE_MSR_IN_SMM_BIT 15
#define IA32_VMX_MISC_REGISTER_RDMSR_CAN_READ_IA32_SMBASE_MSR_IN_SMM_MASK 0x01
#define IA32_VMX_MISC_REGISTER_RDMSR_CAN_READ_IA32_SMBASE_MSR_IN_SMM(_) (((_) >> 15) & 0x01)

    /**
     * @brief Number of CR3 target values supported by the processor (0-256)
     *
     * [Bits 24:16] Indicate the number of CR3-target values supported by the processor. This number is a value between 0 and
     * 256, inclusive (bit 24 is set if and only if bits 23:16 are clear).
     */
    UINT64 Cr3TargetCount                                          : 9;
#define IA32_VMX_MISC_REGISTER_CR3_TARGET_COUNT_BIT                  16
#define IA32_VMX_MISC_REGISTER_CR3_TARGET_COUNT_MASK                 0x1FF
#define IA32_VMX_MISC_REGISTER_CR3_TARGET_COUNT(_)                   (((_) >> 16) & 0x1FF)

    /**
     * @brief Maximum number of MSRs in the VMCS. (N+1)*512
     *
     * [Bits 27:25] Used to compute the recommended maximum number of MSRs that should appear in the VM-exit MSR-store list,
     * the VM-exit MSR-load list, or the VM-entry MSR-load list. Specifically, if the value bits 27:25 of IA32_VMX_MISC is N,
     * then 512 * (N + 1) is the recommended maximum number of MSRs to be included in each list. If the limit is exceeded,
     * undefined processor behavior may result (including a machine check during the VMX transition).
     */
    UINT64 MaxNumberOfMsr                                          : 3;
#define IA32_VMX_MISC_REGISTER_MAX_NUMBER_OF_MSR_BIT                 25
#define IA32_VMX_MISC_REGISTER_MAX_NUMBER_OF_MSR_MASK                0x07
#define IA32_VMX_MISC_REGISTER_MAX_NUMBER_OF_MSR(_)                  (((_) >> 25) & 0x07)

    /**
     * @brief Whether bit 2 of IA32_SMM_MONITOR_CTL can be set to 1
     *
     * [Bit 28] When set to 1, bit 2 of the IA32_SMM_MONITOR_CTL can be set to 1. VMXOFF unblocks SMIs unless
     * IA32_SMM_MONITOR_CTL[bit 2] is 1.
     *
     * @see Vol3C[34.14.4(VMXOFF and SMI Unblocking)]
     */
    UINT64 SmmMonitorCtlB2                                         : 1;
#define IA32_VMX_MISC_REGISTER_SMM_MONITOR_CTL_B2_BIT                28
#define IA32_VMX_MISC_REGISTER_SMM_MONITOR_CTL_B2_MASK               0x01
#define IA32_VMX_MISC_REGISTER_SMM_MONITOR_CTL_B2(_)                 (((_) >> 28) & 0x01)

    /**
     * @brief Whether VMWRITE can be used to write VM-exit information fields
     *
     * [Bit 29] When set to 1, software can use VMWRITE to write to any supported field in the VMCS; otherwise, VMWRITE cannot
     * be used to modify VM-exit information fields.
     */
    UINT64 VmwriteVmexitInfo                                       : 1;
#define IA32_VMX_MISC_REGISTER_VMWRITE_VMEXIT_INFO_BIT               29
#define IA32_VMX_MISC_REGISTER_VMWRITE_VMEXIT_INFO_MASK              0x01
#define IA32_VMX_MISC_REGISTER_VMWRITE_VMEXIT_INFO(_)                (((_) >> 29) & 0x01)

    /**
     * [Bit 30] When set to 1, VM entry allows injection of a software interrupt, software exception, or privileged software
     * exception with an instruction length of 0.
     */
    UINT64 ZeroLengthInstructionVmentryInjection                   : 1;
#define IA32_VMX_MISC_REGISTER_ZERO_LENGTH_INSTRUCTION_VMENTRY_INJECTION_BIT 30
#define IA32_VMX_MISC_REGISTER_ZERO_LENGTH_INSTRUCTION_VMENTRY_INJECTION_MASK 0x01
#define IA32_VMX_MISC_REGISTER_ZERO_LENGTH_INSTRUCTION_VMENTRY_INJECTION(_) (((_) >> 30) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief MSEG revision identifier used by the processor
     *
     * [Bits 63:32] Report the 32-bit MSEG revision identifier used by the processor.
     */
    UINT64 MsegId                                                  : 32;
#define IA32_VMX_MISC_REGISTER_MSEG_ID_BIT                           32
#define IA32_VMX_MISC_REGISTER_MSEG_ID_MASK                          0xFFFFFFFF
#define IA32_VMX_MISC_REGISTER_MSEG_ID(_)                            (((_) >> 32) & 0xFFFFFFFF)
  };

  UINT64 Flags;
} IA32_VMX_MISC_REGISTER;

/**
 * Capability Reporting Register of CR0 Bits Fixed to 0.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.7(VMX-FIXED BITS IN CR0)]
 * @see Vol3D[A.7(VMX-Fixed Bits in CR0)] (reference)
 */
#define IA32_VMX_CR0_FIXED0                                          0x00000486

/**
 * Capability Reporting Register of CR0 Bits Fixed to 1.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.7(VMX-FIXED BITS IN CR0)]
 * @see Vol3D[A.7(VMX-Fixed Bits in CR0)] (reference)
 */
#define IA32_VMX_CR0_FIXED1                                          0x00000487

/**
 * Capability Reporting Register of CR4 Bits Fixed to 0.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.8(VMX-FIXED BITS IN CR4)]
 * @see Vol3D[A.8(VMX-Fixed Bits in CR4)] (reference)
 */
#define IA32_VMX_CR4_FIXED0                                          0x00000488

/**
 * Capability Reporting Register of CR4 Bits Fixed to 1.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.8(VMX-FIXED BITS IN CR4)]
 * @see Vol3D[A.8(VMX-Fixed Bits in CR4)] (reference)
 */
#define IA32_VMX_CR4_FIXED1                                          0x00000489

/**
 * Capability Reporting Register of VMCS Field Enumeration.
 *
 * @remarks If CPUID.01H:ECX.[5] = 1
 * @see Vol3D[A.9(VMCS ENUMERATION)]
 * @see Vol3D[A.9(VMCS Enumeration)] (reference)
 */
#define IA32_VMX_VMCS_ENUM                                           0x0000048A

typedef union
{
  struct
  {
    /**
     * [Bit 0] Indicates access type.
     */
    UINT64 AccessType                                              : 1;
#define IA32_VMX_VMCS_ENUM_REGISTER_ACCESS_TYPE_BIT                  0
#define IA32_VMX_VMCS_ENUM_REGISTER_ACCESS_TYPE_MASK                 0x01
#define IA32_VMX_VMCS_ENUM_REGISTER_ACCESS_TYPE(_)                   (((_) >> 0) & 0x01)

    /**
     * [Bits 9:1] Highest index value used for any VMCS encoding.
     */
    UINT64 HighestIndexValue                                       : 9;
#define IA32_VMX_VMCS_ENUM_REGISTER_HIGHEST_INDEX_VALUE_BIT          1
#define IA32_VMX_VMCS_ENUM_REGISTER_HIGHEST_INDEX_VALUE_MASK         0x1FF
#define IA32_VMX_VMCS_ENUM_REGISTER_HIGHEST_INDEX_VALUE(_)           (((_) >> 1) & 0x1FF)

    /**
     * [Bits 11:10] Indicate the field's type.
     */
    UINT64 FieldType                                               : 2;
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_TYPE_BIT                   10
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_TYPE_MASK                  0x03
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_TYPE(_)                    (((_) >> 10) & 0x03)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bits 14:13] Indicate the field's width.
     */
    UINT64 FieldWidth                                              : 2;
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_WIDTH_BIT                  13
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_WIDTH_MASK                 0x03
#define IA32_VMX_VMCS_ENUM_REGISTER_FIELD_WIDTH(_)                   (((_) >> 13) & 0x03)
    UINT64 Reserved2                                               : 49;
  };

  UINT64 Flags;
} IA32_VMX_VMCS_ENUM_REGISTER;

/**
 * Capability Reporting Register of Secondary Processor-Based VM-Execution Controls.
 *
 * @remarks If ( CPUID.01H:ECX.[5] && IA32_VMX_PROCBASED_CTLS[63] )
 * @see Vol3D[A.3.3(Secondary Processor-Based VM-Execution Controls)]
 * @see Vol3D[24.6.2(Processor-Based VM-Execution Controls)] (reference)
 */
#define IA32_VMX_PROCBASED_CTLS2                                     0x0000048B

typedef union
{
  struct
  {
    /**
     * @brief Virtualize APIC access
     *
     * [Bit 0] If this control is 1, the logical processor treats specially accesses to the page with the APICaccess address.
     *
     * @see Vol3C[29.4(VIRTUALIZING MEMORY-MAPPED APIC ACCESSES)]
     */
    UINT64 VirtualizeApicAccesses                                  : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_APIC_ACCESSES_BIT 0
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_APIC_ACCESSES_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_APIC_ACCESSES(_) (((_) >> 0) & 0x01)

    /**
     * @brief EPT supported/enabled
     *
     * [Bit 1] If this control is 1, extended page tables (EPT) are enabled.
     *
     * @see Vol3C[28.2(THE EXTENDED PAGE TABLE MECHANISM (EPT))]
     */
    UINT64 EnableEpt                                               : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_EPT_BIT             1
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_EPT_MASK            0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_EPT(_)              (((_) >> 1) & 0x01)

    /**
     * @brief Descriptor table instructions cause VM-exits
     *
     * [Bit 2] This control determines whether executions of LGDT, LIDT, LLDT, LTR, SGDT, SIDT, SLDT, and STR cause VM exits.
     */
    UINT64 DescriptorTableExiting                                  : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_DESCRIPTOR_TABLE_EXITING_BIT 2
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_DESCRIPTOR_TABLE_EXITING_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_DESCRIPTOR_TABLE_EXITING(_) (((_) >> 2) & 0x01)

    /**
     * @brief RDTSCP supported/enabled
     *
     * [Bit 3] If this control is 0, any execution of RDTSCP causes an invalid-opcode exception (\#UD).
     */
    UINT64 EnableRdtscp                                            : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_RDTSCP_BIT          3
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_RDTSCP_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_RDTSCP(_)           (((_) >> 3) & 0x01)

    /**
     * @brief Virtualize x2APIC mode
     *
     * [Bit 4] If this control is 1, the logical processor treats specially RDMSR and WRMSR to APIC MSRs (in the range
     * 800H-8FFH).
     *
     * @see Vol3C[29.5(VIRTUALIZING MSR-BASED APIC ACCESSES)]
     */
    UINT64 VirtualizeX2ApicMode                                    : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_X2APIC_MODE_BIT 4
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_X2APIC_MODE_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUALIZE_X2APIC_MODE(_)  (((_) >> 4) & 0x01)

    /**
     * @brief VPID supported/enabled
     *
     * [Bit 5] If this control is 1, cached translations of linear addresses are associated with a virtualprocessor identifier
     * (VPID).
     *
     * @see Vol3C[28.1(VIRTUAL PROCESSOR IDENTIFIERS (VPIDS))]
     */
    UINT64 EnableVpid                                              : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VPID_BIT            5
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VPID_MASK           0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VPID(_)             (((_) >> 5) & 0x01)

    /**
     * @brief VM-exit when executing the WBINVD instruction
     *
     * [Bit 6] This control determines whether executions of WBINVD cause VM exits.
     */
    UINT64 WbinvdExiting                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_WBINVD_EXITING_BIT         6
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_WBINVD_EXITING_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_WBINVD_EXITING(_)          (((_) >> 6) & 0x01)

    /**
     * @brief Unrestricted guest execution
     *
     * [Bit 7] This control determines whether guest software may run in unpaged protected mode or in realaddress mode.
     */
    UINT64 UnrestrictedGuest                                       : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_UNRESTRICTED_GUEST_BIT     7
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_UNRESTRICTED_GUEST_MASK    0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_UNRESTRICTED_GUEST(_)      (((_) >> 7) & 0x01)

    /**
     * @brief APIC register virtualization
     *
     * [Bit 8] If this control is 1, the logical processor virtualizes certain APIC accesses.
     *
     * @see Vol3C[29.4(VIRTUALIZING MEMORY-MAPPED APIC ACCESSES)]
     * @see Vol3C[29.5(VIRTUALIZING MSR-BASED APIC ACCESSES)]
     */
    UINT64 ApicRegisterVirtualization                              : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_APIC_REGISTER_VIRTUALIZATION_BIT 8
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_APIC_REGISTER_VIRTUALIZATION_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_APIC_REGISTER_VIRTUALIZATION(_) (((_) >> 8) & 0x01)

    /**
     * @brief Virtual-interrupt delivery
     *
     * [Bit 9] This controls enables the evaluation and delivery of pending virtual interrupts as well as the emulation of
     * writes to the APIC registers that control interrupt prioritization.
     */
    UINT64 VirtualInterruptDelivery                                : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUAL_INTERRUPT_DELIVERY_BIT 9
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUAL_INTERRUPT_DELIVERY_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VIRTUAL_INTERRUPT_DELIVERY(_) (((_) >> 9) & 0x01)

    /**
     * @brief A specified number of pause loops cause a VM-exit
     *
     * [Bit 10] This control determines whether a series of executions of PAUSE can cause a VM exit.
     *
     * @see Vol3C[24.6.13(Controls for PAUSE-Loop Exiting)]
     * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
     */
    UINT64 PauseLoopExiting                                        : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_PAUSE_LOOP_EXITING_BIT     10
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_PAUSE_LOOP_EXITING_MASK    0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_PAUSE_LOOP_EXITING(_)      (((_) >> 10) & 0x01)

    /**
     * @brief VM-exit when executing RDRAND instructions
     *
     * [Bit 11] This control determines whether executions of RDRAND cause VM exits.
     */
    UINT64 RdrandExiting                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDRAND_EXITING_BIT         11
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDRAND_EXITING_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDRAND_EXITING(_)          (((_) >> 11) & 0x01)

    /**
     * @brief Enables INVPCID instructions
     *
     * [Bit 12] If this control is 0, any execution of INVPCID causes a \#UD.
     */
    UINT64 EnableInvpcid                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_INVPCID_BIT         12
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_INVPCID_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_INVPCID(_)          (((_) >> 12) & 0x01)

    /**
     * @brief Enables VMFUNC instructions
     *
     * [Bit 13] Setting this control to 1 enables use of the VMFUNC instruction in VMX non-root operation.
     *
     * @see Vol3C[25.5.5(VM Functions)]
     */
    UINT64 EnableVmFunctions                                       : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VM_FUNCTIONS_BIT    13
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VM_FUNCTIONS_MASK   0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_VM_FUNCTIONS(_)     (((_) >> 13) & 0x01)

    /**
     * @brief Enables VMCS shadowing
     *
     * [Bit 14] If this control is 1, executions of VMREAD and VMWRITE in VMX non-root operation may access a shadow VMCS
     * (instead of causing VM exits).
     *
     * @see {'Vol3C[24.10(VMCS TYPES': 'ORDINARY AND SHADOW)]'}
     * @see Vol3C[30.3(VMX INSTRUCTIONS)]
     */
    UINT64 VmcsShadowing                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VMCS_SHADOWING_BIT         14
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VMCS_SHADOWING_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_VMCS_SHADOWING(_)          (((_) >> 14) & 0x01)

    /**
     * @brief Enables ENCLS VM-exits
     *
     * [Bit 15] If this control is 1, executions of ENCLS consult the ENCLS-exiting bitmap to determine whether the instruction
     * causes a VM exit.
     *
     * @see Vol3C[24.6.16(ENCLS-Exiting Bitmap)]
     * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
     */
    UINT64 EnableEnclsExiting                                      : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_ENCLS_EXITING_BIT   15
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_ENCLS_EXITING_MASK  0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_ENCLS_EXITING(_)    (((_) >> 15) & 0x01)

    /**
     * @brief VM-exit when executing RDSEED
     *
     * [Bit 16] This control determines whether executions of RDSEED cause VM exits.
     */
    UINT64 RdseedExiting                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDSEED_EXITING_BIT         16
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDSEED_EXITING_MASK        0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_RDSEED_EXITING(_)          (((_) >> 16) & 0x01)

    /**
     * @brief Enables page-modification logging
     *
     * [Bit 17] If this control is 1, an access to a guest-physical address that sets an EPT dirty bit first adds an entry to
     * the page-modification log.
     *
     * @see Vol3C[28.2.5(Page-Modification Logging)]
     */
    UINT64 EnablePml                                               : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_PML_BIT             17
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_PML_MASK            0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_PML(_)              (((_) >> 17) & 0x01)

    /**
     * @brief Controls whether EPT-violations may cause
     *
     * [Bit 18] If this control is 1, EPT violations may cause virtualization exceptions (\#VE) instead of VM exits.
     *
     * @see Vol3C[25.5.6(Virtualization Exceptions)]
     */
    UINT64 EptViolation                                            : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_EPT_VIOLATION_BIT          18
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_EPT_VIOLATION_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_EPT_VIOLATION(_)           (((_) >> 18) & 0x01)

    /**
     * @brief Conceal VMX non-root operation from Intel processor trace (PT)
     *
     * [Bit 19] If this control is 1, Intel Processor Trace suppresses from PIPs an indication that the processor was in VMX
     * non-root operation and omits a VMCS packet from any PSB+ produced in VMX nonroot operation.
     *
     * @see Vol3C[35(INTEL(R) PROCESSOR TRACE)]
     */
    UINT64 ConcealVmxFromPt                                        : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_CONCEAL_VMX_FROM_PT_BIT    19
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_CONCEAL_VMX_FROM_PT_MASK   0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_CONCEAL_VMX_FROM_PT(_)     (((_) >> 19) & 0x01)

    /**
     * @brief Enables XSAVES/XRSTORS instructions
     *
     * [Bit 20] If this control is 0, any execution of XSAVES or XRSTORS causes a \#UD.
     */
    UINT64 EnableXsaves                                            : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_XSAVES_BIT          20
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_XSAVES_MASK         0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_ENABLE_XSAVES(_)           (((_) >> 20) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 22] If this control is 1, EPT execute permissions are based on whether the linear address being accessed is
     * supervisor mode or user mode.
     *
     * @see Vol3C[28(VMX SUPPORT FOR ADDRESS TRANSLATION)]
     */
    UINT64 ModeBasedExecuteControlForEpt                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_MODE_BASED_EXECUTE_CONTROL_FOR_EPT_BIT 22
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_MODE_BASED_EXECUTE_CONTROL_FOR_EPT_MASK 0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_MODE_BASED_EXECUTE_CONTROL_FOR_EPT(_) (((_) >> 22) & 0x01)
    UINT64 Reserved2                                               : 2;

    /**
     * @brief Use TSC scaling
     *
     * [Bit 25] This control determines whether executions of RDTSC, executions of RDTSCP, and executions of RDMSR that read
     * from the IA32_TIME_STAMP_COUNTER MSR return a value modified by the TSC multiplier field.
     *
     * @see Vol3C[24.6.5(Time-Stamp Counter Offset and Multiplier)]
     * @see Vol3C[25.3(CHANGES TO INSTRUCTION BEHAVIOR IN VMX NON-ROOT OPERATION)]
     */
    UINT64 UseTscScaling                                           : 1;
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_USE_TSC_SCALING_BIT        25
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_USE_TSC_SCALING_MASK       0x01
#define IA32_VMX_PROCBASED_CTLS2_REGISTER_USE_TSC_SCALING(_)         (((_) >> 25) & 0x01)
    UINT64 Reserved3                                               : 38;
  };

  UINT64 Flags;
} IA32_VMX_PROCBASED_CTLS2_REGISTER;

/**
 * Capability Reporting Register of EPT and VPID.
 *
 * @remarks If ( CPUID.01H:ECX.[5] && IA32_VMX_PROCBASED_CTLS[63] && (IA32_VMX_PROCBASED_CTLS2[33] ||
 *          IA32_VMX_PROCBASED_CTLS2[37]) )
 * @see Vol3D[A.10(VPID AND EPT CAPABILITIES)]
 * @see Vol3D[A.10(VPID and EPT Capabilities)] (reference)
 */
#define IA32_VMX_EPT_VPID_CAP                                        0x0000048C

typedef union
{
  struct
  {
    /**
     * [Bit 0] When set to 1, the processor supports execute-only translations by EPT. This support allows software to
     * configure EPT paging-structure entries in which bits 1:0 are clear (indicating that data accesses are not allowed) and
     * bit 2 is set (indicating that instruction fetches are allowed).
     */
    UINT64 ExecuteOnlyPages                                        : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EXECUTE_ONLY_PAGES_BIT        0
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EXECUTE_ONLY_PAGES_MASK       0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EXECUTE_ONLY_PAGES(_)         (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bit 6] Indicates support for a page-walk length of 4.
     */
    UINT64 PageWalkLength4                                         : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PAGE_WALK_LENGTH_4_BIT        6
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PAGE_WALK_LENGTH_4_MASK       0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PAGE_WALK_LENGTH_4(_)         (((_) >> 6) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 8] When set to 1, the logical processor allows software to configure the EPT paging-structure memory type to be
     * uncacheable (UC).
     *
     * @see Vol3C[24.6.11(Extended-Page-Table Pointer (EPTP))]
     */
    UINT64 MemoryTypeUncacheable                                   : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_UNCACHEABLE_BIT   8
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_UNCACHEABLE_MASK  0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_UNCACHEABLE(_)    (((_) >> 8) & 0x01)
    UINT64 Reserved3                                               : 5;

    /**
     * [Bit 14] When set to 1, the logical processor allows software to configure the EPT paging-structure memory type to be
     * write-back (WB).
     */
    UINT64 MemoryTypeWriteBack                                     : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_WRITE_BACK_BIT    14
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_WRITE_BACK_MASK   0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_MEMORY_TYPE_WRITE_BACK(_)     (((_) >> 14) & 0x01)
    UINT64 Reserved4                                               : 1;

    /**
     * [Bit 16] When set to 1, the logical processor allows software to configure a EPT PDE to map a 2-Mbyte page (by setting
     * bit 7 in the EPT PDE).
     */
    UINT64 Pde2MbPages                                             : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDE_2MB_PAGES_BIT             16
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDE_2MB_PAGES_MASK            0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDE_2MB_PAGES(_)              (((_) >> 16) & 0x01)

    /**
     * [Bit 17] When set to 1, the logical processor allows software to configure a EPT PDPTE to map a 1-Gbyte page (by setting
     * bit 7 in the EPT PDPTE).
     */
    UINT64 Pdpte1GbPages                                           : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDPTE_1GB_PAGES_BIT           17
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDPTE_1GB_PAGES_MASK          0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_PDPTE_1GB_PAGES(_)            (((_) >> 17) & 0x01)
    UINT64 Reserved5                                               : 2;

    /**
     * [Bit 20] If bit 20 is read as 1, the INVEPT instruction is supported.
     *
     * @see Vol3C[30(VMX INSTRUCTION REFERENCE)]
     * @see Vol3C[28.3.3.1(Operations that Invalidate Cached Mappings)]
     */
    UINT64 Invept                                                  : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_BIT                    20
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_MASK                   0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT(_)                     (((_) >> 20) & 0x01)

    /**
     * [Bit 21] When set to 1, accessed and dirty flags for EPT are supported.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 EptAccessedAndDirtyFlags                                : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EPT_ACCESSED_AND_DIRTY_FLAGS_BIT 21
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EPT_ACCESSED_AND_DIRTY_FLAGS_MASK 0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_EPT_ACCESSED_AND_DIRTY_FLAGS(_) (((_) >> 21) & 0x01)

    /**
     * [Bit 22] When set to 1, the processor reports advanced VM-exit information for EPT violations. This reporting is done
     * only if this bit is read as 1.
     *
     * @see Vol3C[27.2.1(Basic VM-Exit Information)]
     */
    UINT64 AdvancedVmexitEptViolationsInformation                  : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_ADVANCED_VMEXIT_EPT_VIOLATIONS_INFORMATION_BIT 22
#define IA32_VMX_EPT_VPID_CAP_REGISTER_ADVANCED_VMEXIT_EPT_VIOLATIONS_INFORMATION_MASK 0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_ADVANCED_VMEXIT_EPT_VIOLATIONS_INFORMATION(_) (((_) >> 22) & 0x01)
    UINT64 Reserved6                                               : 2;

    /**
     * [Bit 25] When set to 1, the single-context INVEPT type is supported.
     *
     * @see Vol3C[30(VMX INSTRUCTION REFERENCE)]
     * @see Vol3C[28.3.3.1(Operations that Invalidate Cached Mappings)]
     */
    UINT64 InveptSingleContext                                     : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_SINGLE_CONTEXT_BIT     25
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_SINGLE_CONTEXT_MASK    0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_SINGLE_CONTEXT(_)      (((_) >> 25) & 0x01)

    /**
     * [Bit 26] When set to 1, the all-context INVEPT type is supported.
     *
     * @see Vol3C[30(VMX INSTRUCTION REFERENCE)]
     * @see Vol3C[28.3.3.1(Operations that Invalidate Cached Mappings)]
     */
    UINT64 InveptAllContexts                                       : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_ALL_CONTEXTS_BIT       26
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_ALL_CONTEXTS_MASK      0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVEPT_ALL_CONTEXTS(_)        (((_) >> 26) & 0x01)
    UINT64 Reserved7                                               : 5;

    /**
     * [Bit 32] When set to 1, the INVVPID instruction is supported.
     */
    UINT64 Invvpid                                                 : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_BIT                   32
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_MASK                  0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID(_)                    (((_) >> 32) & 0x01)
    UINT64 Reserved8                                               : 7;

    /**
     * [Bit 40] When set to 1, the individual-address INVVPID type is supported.
     */
    UINT64 InvvpidIndividualAddress                                : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_INDIVIDUAL_ADDRESS_BIT 40
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_INDIVIDUAL_ADDRESS_MASK 0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_INDIVIDUAL_ADDRESS(_) (((_) >> 40) & 0x01)

    /**
     * [Bit 41] When set to 1, the single-context INVVPID type is supported.
     */
    UINT64 InvvpidSingleContext                                    : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT_BIT    41
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT_MASK   0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT(_)     (((_) >> 41) & 0x01)

    /**
     * [Bit 42] When set to 1, the all-context INVVPID type is supported.
     */
    UINT64 InvvpidAllContexts                                      : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_ALL_CONTEXTS_BIT      42
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_ALL_CONTEXTS_MASK     0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_ALL_CONTEXTS(_)       (((_) >> 42) & 0x01)

    /**
     * [Bit 43] When set to 1, the single-context-retaining-globals INVVPID type is supported.
     */
    UINT64 InvvpidSingleContextRetainGlobals                       : 1;
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT_RETAIN_GLOBALS_BIT 43
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT_RETAIN_GLOBALS_MASK 0x01
#define IA32_VMX_EPT_VPID_CAP_REGISTER_INVVPID_SINGLE_CONTEXT_RETAIN_GLOBALS(_) (((_) >> 43) & 0x01)
    UINT64 Reserved9                                               : 20;
  };

  UINT64 Flags;
} IA32_VMX_EPT_VPID_CAP_REGISTER;

/**
 * @defgroup IA32_VMX_TRUE_CTLS \
 *           IA32_VMX_TRUE_(x)_CTLS
 *
 * Capability Reporting Register of Pin-Based VM-Execution Flex Controls, Primary Processor-Based VM-Execution Flex
 * Controls, VM-Exit Flex Controls and VM-Entry Flex Controls.
 *
 * @remarks If ( CPUID.01H:ECX.[5] = 1 && IA32_VMX_BASIC[55] )
 * @see Vol3D[A.3.1(Pin-Based VM-Execution Controls)]
 * @see Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)]
 * @see Vol3D[A.4(VM-EXIT CONTROLS)]
 * @see Vol3D[A.5(VM-ENTRY CONTROLS)]
 * @see Vol3D[A.3.1(Pin-Based VMExecution Controls)] (reference)
 * @see Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)] (reference)
 * @see Vol3D[A.4(VM-Exit Controls)] (reference)
 * @see Vol3D[A.5(VM-Entry Controls)] (reference)
 * @{
 */
#define IA32_VMX_TRUE_PINBASED_CTLS                                  0x0000048D
#define IA32_VMX_TRUE_PROCBASED_CTLS                                 0x0000048E
#define IA32_VMX_TRUE_EXIT_CTLS                                      0x0000048F
#define IA32_VMX_TRUE_ENTRY_CTLS                                     0x00000490
typedef struct
{
  UINT32 Allowed0Settings;
  UINT32 Allowed1Settings;
} IA32_VMX_TRUE_CTLS_REGISTER;

/**
 * @}
 */

/**
 * Capability Reporting Register of VMFunction Controls.
 *
 * @remarks If ( CPUID.01H:ECX.[5] = 1 && IA32_VMX_BASIC[55] )
 * @see Vol3D[A.11(VM FUNCTIONS)]
 * @see Vol3D[24.6.14(VM-Function Controls)] (reference)
 */
#define IA32_VMX_VMFUNC                                              0x00000491

typedef union
{
  struct
  {
    /**
     * [Bit 0] The EPTP-switching VM function changes the EPT pointer to a value chosen from the EPTP list.
     *
     * @see Vol3C[25.5.5.3(EPTP Switching)]
     */
    UINT64 EptpSwitching                                           : 1;
#define IA32_VMX_VMFUNC_REGISTER_EPTP_SWITCHING_BIT                  0
#define IA32_VMX_VMFUNC_REGISTER_EPTP_SWITCHING_MASK                 0x01
#define IA32_VMX_VMFUNC_REGISTER_EPTP_SWITCHING(_)                   (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_VMX_VMFUNC_REGISTER;

/**
 * @defgroup IA32_A_PMC \
 *           IA32_A_PMC(n)
 *
 * Full Width Writable IA32_PMC(n) Alias.
 *
 * @remarks (If CPUID.0AH: EAX[15:8] > 0) && IA32_PERF_CAPABILITIES[13] = 1
 * @{
 */
#define IA32_A_PMC0                                                  0x000004C1
#define IA32_A_PMC1                                                  0x000004C2
#define IA32_A_PMC2                                                  0x000004C3
#define IA32_A_PMC3                                                  0x000004C4
#define IA32_A_PMC4                                                  0x000004C5
#define IA32_A_PMC5                                                  0x000004C6
#define IA32_A_PMC6                                                  0x000004C7
#define IA32_A_PMC7                                                  0x000004C8
/**
 * @}
 */

/**
 * Allows software to signal some MCEs to only a single logical processor in the system.
 *
 * @remarks If IA32_MCG_CAP.LMCE_P = 1
 * @see Vol3B[15.3.1.4(IA32_MCG_EXT_CTL MSR)]
 */
#define IA32_MCG_EXT_CTL                                             0x000004D0

typedef union
{
  struct
  {
    UINT64 LmceEn                                                  : 1;
#define IA32_MCG_EXT_CTL_REGISTER_LMCE_EN_BIT                        0
#define IA32_MCG_EXT_CTL_REGISTER_LMCE_EN_MASK                       0x01
#define IA32_MCG_EXT_CTL_REGISTER_LMCE_EN(_)                         (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_MCG_EXT_CTL_REGISTER;

/**
 * @brief Status and SVN Threshold of SGX Support for ACM <b>(RO)</b>
 *
 * Intel SGX only allows launching ACMs with an Intel SGX SVN that is at the same level or higher than the expected Intel
 * SGX SVN. The expected Intel SGX SVN is specified by BIOS and locked down by the processor on the first successful
 * execution of an Intel SGX instruction that doesn't return an error code. Intel SGX provides interfaces for system
 * software to discover whether a non faulting Intel SGX instruction has been executed, and evaluate the suitability of the
 * Intel SGX SVN value of any ACM that is expected to be launched by the OS or the VMM.
 *
 * @remarks If CPUID.(EAX=07H, ECX=0H): EBX[2] = 1
 * @see Vol3D[41.11.3(Interactions with Authenticated Code Modules (ACMs))] (reference)
 */
#define IA32_SGX_SVN_STATUS                                          0x00000500

typedef union
{
  struct
  {
    /**
     * [Bit 0] - If 1, indicates that a non-faulting Intel SGX instruction has been executed, consequently, launching a
     * properly signed ACM but with Intel SGX SVN value less than the BIOS specified Intel SGX SVN threshold would lead to an
     * TXT shutdown.
     * - If 0, indicates that the processor will allow a properly signed ACM to launch irrespective of the Intel SGX SVN value
     * of the ACM.
     *
     * @see Vol3D[41.11.3(Interactions with Authenticated Code Modules (ACMs))]
     */
    UINT64 Lock                                                    : 1;
#define IA32_SGX_SVN_STATUS_REGISTER_LOCK_BIT                        0
#define IA32_SGX_SVN_STATUS_REGISTER_LOCK_MASK                       0x01
#define IA32_SGX_SVN_STATUS_REGISTER_LOCK(_)                         (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 15;

    /**
     * @brief Reflects the expected threshold of Intel SGX SVN for the SINIT ACM
     *
     * [Bits 23:16] - If CPUID.01H:ECX.SMX = 1, this field reflects the expected threshold of Intel SGX SVN for the SINIT ACM.
     * - If CPUID.01H:ECX.SMX = 0, this field is reserved (0).
     *
     * @see Vol3D[41.11.3(Interactions with Authenticated Code Modules (ACMs))]
     */
    UINT64 SgxSvnSinit                                             : 8;
#define IA32_SGX_SVN_STATUS_REGISTER_SGX_SVN_SINIT_BIT               16
#define IA32_SGX_SVN_STATUS_REGISTER_SGX_SVN_SINIT_MASK              0xFF
#define IA32_SGX_SVN_STATUS_REGISTER_SGX_SVN_SINIT(_)                (((_) >> 16) & 0xFF)
    UINT64 Reserved2                                               : 40;
  };

  UINT64 Flags;
} IA32_SGX_SVN_STATUS_REGISTER;

/**
 * Trace Output Base Register.
 *
 * @remarks If ( (CPUID.(EAX=07H, ECX=0):EBX[25] = 1) && ( (CPUID.(EAX=14H,ECX=0): ECX[0] = 1) ||
 *          (CPUID.(EAX=14H,ECX=0):ECX[2] = 1) ) )
 * @see Vol3C[35.2.7.7(IA32_RTIT_OUTPUT_BASE MSR)] (reference)
 */
#define IA32_RTIT_OUTPUT_BASE                                        0x00000560

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 7;

    /**
     * @brief Base physical address
     *
     * [Bits 47:7] The base physical address. How this address is used depends on the value of IA32_RTIT_CTL.ToPA:
     * - 0: This is the base physical address of a single, contiguous physical output region. This could be mapped to DRAM or
     * to MMIO, depending on the value. The base address should be aligned with the size of the region, such that none of the
     * 1s in the mask value overlap with 1s in the base address. If the base is not aligned, an operational error will result.
     * - 1: The base physical address of the current ToPA table. The address must be 4K aligned. Writing an address in which
     * bits 11:7 are non-zero will not cause a \#GP, but an operational error will be signaled once TraceEn is set.
     *
     * @see Vol3C[35.2.7.8(IA32_RTIT_OUTPUT_MASK_PTRS MSR)]
     * @see Vol3C[35.3.9(Operational Errors)]
     * @see Vol3C[35.2.6.2(Table of Physical Addresses (ToPA))]
     */
    UINT64 BasePhysicalAddress                                     : 41;
#define IA32_RTIT_OUTPUT_BASE_REGISTER_BASE_PHYSICAL_ADDRESS_BIT     7
#define IA32_RTIT_OUTPUT_BASE_REGISTER_BASE_PHYSICAL_ADDRESS_MASK    0x1FFFFFFFFFF
#define IA32_RTIT_OUTPUT_BASE_REGISTER_BASE_PHYSICAL_ADDRESS(_)      (((_) >> 7) & 0x1FFFFFFFFFF)
    UINT64 Reserved2                                               : 16;
  };

  UINT64 Flags;
} IA32_RTIT_OUTPUT_BASE_REGISTER;

/**
 * Trace Output Mask Pointers Register.
 *
 * @remarks If ( (CPUID.(EAX=07H, ECX=0):EBX[25] = 1) && ( (CPUID.(EAX=14H,ECX=0):ECX[0] = 1) ||
 *          (CPUID.(EAX=14H,ECX=0):ECX[2] = 1) ) )
 * @see Vol3C[35.2.7.8(IA32_RTIT_OUTPUT_MASK_PTRS MSR)] (reference)
 */
#define IA32_RTIT_OUTPUT_MASK_PTRS                                   0x00000561

typedef union
{
  struct
  {
    /**
     * [Bits 6:0] Forced to 1, writes are ignored.
     */
    UINT64 LowerMask                                               : 7;
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_LOWER_MASK_BIT           0
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_LOWER_MASK_MASK          0x7F
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_LOWER_MASK(_)            (((_) >> 0) & 0x7F)

    /**
     * @brief MaskOrTableOffset
     *
     * [Bits 31:7] The use of this field depends on the value of IA32_RTIT_CTL.ToPA:
     * - 0: This field holds bits 31:7 of the mask value for the single, contiguous physical output region. The size of this
     * field indicates that regions can be of size 128B up to 4GB. This value (combined with the lower 7 bits, which are
     * reserved to 1) will be ANDed with the OutputOffset field to determine the next write address. All 1s in this field
     * should be consecutive and starting at bit 7, otherwise the region will not be contiguous, and an operational error will
     * be signaled when TraceEn is set.
     * - 1: This field holds bits 27:3 of the offset pointer into the current ToPA table. This value can be added to the
     * IA32_RTIT_OUTPUT_BASE value to produce a pointer to the current ToPA table entry, which itself is a pointer to the
     * current output region. In this scenario, the lower 7 reserved bits are ignored. This field supports tables up to 256
     * MBytes in size.
     *
     * @see Vol3C[35.3.9(Operational Errors)]
     */
    UINT64 MaskOrTableOffset                                       : 25;
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_MASK_OR_TABLE_OFFSET_BIT 7
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_MASK_OR_TABLE_OFFSET_MASK 0x1FFFFFF
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_MASK_OR_TABLE_OFFSET(_)  (((_) >> 7) & 0x1FFFFFF)

    /**
     * @brief Output Offset
     *
     * [Bits 63:32] The use of this field depends on the value of IA32_RTIT_CTL.ToPA:
     * - 0: This is bits 31:0 of the offset pointer into the single, contiguous physical output region. This value will be
     * added to the IA32_RTIT_OUTPUT_BASE value to form the physical address at which the next byte of packet output data will
     * be written. This value must be less than or equal to the MaskOrTableOffset field, otherwise an operational error will be
     * signaled when TraceEn is set.
     * - 1: This field holds bits 31:0 of the offset pointer into the current ToPA output region. This value will be added to
     * the output region base field, found in the current ToPA table entry, to form the physical address at which the next byte
     * of trace output data will be written. This value must be less than the ToPA entry size, otherwise an operational error
     * will be signaled when TraceEn is set.
     *
     * @see Vol3C[35.3.9(Operational Errors)]
     */
    UINT64 OutputOffset                                            : 32;
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_OUTPUT_OFFSET_BIT        32
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_OUTPUT_OFFSET_MASK       0xFFFFFFFF
#define IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER_OUTPUT_OFFSET(_)         (((_) >> 32) & 0xFFFFFFFF)
  };

  UINT64 Flags;
} IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER;

/**
 * Trace Control Register.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[25] = 1)
 * @see Vol3C[35.2.7.2(IA32_RTIT_CTL MSR)] (reference)
 */
#define IA32_RTIT_CTL                                                0x00000570

typedef union
{
  struct
  {
    /**
     * @brief TraceEn
     *
     * [Bit 0] If 1, enables tracing; else tracing is disabled.
     * When this bit transitions from 1 to 0, all buffered packets are flushed out of internal buffers. A further store, fence,
     * or architecturally serializing instruction may be required to ensure that packet data can be observed at the trace
     * endpoint.
     * Note that the processor will clear this bit on \#SMI (Section) and warm reset. Other MSR bits of IA32_RTIT_CTL (and
     * other trace configuration MSRs) are not impacted by these events.
     *
     * @see Vol3C[35.2.7.3(Enabling and Disabling Packet Generation with TraceEn)]
     */
    UINT64 TraceEnabled                                            : 1;
#define IA32_RTIT_CTL_REGISTER_TRACE_ENABLED_BIT                     0
#define IA32_RTIT_CTL_REGISTER_TRACE_ENABLED_MASK                    0x01
#define IA32_RTIT_CTL_REGISTER_TRACE_ENABLED(_)                      (((_) >> 0) & 0x01)

    /**
     * @brief CYCEn
     *
     * [Bit 1] - 0: Disables CYC Packet.
     * - 1: Enables CYC Packet.
     *
     * @remarks If CPUID.(EAX=14H, ECX=0):EBX.CPSB_CAM[bit 1] = 0
     * @see Vol3C[35.4.2.14(Cycle Count (CYC) Packet)]
     */
    UINT64 CycEnabled                                              : 1;
#define IA32_RTIT_CTL_REGISTER_CYC_ENABLED_BIT                       1
#define IA32_RTIT_CTL_REGISTER_CYC_ENABLED_MASK                      0x01
#define IA32_RTIT_CTL_REGISTER_CYC_ENABLED(_)                        (((_) >> 1) & 0x01)

    /**
     * @brief OS
     *
     * [Bit 2] - 0: Packet generation is disabled when CPL = 0.
     * - 1: Packet generation may be enabled when CPL = 0.
     */
    UINT64 Os                                                      : 1;
#define IA32_RTIT_CTL_REGISTER_OS_BIT                                2
#define IA32_RTIT_CTL_REGISTER_OS_MASK                               0x01
#define IA32_RTIT_CTL_REGISTER_OS(_)                                 (((_) >> 2) & 0x01)

    /**
     * @brief User
     *
     * [Bit 3] - 0: Packet generation is disabled when CPL > 0.
     * - 1: Packet generation may be enabled when CPL > 0.
     */
    UINT64 User                                                    : 1;
#define IA32_RTIT_CTL_REGISTER_USER_BIT                              3
#define IA32_RTIT_CTL_REGISTER_USER_MASK                             0x01
#define IA32_RTIT_CTL_REGISTER_USER(_)                               (((_) >> 3) & 0x01)

    /**
     * @brief PwrEvtEn
     *
     * [Bit 4] - 0: Power Event Trace packets are disabled.
     * - 1: Power Event Trace packets are enabled.
     *
     * @see Vol3C[35.2.3(Power Event Tracing)]
     */
    UINT64 PowerEventTraceEnabled                                  : 1;
#define IA32_RTIT_CTL_REGISTER_POWER_EVENT_TRACE_ENABLED_BIT         4
#define IA32_RTIT_CTL_REGISTER_POWER_EVENT_TRACE_ENABLED_MASK        0x01
#define IA32_RTIT_CTL_REGISTER_POWER_EVENT_TRACE_ENABLED(_)          (((_) >> 4) & 0x01)

    /**
     * @brief FUPonPTW
     *
     * [Bit 5] - 0: PTW packets are not followed by FUPs.
     * - 1: PTW packets are followed by FUPs.
     */
    UINT64 FupOnPtw                                                : 1;
#define IA32_RTIT_CTL_REGISTER_FUP_ON_PTW_BIT                        5
#define IA32_RTIT_CTL_REGISTER_FUP_ON_PTW_MASK                       0x01
#define IA32_RTIT_CTL_REGISTER_FUP_ON_PTW(_)                         (((_) >> 5) & 0x01)

    /**
     * @brief FabricEn
     *
     * [Bit 6] - 0: Trace output is directed to the memory subsystem, mechanism depends on IA32_RTIT_CTL.ToPA.
     * - 1: Trace output is directed to the trace transport subsystem, IA32_RTIT_CTL.ToPA is ignored.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):ECX[3] = 1) Reserved if CPUID.(EAX=14H, ECX=0):ECX[bit 3] = 0
     */
    UINT64 FabricEnabled                                           : 1;
#define IA32_RTIT_CTL_REGISTER_FABRIC_ENABLED_BIT                    6
#define IA32_RTIT_CTL_REGISTER_FABRIC_ENABLED_MASK                   0x01
#define IA32_RTIT_CTL_REGISTER_FABRIC_ENABLED(_)                     (((_) >> 6) & 0x01)

    /**
     * @brief CR3 filter
     *
     * [Bit 7] - 0: Disables CR3 filtering.
     * - 1: Enables CR3 filtering.
     */
    UINT64 Cr3Filter                                               : 1;
#define IA32_RTIT_CTL_REGISTER_CR3_FILTER_BIT                        7
#define IA32_RTIT_CTL_REGISTER_CR3_FILTER_MASK                       0x01
#define IA32_RTIT_CTL_REGISTER_CR3_FILTER(_)                         (((_) >> 7) & 0x01)

    /**
     * @brief ToPA
     *
     * [Bit 8] - 0: Single-range output scheme enabled.
     * - 1: ToPA output scheme enabled.
     *
     * @remarks 0: If CPUID.(EAX=14H, ECX=0):ECX.SNGLRGNOUT[bit 2] = 1 and IA32_RTIT_CTL.FabricEn=0 1: If CPUID.(EAX=14H,
     *          ECX=0):ECX.TOPA[bit 0] = 1, and IA32_RTIT_CTL.FabricEn=0
     *          WRMSR to IA32_RTIT_CTL that sets TraceEn but clears this bit and FabricEn would cause \#GP: If CPUID.(EAX=14H,
     *          ECX=0):ECX.SNGLRGNOUT[bit 2] = 0 WRMSR to IA32_RTIT_CTL that sets this bit causes \#GP: If CPUID.(EAX=14H,
     *          ECX=0):ECX.TOPA[bit 0] = 0
     * @see Vol3C[35.2.6.2(Table of Physical Addresses (ToPA))]
     */
    UINT64 Topa                                                    : 1;
#define IA32_RTIT_CTL_REGISTER_TOPA_BIT                              8
#define IA32_RTIT_CTL_REGISTER_TOPA_MASK                             0x01
#define IA32_RTIT_CTL_REGISTER_TOPA(_)                               (((_) >> 8) & 0x01)

    /**
     * @brief MTCEn
     *
     * [Bit 9] - 0: Disables MTC Packet.
     * - 1: Enables MTC Packet.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[3] = 1) Reserved if CPUID.(EAX=14H, ECX=0):EBX.MTC[bit 3] = 0
     * @see Vol3C[35.4.2.16(Overflow (OVF) Packet)]
     */
    UINT64 MtcEnabled                                              : 1;
#define IA32_RTIT_CTL_REGISTER_MTC_ENABLED_BIT                       9
#define IA32_RTIT_CTL_REGISTER_MTC_ENABLED_MASK                      0x01
#define IA32_RTIT_CTL_REGISTER_MTC_ENABLED(_)                        (((_) >> 9) & 0x01)

    /**
     * @brief TSCEn
     *
     * [Bit 10] - 0: Disable TSC packets.
     * - 1: Enable TSC packets.
     *
     * @see Vol3C[35.4.2.11(Timestamp Counter (TSC) Packet)]
     */
    UINT64 TscEnabled                                              : 1;
#define IA32_RTIT_CTL_REGISTER_TSC_ENABLED_BIT                       10
#define IA32_RTIT_CTL_REGISTER_TSC_ENABLED_MASK                      0x01
#define IA32_RTIT_CTL_REGISTER_TSC_ENABLED(_)                        (((_) >> 10) & 0x01)

    /**
     * @brief DisRETC
     *
     * [Bit 11] - 0: Enable RET compression.
     * - 1: Disable RET compression.
     *
     * @see Vol3C[35.2.1.2(Indirect Transfer COFI)]
     */
    UINT64 RetCompressionDisabled                                  : 1;
#define IA32_RTIT_CTL_REGISTER_RET_COMPRESSION_DISABLED_BIT          11
#define IA32_RTIT_CTL_REGISTER_RET_COMPRESSION_DISABLED_MASK         0x01
#define IA32_RTIT_CTL_REGISTER_RET_COMPRESSION_DISABLED(_)           (((_) >> 11) & 0x01)

    /**
     * @brief PTWEn
     *
     * [Bit 12] - 0: PTWRITE packet generation disabled.
     * - 1: PTWRITE packet generation enabled.
     */
    UINT64 PtwEnabled                                              : 1;
#define IA32_RTIT_CTL_REGISTER_PTW_ENABLED_BIT                       12
#define IA32_RTIT_CTL_REGISTER_PTW_ENABLED_MASK                      0x01
#define IA32_RTIT_CTL_REGISTER_PTW_ENABLED(_)                        (((_) >> 12) & 0x01)

    /**
     * @brief BranchEn
     *
     * [Bit 13] - 0: Disable COFI-based packets.
     * - 1: Enable COFI-based packets: FUP, TIP, TIP.PGE, TIP.PGD, TNT, MODE.Exec, MODE.TSX.
     *
     * @see Vol3C[35.2.5.4(Branch Enable (BranchEn))]
     */
    UINT64 BranchEnabled                                           : 1;
#define IA32_RTIT_CTL_REGISTER_BRANCH_ENABLED_BIT                    13
#define IA32_RTIT_CTL_REGISTER_BRANCH_ENABLED_MASK                   0x01
#define IA32_RTIT_CTL_REGISTER_BRANCH_ENABLED(_)                     (((_) >> 13) & 0x01)

    /**
     * @brief MTCFreq
     *
     * [Bits 17:14] Defines MTC packet Frequency, which is based on the core crystal clock, or Always Running Timer (ART). MTC
     * will be sent each time the selected ART bit toggles. The following Encodings are defined:
     * 0: ART(0), 1: ART(1), 2: ART(2), 3: ART(3), 4: ART(4), 5: ART(5), 6: ART(6), 7: ART(7), 8: ART(8), 9: ART(9), 10:
     * ART(10), 11: ART(11), 12: ART(12), 13: ART(13), 14: ART(14), 15: ART(15)
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[3] = 1) Reserved if CPUID.(EAX=14H, ECX=0):EBX.MTC[bit 3] = 0
     * @see Vol3C[35.3.1(Detection of Intel Processor Trace and Capability Enumeration)]
     */
    UINT64 MtcFrequency                                            : 4;
#define IA32_RTIT_CTL_REGISTER_MTC_FREQUENCY_BIT                     14
#define IA32_RTIT_CTL_REGISTER_MTC_FREQUENCY_MASK                    0x0F
#define IA32_RTIT_CTL_REGISTER_MTC_FREQUENCY(_)                      (((_) >> 14) & 0x0F)
    UINT64 Reserved1                                               : 1;

    /**
     * @brief CYCThresh
     *
     * [Bits 22:19] CYC packet threshold. CYC packets will be sent with the first eligible packet after N cycles have passed
     * since the last CYC packet. If CycThresh is 0 then N=0, otherwise N is defined as 2(CycThresh-1). The following Encodings
     * are defined:
     * 0: 0, 1: 1, 2: 2, 3: 4, 4: 8, 5: 16, 6: 32, 7: 64, 8: 128, 9: 256, 10: 512, 11: 1024, 12: 2048, 13: 4096, 14: 8192, 15:
     * 16384
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[1] = 1) Reserved if CPUID.(EAX=14H, ECX=0):EBX.CPSB_CAM[bit 1] = 0
     * @see Vol3C[35.3.6(Cycle-Accurate Mode)]
     * @see Vol3C[35.3.1(Detection of Intel Processor Trace and Capability Enumeration)]
     */
    UINT64 CycThreshold                                            : 4;
#define IA32_RTIT_CTL_REGISTER_CYC_THRESHOLD_BIT                     19
#define IA32_RTIT_CTL_REGISTER_CYC_THRESHOLD_MASK                    0x0F
#define IA32_RTIT_CTL_REGISTER_CYC_THRESHOLD(_)                      (((_) >> 19) & 0x0F)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief PSBFreq
     *
     * [Bits 27:24] Indicates the frequency of PSB packets. PSB packet frequency is based on the number of Intel PT packet
     * bytes output, so this field allows the user to determine the increment of IA32_IA32_RTIT_STATUS.PacketByteCnt that
     * should cause a PSB to be generated. Note that PSB insertion is not precise, but the average output bytes per PSB should
     * approximate the SW selected period. The following Encodings are defined:
     * 0: 2K, 1: 4K, 2: 8K, 3: 16K, 4: 32K, 5: 64K, 6: 128K, 7: 256K, 8: 512K, 9: 1M, 10: 2M, 11: 4M, 12: 8M, 13: 16M, 14: 32M,
     * 15: 64M
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[1] = 1) Reserved if CPUID.(EAX=14H, ECX=0):EBX.CPSB_CAM[bit 1] = 0
     * @see Vol3C[35.3.1(Detection of Intel Processor Trace and Capability Enumeration)]
     */
    UINT64 PsbFrequency                                            : 4;
#define IA32_RTIT_CTL_REGISTER_PSB_FREQUENCY_BIT                     24
#define IA32_RTIT_CTL_REGISTER_PSB_FREQUENCY_MASK                    0x0F
#define IA32_RTIT_CTL_REGISTER_PSB_FREQUENCY(_)                      (((_) >> 24) & 0x0F)
    UINT64 Reserved3                                               : 4;

    /**
     * @brief ADDR0_CFG
     *
     * [Bits 35:32] Configures the base/limit register pair IA32_RTIT_ADDR0_A/B based on the following encodings:
     * - 0: ADDR0 range unused.
     * - 1: The [IA32_RTIT_ADDR0_A..IA32_RTIT_ADDR0_B] range defines a FilterEn range. FilterEn will only be set when the IP is
     * within this range, though other FilterEn ranges can additionally be used.
     * - 2: The [IA32_RTIT_ADDR0_A..IA32_RTIT_ADDR0_B] range defines a TraceStop range. TraceStop will be asserted if code
     * branches into this range.
     * - 3..15: Reserved (\#GP).
     *
     * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 0) Reserved if CPUID.(EAX=14H, ECX=1):EBX.RANGECNT[2:0] >= 0
     * @see Vol3C[35.2.4.3(Filtering by IP)]
     * @see Vol3C[35.4.2.10(Core:Bus Ratio (CBR) Packet)]
     */
    UINT64 Addr0Cfg                                                : 4;
#define IA32_RTIT_CTL_REGISTER_ADDR0_CFG_BIT                         32
#define IA32_RTIT_CTL_REGISTER_ADDR0_CFG_MASK                        0x0F
#define IA32_RTIT_CTL_REGISTER_ADDR0_CFG(_)                          (((_) >> 32) & 0x0F)

    /**
     * @brief ADDR1_CFG
     *
     * [Bits 39:36] Configures the base/limit register pair IA32_RTIT_ADDR1_A/B based on the following encodings:
     * - 0: ADDR1 range unused.
     * - 1: The [IA32_RTIT_ADDR1_A..IA32_RTIT_ADDR1_B] range defines a FilterEn range. FilterEn will only be set when the IP is
     * within this range, though other FilterEn ranges can additionally be used.
     * - 2: The [IA32_RTIT_ADDR1_A..IA32_RTIT_ADDR1_B] range defines a TraceStop range. TraceStop will be asserted if code
     * branches into this range.
     * - 3..15: Reserved (\#GP).
     *
     * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 1) Reserved if CPUID.(EAX=14H, ECX=1):EBX.RANGECNT[2:0] < 2
     * @see Vol3C[35.2.4.3(Filtering by IP)]
     * @see Vol3C[35.4.2.10(Core:Bus Ratio (CBR) Packet)]
     */
    UINT64 Addr1Cfg                                                : 4;
#define IA32_RTIT_CTL_REGISTER_ADDR1_CFG_BIT                         36
#define IA32_RTIT_CTL_REGISTER_ADDR1_CFG_MASK                        0x0F
#define IA32_RTIT_CTL_REGISTER_ADDR1_CFG(_)                          (((_) >> 36) & 0x0F)

    /**
     * @brief ADDR2_CFG
     *
     * [Bits 43:40] Configures the base/limit register pair IA32_RTIT_ADDR2_A/B based on the following encodings:
     * - 0: ADDR2 range unused.
     * - 1: The [IA32_RTIT_ADDR2_A..IA32_RTIT_ADDR2_B] range defines a FilterEn range. FilterEn will only be set when the IP is
     * within this range, though other FilterEn ranges can additionally be used.
     * - 2: The [IA32_RTIT_ADDR2_A..IA32_RTIT_ADDR2_B] range defines a TraceStop range. TraceStop will be asserted if code
     * branches into this range.
     * - 3..15: Reserved (\#GP).
     *
     * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 2) Reserved if CPUID.(EAX=14H, ECX=1):EBX.RANGECNT[2:0] < 3
     * @see Vol3C[35.2.4.3(Filtering by IP)]
     * @see Vol3C[35.4.2.10(Core:Bus Ratio (CBR) Packet)]
     */
    UINT64 Addr2Cfg                                                : 4;
#define IA32_RTIT_CTL_REGISTER_ADDR2_CFG_BIT                         40
#define IA32_RTIT_CTL_REGISTER_ADDR2_CFG_MASK                        0x0F
#define IA32_RTIT_CTL_REGISTER_ADDR2_CFG(_)                          (((_) >> 40) & 0x0F)

    /**
     * @brief ADDR3_CFG
     *
     * [Bits 47:44] Configures the base/limit register pair IA32_RTIT_ADDR3_A/B based on the following encodings:
     * - 0: ADDR3 range unused.
     * - 1: The [IA32_RTIT_ADDR3_A..IA32_RTIT_ADDR3_B] range defines a FilterEn range. FilterEn will only be set when the IP is
     * within this range, though other FilterEn ranges can additionally be used.
     * - 2: The [IA32_RTIT_ADDR3_A..IA32_RTIT_ADDR3_B] range defines a TraceStop range. TraceStop will be asserted if code
     * branches into this range.
     * - 3..15: Reserved (\#GP).
     *
     * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > 3) Reserved if CPUID.(EAX=14H, ECX=1):EBX.RANGECNT[2:0] < 4
     * @see Vol3C[35.2.4.3(Filtering by IP)]
     * @see Vol3C[35.4.2.10(Core:Bus Ratio (CBR) Packet)]
     */
    UINT64 Addr3Cfg                                                : 4;
#define IA32_RTIT_CTL_REGISTER_ADDR3_CFG_BIT                         44
#define IA32_RTIT_CTL_REGISTER_ADDR3_CFG_MASK                        0x0F
#define IA32_RTIT_CTL_REGISTER_ADDR3_CFG(_)                          (((_) >> 44) & 0x0F)
    UINT64 Reserved4                                               : 8;

    /**
     * @brief InjectPsbPmiOnEnable
     *
     * [Bit 56] - 1: Enables use of IA32_RTIT_STATUS bits PendPSB[6] and PendTopaPMI[7].
     * - 0: IA32_RTIT_STATUS bits 6 and 7 are ignored.
     *
     * @remarks Reserved if CPUID.(EAX=14H, ECX=0):EBX.INJECTPSBPMI[6] = 0
     * @see Vol3C[35.2.7.4(IA32_RTIT_STATUS MSR)]
     */
    UINT64 InjectPsbPmiOnEnable                                    : 1;
#define IA32_RTIT_CTL_REGISTER_INJECT_PSB_PMI_ON_ENABLE_BIT          56
#define IA32_RTIT_CTL_REGISTER_INJECT_PSB_PMI_ON_ENABLE_MASK         0x01
#define IA32_RTIT_CTL_REGISTER_INJECT_PSB_PMI_ON_ENABLE(_)           (((_) >> 56) & 0x01)
    UINT64 Reserved5                                               : 7;
  };

  UINT64 Flags;
} IA32_RTIT_CTL_REGISTER;

/**
 * Tracing Status Register.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[25] = 1)
 */
#define IA32_RTIT_STATUS                                             0x00000571

typedef union
{
  struct
  {
    /**
     * @brief FilterEn (writes ignored)
     *
     * [Bit 0] This bit is written by the processor, and indicates that tracing is allowed for the current IP. Writes are
     * ignored.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[2] = 1)
     * @see Vol3C[35.2.5.5(Filter Enable (FilterEn))]
     */
    UINT64 FilterEnabled                                           : 1;
#define IA32_RTIT_STATUS_REGISTER_FILTER_ENABLED_BIT                 0
#define IA32_RTIT_STATUS_REGISTER_FILTER_ENABLED_MASK                0x01
#define IA32_RTIT_STATUS_REGISTER_FILTER_ENABLED(_)                  (((_) >> 0) & 0x01)

    /**
     * @brief ContexEn (writes ignored)
     *
     * [Bit 1] The processor sets this bit to indicate that tracing is allowed for the current context. Writes are ignored.
     *
     * @see Vol3C[35.2.5.3(Context Enable (ContextEn))]
     */
    UINT64 ContextEnabled                                          : 1;
#define IA32_RTIT_STATUS_REGISTER_CONTEXT_ENABLED_BIT                1
#define IA32_RTIT_STATUS_REGISTER_CONTEXT_ENABLED_MASK               0x01
#define IA32_RTIT_STATUS_REGISTER_CONTEXT_ENABLED(_)                 (((_) >> 1) & 0x01)

    /**
     * @brief TriggerEn (writes ignored)
     *
     * [Bit 2] The processor sets this bit to indicate that tracing is enabled. Writes are ignored.
     *
     * @see Vol3C[35.2.5.2(Trigger Enable (TriggerEn))]
     */
    UINT64 TriggerEnabled                                          : 1;
#define IA32_RTIT_STATUS_REGISTER_TRIGGER_ENABLED_BIT                2
#define IA32_RTIT_STATUS_REGISTER_TRIGGER_ENABLED_MASK               0x01
#define IA32_RTIT_STATUS_REGISTER_TRIGGER_ENABLED(_)                 (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * @brief Error
     *
     * [Bit 4] The processor sets this bit to indicate that an operational error has been encountered. When this bit is set,
     * TriggerEn is cleared to 0 and packet generation is disabled.
     * When TraceEn is cleared, software can write this bit. Once it is set, only software can clear it. It is not recommended
     * that software ever set this bit, except in cases where it is restoring a prior saved state.
     *
     * @see Vol3C[35.2.6.2(Table of Physical Addresses (ToPA) | ToPA Errors)]
     */
    UINT64 Error                                                   : 1;
#define IA32_RTIT_STATUS_REGISTER_ERROR_BIT                          4
#define IA32_RTIT_STATUS_REGISTER_ERROR_MASK                         0x01
#define IA32_RTIT_STATUS_REGISTER_ERROR(_)                           (((_) >> 4) & 0x01)

    /**
     * @brief Stopped
     *
     * [Bit 5] The processor sets this bit to indicate that a ToPA Stop condition has been encountered. When this bit is set,
     * TriggerEn is cleared to 0 and packet generation is disabled.
     * When TraceEn is cleared, software can write this bit. Once it is set, only software can clear it. It is not recommended
     * that software ever set this bit, except in cases where it is restoring a prior saved state.
     *
     * @see Vol3C[35.2.6.2(Table of Physical Addresses (ToPA) | ToPA STOP)]
     */
    UINT64 Stopped                                                 : 1;
#define IA32_RTIT_STATUS_REGISTER_STOPPED_BIT                        5
#define IA32_RTIT_STATUS_REGISTER_STOPPED_MASK                       0x01
#define IA32_RTIT_STATUS_REGISTER_STOPPED(_)                         (((_) >> 5) & 0x01)

    /**
     * @brief Pend PSB
     *
     * [Bit 6] If IA32_RTIT_CTL.InjectPsbPmiOnEnable[56] = 1, the processor sets this bit when the threshold for a PSB+ to be
     * inserted has been reached. The processor will clear this bit when the PSB+ has been inserted into the trace. If PendPSB
     * = 1 and InjectPsbPmiOnEnable = 1 when IA32_RTIT_CTL.TraceEn[0] transitions from 0 to 1, a PSB+ will be inserted into the
     * trace.
     *
     * @remarks If CPUID.(EAX=14H, ECX=0):EBX.INJECTPSBPMI[6] = 1
     */
    UINT64 PendPsb                                                 : 1;
#define IA32_RTIT_STATUS_REGISTER_PEND_PSB_BIT                       6
#define IA32_RTIT_STATUS_REGISTER_PEND_PSB_MASK                      0x01
#define IA32_RTIT_STATUS_REGISTER_PEND_PSB(_)                        (((_) >> 6) & 0x01)

    /**
     * @brief Pend ToPA PMI
     *
     * [Bit 7] If IA32_RTIT_CTL.InjectPsbPmiOnEnable[56] = 1, the processor sets this bit when the threshold for a ToPA PMI to
     * be inserted has been reached. Software should clear this bit once the ToPA PMI has been handled. If PendTopaPMI = 1 and
     * InjectPsbPmiOnEnable = 1 when IA32_RTIT_CTL.TraceEn[0] transitions from 0 to 1, a PMI will be pended.
     *
     * @remarks If CPUID.(EAX=14H, ECX=0):EBX.INJECTPSBPMI[6] = 1
     * @see Vol3C[35.2.6.2(Table of Physical Addresses (ToPA) | ToPA PMI)]
     */
    UINT64 PendTopaPmi                                             : 1;
#define IA32_RTIT_STATUS_REGISTER_PEND_TOPA_PMI_BIT                  7
#define IA32_RTIT_STATUS_REGISTER_PEND_TOPA_PMI_MASK                 0x01
#define IA32_RTIT_STATUS_REGISTER_PEND_TOPA_PMI(_)                   (((_) >> 7) & 0x01)
    UINT64 Reserved2                                               : 24;

    /**
     * @brief PacketByteCnt
     *
     * [Bits 48:32] This field is written by the processor, and holds a count of packet bytes that have been sent out. The
     * processor also uses this field to determine when the next PSB packet should be inserted. Note that the processor may
     * clear or modify this field at any time while IA32_RTIT_CTL.TraceEn=1. It will have a stable value when
     * IA32_RTIT_CTL.TraceEn=0.
     *
     * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[1] > 3)
     * @see Vol3C[35.4.2.17(Packet Stream Boundary (PSB) Packet)]
     */
    UINT64 PacketByteCount                                         : 17;
#define IA32_RTIT_STATUS_REGISTER_PACKET_BYTE_COUNT_BIT              32
#define IA32_RTIT_STATUS_REGISTER_PACKET_BYTE_COUNT_MASK             0x1FFFF
#define IA32_RTIT_STATUS_REGISTER_PACKET_BYTE_COUNT(_)               (((_) >> 32) & 0x1FFFF)
    UINT64 Reserved3                                               : 15;
  };

  UINT64 Flags;
} IA32_RTIT_STATUS_REGISTER;

/**
 * @brief Trace Filter CR3 Match Register <b>(R/W)</b>
 *
 * The IA32_RTIT_CR3_MATCH register is compared against CR3 when IA32_RTIT_CTL.CR3Filter is 1. Bits 63:5 hold the CR3
 * address value to match, bits 4:0 are reserved to 0.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=0):EBX[25] = 1)
 * @see Vol3C[35.2.4.2(Filtering by CR3)]
 * @see Vol3C[35.2.7.6(IA32_RTIT_CR3_MATCH MSR)] (reference)
 */
#define IA32_RTIT_CR3_MATCH                                          0x00000572

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 5;

    /**
     * [Bits 63:5] CR3[63:5] value to match.
     */
    UINT64 Cr3ValueToMatch                                         : 59;
#define IA32_RTIT_CR3_MATCH_REGISTER_CR3_VALUE_TO_MATCH_BIT          5
#define IA32_RTIT_CR3_MATCH_REGISTER_CR3_VALUE_TO_MATCH_MASK         0x7FFFFFFFFFFFFFF
#define IA32_RTIT_CR3_MATCH_REGISTER_CR3_VALUE_TO_MATCH(_)           (((_) >> 5) & 0x7FFFFFFFFFFFFFF)
  };

  UINT64 Flags;
} IA32_RTIT_CR3_MATCH_REGISTER;

/**
 * @defgroup IA32_RTIT_ADDR \
 *           IA32_RTIT_ADDR(x)
 *
 * The role of the IA32_RTIT_ADDRn_A/B register pairs, for each n, is determined by the corresponding ADDRn_CFG fields in
 * IA32_RTIT_CTL. The number of these register pairs is enumerated by CPUID.(EAX=14H, ECX=1):EAX.RANGECNT[2:0].
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @see Vol3C[35.2.7.2(IA32_RTIT_CTL MSR)]
 * @see Vol3C[35.2.7.5(IA32_RTIT_ADDRn_A and IA32_RTIT_ADDRn_B MSRs)] (reference)
 * @{
 */
/**
 * @defgroup IA32_RTIT_ADDR_A \
 *           IA32_RTIT_ADDR(n)_A
 *
 * Region n Start Address.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @{
 */
#define IA32_RTIT_ADDR0_A                                            0x00000580
#define IA32_RTIT_ADDR1_A                                            0x00000582
#define IA32_RTIT_ADDR2_A                                            0x00000584
#define IA32_RTIT_ADDR3_A                                            0x00000586
/**
 * @}
 */

/**
 * @defgroup IA32_RTIT_ADDR_B \
 *           IA32_RTIT_ADDR(n)_B
 *
 * Region n End Address.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @{
 */
#define IA32_RTIT_ADDR0_B                                            0x00000581
#define IA32_RTIT_ADDR1_B                                            0x00000583
#define IA32_RTIT_ADDR2_B                                            0x00000585
#define IA32_RTIT_ADDR3_B                                            0x00000587
/**
 * @}
 */

typedef union
{
  struct
  {
    /**
     * [Bits 47:0] Virtual Address.
     */
    UINT64 VirtualAddress                                          : 48;
#define IA32_RTIT_ADDR_REGISTER_VIRTUAL_ADDRESS_BIT                  0
#define IA32_RTIT_ADDR_REGISTER_VIRTUAL_ADDRESS_MASK                 0xFFFFFFFFFFFF
#define IA32_RTIT_ADDR_REGISTER_VIRTUAL_ADDRESS(_)                   (((_) >> 0) & 0xFFFFFFFFFFFF)

    /**
     * [Bits 63:48] SignExt_VA.
     */
    UINT64 SignExtVa                                               : 16;
#define IA32_RTIT_ADDR_REGISTER_SIGN_EXT_VA_BIT                      48
#define IA32_RTIT_ADDR_REGISTER_SIGN_EXT_VA_MASK                     0xFFFF
#define IA32_RTIT_ADDR_REGISTER_SIGN_EXT_VA(_)                       (((_) >> 48) & 0xFFFF)
  };

  UINT64 Flags;
} IA32_RTIT_ADDR_REGISTER;

/**
 * @}
 */

/**
 * DS Save Area. Points to the linear address of the first byte of the DS buffer management area, which is used to manage
 * the BTS and PEBS buffers.
 * Returns:
 * - [63:0] The linear address of the first byte of the DS buffer management area, if IA-32e mode is active.
 * - [31:0] The linear address of the first byte of the DS buffer management area, if not in IA-32e mode.
 * - [63:32] Reserved if not in IA-32e mode.
 *
 * @remarks If CPUID.01H:EDX.DS[21] = 1
 * @see Vol3B[18.6.3.4(Debug Store (DS) Mechanism)]
 */
#define IA32_DS_AREA                                                 0x00000600

/**
 * TSC Target of Local APIC's TSC Deadline Mode.
 *
 * @remarks If CPUID.01H:ECX.[24] = 1
 */
#define IA32_TSC_DEADLINE                                            0x000006E0

/**
 * Enable/disable HWP.
 *
 * @remarks If CPUID.06H:EAX.[7] = 1
 */
#define IA32_PM_ENABLE                                               0x00000770

typedef union
{
  struct
  {
    /**
     * [Bit 0] HWP_ENABLE.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.2(Enabling HWP)]
     */
    UINT64 HwpEnable                                               : 1;
#define IA32_PM_ENABLE_REGISTER_HWP_ENABLE_BIT                       0
#define IA32_PM_ENABLE_REGISTER_HWP_ENABLE_MASK                      0x01
#define IA32_PM_ENABLE_REGISTER_HWP_ENABLE(_)                        (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_PM_ENABLE_REGISTER;

/**
 * HWP Performance Range Enumeration.
 *
 * @remarks If CPUID.06H:EAX.[7] = 1
 */
#define IA32_HWP_CAPABILITIES                                        0x00000771

typedef union
{
  struct
  {
    /**
     * [Bits 7:0] Highest_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.3(HWP Performance Range and Dynamic Capabilities)]
     */
    UINT64 HighestPerformance                                      : 8;
#define IA32_HWP_CAPABILITIES_REGISTER_HIGHEST_PERFORMANCE_BIT       0
#define IA32_HWP_CAPABILITIES_REGISTER_HIGHEST_PERFORMANCE_MASK      0xFF
#define IA32_HWP_CAPABILITIES_REGISTER_HIGHEST_PERFORMANCE(_)        (((_) >> 0) & 0xFF)

    /**
     * [Bits 15:8] Guaranteed_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.3(HWP Performance Range and Dynamic Capabilities)]
     */
    UINT64 GuaranteedPerformance                                   : 8;
#define IA32_HWP_CAPABILITIES_REGISTER_GUARANTEED_PERFORMANCE_BIT    8
#define IA32_HWP_CAPABILITIES_REGISTER_GUARANTEED_PERFORMANCE_MASK   0xFF
#define IA32_HWP_CAPABILITIES_REGISTER_GUARANTEED_PERFORMANCE(_)     (((_) >> 8) & 0xFF)

    /**
     * [Bits 23:16] Most_Efficient_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.3(HWP Performance Range and Dynamic Capabilities)]
     */
    UINT64 MostEfficientPerformance                                : 8;
#define IA32_HWP_CAPABILITIES_REGISTER_MOST_EFFICIENT_PERFORMANCE_BIT 16
#define IA32_HWP_CAPABILITIES_REGISTER_MOST_EFFICIENT_PERFORMANCE_MASK 0xFF
#define IA32_HWP_CAPABILITIES_REGISTER_MOST_EFFICIENT_PERFORMANCE(_) (((_) >> 16) & 0xFF)

    /**
     * [Bits 31:24] Lowest_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.3(HWP Performance Range and Dynamic Capabilities)]
     */
    UINT64 LowestPerformance                                       : 8;
#define IA32_HWP_CAPABILITIES_REGISTER_LOWEST_PERFORMANCE_BIT        24
#define IA32_HWP_CAPABILITIES_REGISTER_LOWEST_PERFORMANCE_MASK       0xFF
#define IA32_HWP_CAPABILITIES_REGISTER_LOWEST_PERFORMANCE(_)         (((_) >> 24) & 0xFF)
    UINT64 Reserved1                                               : 32;
  };

  UINT64 Flags;
} IA32_HWP_CAPABILITIES_REGISTER;

/**
 * Power Management Control Hints for All Logical Processors in a Package.
 *
 * @remarks If CPUID.06H:EAX.[11] = 1
 */
#define IA32_HWP_REQUEST_PKG                                         0x00000772

typedef union
{
  struct
  {
    /**
     * [Bits 7:0] Minimum_Performance.
     *
     * @remarks If CPUID.06H:EAX.[11] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 MinimumPerformance                                      : 8;
#define IA32_HWP_REQUEST_PKG_REGISTER_MINIMUM_PERFORMANCE_BIT        0
#define IA32_HWP_REQUEST_PKG_REGISTER_MINIMUM_PERFORMANCE_MASK       0xFF
#define IA32_HWP_REQUEST_PKG_REGISTER_MINIMUM_PERFORMANCE(_)         (((_) >> 0) & 0xFF)

    /**
     * [Bits 15:8] Maximum_Performance.
     *
     * @remarks If CPUID.06H:EAX.[11] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 MaximumPerformance                                      : 8;
#define IA32_HWP_REQUEST_PKG_REGISTER_MAXIMUM_PERFORMANCE_BIT        8
#define IA32_HWP_REQUEST_PKG_REGISTER_MAXIMUM_PERFORMANCE_MASK       0xFF
#define IA32_HWP_REQUEST_PKG_REGISTER_MAXIMUM_PERFORMANCE(_)         (((_) >> 8) & 0xFF)

    /**
     * [Bits 23:16] Desired_Performance.
     *
     * @remarks If CPUID.06H:EAX.[11] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 DesiredPerformance                                      : 8;
#define IA32_HWP_REQUEST_PKG_REGISTER_DESIRED_PERFORMANCE_BIT        16
#define IA32_HWP_REQUEST_PKG_REGISTER_DESIRED_PERFORMANCE_MASK       0xFF
#define IA32_HWP_REQUEST_PKG_REGISTER_DESIRED_PERFORMANCE(_)         (((_) >> 16) & 0xFF)

    /**
     * [Bits 31:24] Energy_Performance_Preference.
     *
     * @remarks If CPUID.06H:EAX.[11] = 1 && CPUID.06H:EAX.[10] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 EnergyPerformancePreference                             : 8;
#define IA32_HWP_REQUEST_PKG_REGISTER_ENERGY_PERFORMANCE_PREFERENCE_BIT 24
#define IA32_HWP_REQUEST_PKG_REGISTER_ENERGY_PERFORMANCE_PREFERENCE_MASK 0xFF
#define IA32_HWP_REQUEST_PKG_REGISTER_ENERGY_PERFORMANCE_PREFERENCE(_) (((_) >> 24) & 0xFF)

    /**
     * [Bits 41:32] Activity_Window.
     *
     * @remarks If CPUID.06H:EAX.[11] = 1 && CPUID.06H:EAX.[9] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 ActivityWindow                                          : 10;
#define IA32_HWP_REQUEST_PKG_REGISTER_ACTIVITY_WINDOW_BIT            32
#define IA32_HWP_REQUEST_PKG_REGISTER_ACTIVITY_WINDOW_MASK           0x3FF
#define IA32_HWP_REQUEST_PKG_REGISTER_ACTIVITY_WINDOW(_)             (((_) >> 32) & 0x3FF)
    UINT64 Reserved1                                               : 22;
  };

  UINT64 Flags;
} IA32_HWP_REQUEST_PKG_REGISTER;

/**
 * Control HWP Native Interrupts.
 *
 * @remarks If CPUID.06H:EAX.[8] = 1
 */
#define IA32_HWP_INTERRUPT                                           0x00000773

typedef union
{
  struct
  {
    /**
     * [Bit 0] EN_Guaranteed_Performance_Change.
     *
     * @remarks If CPUID.06H:EAX.[8] = 1
     * @see Vol3B[14.4.6(HWP Notifications)]
     */
    UINT64 EnGuaranteedPerformanceChange                           : 1;
#define IA32_HWP_INTERRUPT_REGISTER_EN_GUARANTEED_PERFORMANCE_CHANGE_BIT 0
#define IA32_HWP_INTERRUPT_REGISTER_EN_GUARANTEED_PERFORMANCE_CHANGE_MASK 0x01
#define IA32_HWP_INTERRUPT_REGISTER_EN_GUARANTEED_PERFORMANCE_CHANGE(_) (((_) >> 0) & 0x01)

    /**
     * [Bit 1] EN_Excursion_Minimum.
     *
     * @remarks If CPUID.06H:EAX.[8] = 1
     * @see Vol3B[14.4.6(HWP Notifications)]
     */
    UINT64 EnExcursionMinimum                                      : 1;
#define IA32_HWP_INTERRUPT_REGISTER_EN_EXCURSION_MINIMUM_BIT         1
#define IA32_HWP_INTERRUPT_REGISTER_EN_EXCURSION_MINIMUM_MASK        0x01
#define IA32_HWP_INTERRUPT_REGISTER_EN_EXCURSION_MINIMUM(_)          (((_) >> 1) & 0x01)
    UINT64 Reserved1                                               : 62;
  };

  UINT64 Flags;
} IA32_HWP_INTERRUPT_REGISTER;

/**
 * Power Management Control Hints to a Logical Processor.
 *
 * @remarks If CPUID.06H:EAX.[7] = 1
 */
#define IA32_HWP_REQUEST                                             0x00000774

typedef union
{
  struct
  {
    /**
     * [Bits 7:0] Minimum_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 MinimumPerformance                                      : 8;
#define IA32_HWP_REQUEST_REGISTER_MINIMUM_PERFORMANCE_BIT            0
#define IA32_HWP_REQUEST_REGISTER_MINIMUM_PERFORMANCE_MASK           0xFF
#define IA32_HWP_REQUEST_REGISTER_MINIMUM_PERFORMANCE(_)             (((_) >> 0) & 0xFF)

    /**
     * [Bits 15:8] Maximum_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 MaximumPerformance                                      : 8;
#define IA32_HWP_REQUEST_REGISTER_MAXIMUM_PERFORMANCE_BIT            8
#define IA32_HWP_REQUEST_REGISTER_MAXIMUM_PERFORMANCE_MASK           0xFF
#define IA32_HWP_REQUEST_REGISTER_MAXIMUM_PERFORMANCE(_)             (((_) >> 8) & 0xFF)

    /**
     * [Bits 23:16] Desired_Performance.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 DesiredPerformance                                      : 8;
#define IA32_HWP_REQUEST_REGISTER_DESIRED_PERFORMANCE_BIT            16
#define IA32_HWP_REQUEST_REGISTER_DESIRED_PERFORMANCE_MASK           0xFF
#define IA32_HWP_REQUEST_REGISTER_DESIRED_PERFORMANCE(_)             (((_) >> 16) & 0xFF)

    /**
     * [Bits 31:24] Energy_Performance_Preference.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1 && CPUID.06H:EAX.[10] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 EnergyPerformancePreference                             : 8;
#define IA32_HWP_REQUEST_REGISTER_ENERGY_PERFORMANCE_PREFERENCE_BIT  24
#define IA32_HWP_REQUEST_REGISTER_ENERGY_PERFORMANCE_PREFERENCE_MASK 0xFF
#define IA32_HWP_REQUEST_REGISTER_ENERGY_PERFORMANCE_PREFERENCE(_)   (((_) >> 24) & 0xFF)

    /**
     * [Bits 41:32] Activity_Window.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1 && CPUID.06H:EAX.[9] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 ActivityWindow                                          : 10;
#define IA32_HWP_REQUEST_REGISTER_ACTIVITY_WINDOW_BIT                32
#define IA32_HWP_REQUEST_REGISTER_ACTIVITY_WINDOW_MASK               0x3FF
#define IA32_HWP_REQUEST_REGISTER_ACTIVITY_WINDOW(_)                 (((_) >> 32) & 0x3FF)

    /**
     * [Bit 42] Package_Control.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1 && CPUID.06H:EAX.[11] = 1
     * @see Vol3B[14.4.4(Managing HWP)]
     */
    UINT64 PackageControl                                          : 1;
#define IA32_HWP_REQUEST_REGISTER_PACKAGE_CONTROL_BIT                42
#define IA32_HWP_REQUEST_REGISTER_PACKAGE_CONTROL_MASK               0x01
#define IA32_HWP_REQUEST_REGISTER_PACKAGE_CONTROL(_)                 (((_) >> 42) & 0x01)
    UINT64 Reserved1                                               : 21;
  };

  UINT64 Flags;
} IA32_HWP_REQUEST_REGISTER;

/**
 * Log bits indicating changes to Guaranteed & excursions to Minimum.
 *
 * @remarks If CPUID.06H:EAX.[7] = 1
 */
#define IA32_HWP_STATUS                                              0x00000777

typedef union
{
  struct
  {
    /**
     * [Bit 0] Guaranteed_Performance_Change.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.5(HWP Feedback)]
     */
    UINT64 GuaranteedPerformanceChange                             : 1;
#define IA32_HWP_STATUS_REGISTER_GUARANTEED_PERFORMANCE_CHANGE_BIT   0
#define IA32_HWP_STATUS_REGISTER_GUARANTEED_PERFORMANCE_CHANGE_MASK  0x01
#define IA32_HWP_STATUS_REGISTER_GUARANTEED_PERFORMANCE_CHANGE(_)    (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 2] Excursion_To_Minimum.
     *
     * @remarks If CPUID.06H:EAX.[7] = 1
     * @see Vol3B[14.4.5(HWP Feedback)]
     */
    UINT64 ExcursionToMinimum                                      : 1;
#define IA32_HWP_STATUS_REGISTER_EXCURSION_TO_MINIMUM_BIT            2
#define IA32_HWP_STATUS_REGISTER_EXCURSION_TO_MINIMUM_MASK           0x01
#define IA32_HWP_STATUS_REGISTER_EXCURSION_TO_MINIMUM(_)             (((_) >> 2) & 0x01)
    UINT64 Reserved2                                               : 61;
  };

  UINT64 Flags;
} IA32_HWP_STATUS_REGISTER;

/**
 * x2APIC ID Register.
 *
 * @remarks If CPUID.01H:ECX[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @see Vol3A[10.12(EXTENDED XAPIC (X2APIC))]
 */
#define IA32_X2APIC_APICID                                           0x00000802

/**
 * x2APIC Version Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_VERSION                                          0x00000803

/**
 * x2APIC Task Priority Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_TPR                                              0x00000808

/**
 * x2APIC Processor Priority Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_PPR                                              0x0000080A

/**
 * x2APIC EOI Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_EOI                                              0x0000080B

/**
 * x2APIC Logical Destination Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LDR                                              0x0000080D

/**
 * x2APIC Spurious Interrupt Vector Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_SIVR                                             0x0000080F

/**
 * @defgroup IA32_X2APIC_ISR \
 *           IA32_X2APIC_ISR(n)
 *
 * x2APIC In-Service Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_ISR0                                             0x00000810
#define IA32_X2APIC_ISR1                                             0x00000811
#define IA32_X2APIC_ISR2                                             0x00000812
#define IA32_X2APIC_ISR3                                             0x00000813
#define IA32_X2APIC_ISR4                                             0x00000814
#define IA32_X2APIC_ISR5                                             0x00000815
#define IA32_X2APIC_ISR6                                             0x00000816
#define IA32_X2APIC_ISR7                                             0x00000817
/**
 * @}
 */

/**
 * @defgroup IA32_X2APIC_TMR \
 *           IA32_X2APIC_TMR(n)
 *
 * x2APIC Trigger Mode Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_TMR0                                             0x00000818
#define IA32_X2APIC_TMR1                                             0x00000819
#define IA32_X2APIC_TMR2                                             0x0000081A
#define IA32_X2APIC_TMR3                                             0x0000081B
#define IA32_X2APIC_TMR4                                             0x0000081C
#define IA32_X2APIC_TMR5                                             0x0000081D
#define IA32_X2APIC_TMR6                                             0x0000081E
#define IA32_X2APIC_TMR7                                             0x0000081F
/**
 * @}
 */

/**
 * @defgroup IA32_X2APIC_IRR \
 *           IA32_X2APIC_IRR(n)
 *
 * x2APIC Interrupt Request Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_IRR0                                             0x00000820
#define IA32_X2APIC_IRR1                                             0x00000821
#define IA32_X2APIC_IRR2                                             0x00000822
#define IA32_X2APIC_IRR3                                             0x00000823
#define IA32_X2APIC_IRR4                                             0x00000824
#define IA32_X2APIC_IRR5                                             0x00000825
#define IA32_X2APIC_IRR6                                             0x00000826
#define IA32_X2APIC_IRR7                                             0x00000827
/**
 * @}
 */

/**
 * x2APIC Error Status Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_ESR                                              0x00000828

/**
 * x2APIC LVT Corrected Machine Check Interrupt Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_CMCI                                         0x0000082F

/**
 * x2APIC Interrupt Command Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_ICR                                              0x00000830

/**
 * x2APIC LVT Timer Interrupt Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_TIMER                                        0x00000832

/**
 * x2APIC LVT Thermal Sensor Interrupt Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_THERMAL                                      0x00000833

/**
 * x2APIC LVT Performance Monitor Interrupt Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_PMI                                          0x00000834

/**
 * x2APIC LVT LINT0 Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_LINT0                                        0x00000835

/**
 * x2APIC LVT LINT1 Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_LINT1                                        0x00000836

/**
 * x2APIC LVT Error Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_LVT_ERROR                                        0x00000837

/**
 * x2APIC Initial Count Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_INIT_COUNT                                       0x00000838

/**
 * x2APIC Current Count Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_CUR_COUNT                                        0x00000839

/**
 * x2APIC Divide Configuration Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_DIV_CONF                                         0x0000083E

/**
 * x2APIC Self IPI Register.
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 */
#define IA32_X2APIC_SELF_IPI                                         0x0000083F

/**
 * Silicon Debug Feature Control.
 *
 * @remarks If CPUID.01H:ECX.[11] = 1
 */
#define IA32_DEBUG_INTERFACE                                         0x00000C80

typedef union
{
  struct
  {
    /**
     * @brief Enable <b>(R/W)</b>
     *
     * [Bit 0] BIOS set 1 to enable Silicon debug features. Default is 0.
     *
     * @remarks If CPUID.01H:ECX.[11] = 1
     */
    UINT64 Enable                                                  : 1;
#define IA32_DEBUG_INTERFACE_REGISTER_ENABLE_BIT                     0
#define IA32_DEBUG_INTERFACE_REGISTER_ENABLE_MASK                    0x01
#define IA32_DEBUG_INTERFACE_REGISTER_ENABLE(_)                      (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 29;

    /**
     * @brief Lock <b>(R/W)</b>
     *
     * [Bit 30] If 1, locks any further change to the MSR. The lock bit is set automatically on the first SMI assertion even if
     * not explicitly set by BIOS. Default is 0.
     *
     * @remarks If CPUID.01H:ECX.[11] = 1
     */
    UINT64 Lock                                                    : 1;
#define IA32_DEBUG_INTERFACE_REGISTER_LOCK_BIT                       30
#define IA32_DEBUG_INTERFACE_REGISTER_LOCK_MASK                      0x01
#define IA32_DEBUG_INTERFACE_REGISTER_LOCK(_)                        (((_) >> 30) & 0x01)

    /**
     * @brief Debug Occurred <b>(R/O)</b>
     *
     * [Bit 31] This "sticky bit" is set by hardware to indicate the status of bit 0. Default is 0.
     *
     * @remarks If CPUID.01H:ECX.[11] = 1
     */
    UINT64 DebugOccurred                                           : 1;
#define IA32_DEBUG_INTERFACE_REGISTER_DEBUG_OCCURRED_BIT             31
#define IA32_DEBUG_INTERFACE_REGISTER_DEBUG_OCCURRED_MASK            0x01
#define IA32_DEBUG_INTERFACE_REGISTER_DEBUG_OCCURRED(_)              (((_) >> 31) & 0x01)
    UINT64 Reserved2                                               : 32;
  };

  UINT64 Flags;
} IA32_DEBUG_INTERFACE_REGISTER;

/**
 * L3 QOS Configuration.
 *
 * @remarks If ( CPUID.(EAX=10H, ECX=1):ECX.[2] = 1 )
 */
#define IA32_L3_QOS_CFG                                              0x00000C81

typedef union
{
  struct
  {
    /**
     * @brief Enable <b>(R/W)</b>
     *
     * [Bit 0] Set 1 to enable L3 CAT masks and COS to operate in Code and Data Prioritization (CDP) mode.
     */
    UINT64 Enable                                                  : 1;
#define IA32_L3_QOS_CFG_REGISTER_ENABLE_BIT                          0
#define IA32_L3_QOS_CFG_REGISTER_ENABLE_MASK                         0x01
#define IA32_L3_QOS_CFG_REGISTER_ENABLE(_)                           (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_L3_QOS_CFG_REGISTER;

/**
 * L2 QOS Configuration.
 *
 * @remarks If ( CPUID.(EAX=10H, ECX=2):ECX.[2] = 1 )
 */
#define IA32_L2_QOS_CFG                                              0x00000C82

typedef union
{
  struct
  {
    /**
     * @brief Enable <b>(R/W)</b>
     *
     * [Bit 0] Set 1 to enable L2 CAT masks and COS to operate in Code and Data Prioritization (CDP) mode.
     */
    UINT64 Enable                                                  : 1;
#define IA32_L2_QOS_CFG_REGISTER_ENABLE_BIT                          0
#define IA32_L2_QOS_CFG_REGISTER_ENABLE_MASK                         0x01
#define IA32_L2_QOS_CFG_REGISTER_ENABLE(_)                           (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_L2_QOS_CFG_REGISTER;

/**
 * Monitoring Event Select Register.
 *
 * @remarks If ( CPUID.(EAX=07H, ECX=0):EBX.[12] = 1 )
 */
#define IA32_QM_EVTSEL                                               0x00000C8D

typedef union
{
  struct
  {
    /**
     * @brief Event ID
     *
     * [Bits 7:0] ID of a supported monitoring event to report via IA32_QM_CTR.
     */
    UINT64 EventId                                                 : 8;
#define IA32_QM_EVTSEL_REGISTER_EVENT_ID_BIT                         0
#define IA32_QM_EVTSEL_REGISTER_EVENT_ID_MASK                        0xFF
#define IA32_QM_EVTSEL_REGISTER_EVENT_ID(_)                          (((_) >> 0) & 0xFF)
    UINT64 Reserved1                                               : 24;

    /**
     * @brief Resource Monitoring ID
     *
     * [Bits 63:32] ID for monitoring hardware to report monitored data via IA32_QM_CTR.
     *
     * @remarks Bits [N+31:32] N = Ceil (Log2 (CPUID.(EAX= 0FH,ECX=0H).EBX[31:0] + 1))
     */
    UINT64 ResourceMonitoringId                                    : 32;
#define IA32_QM_EVTSEL_REGISTER_RESOURCE_MONITORING_ID_BIT           32
#define IA32_QM_EVTSEL_REGISTER_RESOURCE_MONITORING_ID_MASK          0xFFFFFFFF
#define IA32_QM_EVTSEL_REGISTER_RESOURCE_MONITORING_ID(_)            (((_) >> 32) & 0xFFFFFFFF)
  };

  UINT64 Flags;
} IA32_QM_EVTSEL_REGISTER;

/**
 * Monitoring Counter Register.
 *
 * @remarks If ( CPUID.(EAX=07H, ECX=0):EBX.[12] = 1 )
 */
#define IA32_QM_CTR                                                  0x00000C8E

typedef union
{
  struct
  {
    /**
     * [Bits 61:0] Resource Monitored Data.
     */
    UINT64 ResourceMonitoredData                                   : 62;
#define IA32_QM_CTR_REGISTER_RESOURCE_MONITORED_DATA_BIT             0
#define IA32_QM_CTR_REGISTER_RESOURCE_MONITORED_DATA_MASK            0x3FFFFFFFFFFFFFFF
#define IA32_QM_CTR_REGISTER_RESOURCE_MONITORED_DATA(_)              (((_) >> 0) & 0x3FFFFFFFFFFFFFFF)

    /**
     * @brief Unavailable
     *
     * [Bit 62] If 1, indicates data for this RMID is not available or not monitored for this resource or RMID.
     */
    UINT64 Unavailable                                             : 1;
#define IA32_QM_CTR_REGISTER_UNAVAILABLE_BIT                         62
#define IA32_QM_CTR_REGISTER_UNAVAILABLE_MASK                        0x01
#define IA32_QM_CTR_REGISTER_UNAVAILABLE(_)                          (((_) >> 62) & 0x01)

    /**
     * @brief Error
     *
     * [Bit 63] If 1, indicates an unsupported RMID or event type was written to IA32_PQR_QM_EVTSEL.
     */
    UINT64 Error                                                   : 1;
#define IA32_QM_CTR_REGISTER_ERROR_BIT                               63
#define IA32_QM_CTR_REGISTER_ERROR_MASK                              0x01
#define IA32_QM_CTR_REGISTER_ERROR(_)                                (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} IA32_QM_CTR_REGISTER;

/**
 * Resource Association Register.
 *
 * @remarks If ( (CPUID.(EAX=07H, ECX=0):EBX[12] = 1) or (CPUID.(EAX=07H, ECX=0):EBX[15] = 1 ) )
 */
#define IA32_PQR_ASSOC                                               0x00000C8F

typedef union
{
  struct
  {
    /**
     * @brief Resource Monitoring ID <b>(R/W)</b>
     *
     * [Bits 31:0] ID for monitoring hardware to track internal operation, e.g., memory access.
     *
     * @remarks Bits [N-1:0] N = Ceil (Log2 (CPUID.(EAX= 0FH, ECX=0H).EBX[31:0] +1)) 31:N Reserved
     */
    UINT64 ResourceMonitoringId                                    : 32;
#define IA32_PQR_ASSOC_REGISTER_RESOURCE_MONITORING_ID_BIT           0
#define IA32_PQR_ASSOC_REGISTER_RESOURCE_MONITORING_ID_MASK          0xFFFFFFFF
#define IA32_PQR_ASSOC_REGISTER_RESOURCE_MONITORING_ID(_)            (((_) >> 0) & 0xFFFFFFFF)

    /**
     * @brief COS <b>(R/W)</b>
     *
     * [Bits 63:32] The class of service (COS) to enforce (on writes); returns the current COS when read.
     *
     * @remarks If ( CPUID.(EAX=07H, ECX=0):EBX.[15] = 1 )
     */
    UINT64 Cos                                                     : 32;
#define IA32_PQR_ASSOC_REGISTER_COS_BIT                              32
#define IA32_PQR_ASSOC_REGISTER_COS_MASK                             0xFFFFFFFF
#define IA32_PQR_ASSOC_REGISTER_COS(_)                               (((_) >> 32) & 0xFFFFFFFF)
  };

  UINT64 Flags;
} IA32_PQR_ASSOC_REGISTER;

/**
 * Supervisor State of MPX Configuration.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=0H):EBX[14] = 1)
 */
#define IA32_BNDCFGS                                                 0x00000D90

typedef union
{
  struct
  {
    /**
     * [Bit 0] Enable Intel MPX in supervisor mode.
     */
    UINT64 Enable                                                  : 1;
#define IA32_BNDCFGS_REGISTER_ENABLE_BIT                             0
#define IA32_BNDCFGS_REGISTER_ENABLE_MASK                            0x01
#define IA32_BNDCFGS_REGISTER_ENABLE(_)                              (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Preserve the bounds registers for near branch instructions in the absence of the BND prefix.
     */
    UINT64 BndPreserve                                             : 1;
#define IA32_BNDCFGS_REGISTER_BND_PRESERVE_BIT                       1
#define IA32_BNDCFGS_REGISTER_BND_PRESERVE_MASK                      0x01
#define IA32_BNDCFGS_REGISTER_BND_PRESERVE(_)                        (((_) >> 1) & 0x01)
    UINT64 Reserved1                                               : 10;

    /**
     * [Bits 63:12] Base Address of Bound Directory.
     */
    UINT64 BoundDirectoryBaseAddress                               : 52;
#define IA32_BNDCFGS_REGISTER_BOUND_DIRECTORY_BASE_ADDRESS_BIT       12
#define IA32_BNDCFGS_REGISTER_BOUND_DIRECTORY_BASE_ADDRESS_MASK      0xFFFFFFFFFFFFF
#define IA32_BNDCFGS_REGISTER_BOUND_DIRECTORY_BASE_ADDRESS(_)        (((_) >> 12) & 0xFFFFFFFFFFFFF)
  };

  UINT64 Flags;
} IA32_BNDCFGS_REGISTER;

/**
 * Extended Supervisor State Mask.
 *
 * @remarks If ( CPUID.(0DH, 1):EAX.[3] = 1
 */
#define IA32_XSS                                                     0x00000DA0

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 8;

    /**
     * [Bit 8] Trace Packet Configuration State.
     */
    UINT64 TracePacketConfigurationState                           : 1;
#define IA32_XSS_REGISTER_TRACE_PACKET_CONFIGURATION_STATE_BIT       8
#define IA32_XSS_REGISTER_TRACE_PACKET_CONFIGURATION_STATE_MASK      0x01
#define IA32_XSS_REGISTER_TRACE_PACKET_CONFIGURATION_STATE(_)        (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 55;
  };

  UINT64 Flags;
} IA32_XSS_REGISTER;

/**
 * Package Level Enable/disable HDC.
 *
 * @remarks If CPUID.06H:EAX.[13] = 1
 */
#define IA32_PKG_HDC_CTL                                             0x00000DB0

typedef union
{
  struct
  {
    /**
     * @brief HDC_Pkg_Enable <b>(R/W)</b>
     *
     * [Bit 0] Force HDC idling or wake up HDC-idled logical processors in the package.
     *
     * @remarks If CPUID.06H:EAX.[13] = 1
     * @see Vol3B[14.5.2(Package level Enabling HDC)]
     */
    UINT64 HdcPkgEnable                                            : 1;
#define IA32_PKG_HDC_CTL_REGISTER_HDC_PKG_ENABLE_BIT                 0
#define IA32_PKG_HDC_CTL_REGISTER_HDC_PKG_ENABLE_MASK                0x01
#define IA32_PKG_HDC_CTL_REGISTER_HDC_PKG_ENABLE(_)                  (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_PKG_HDC_CTL_REGISTER;

/**
 * Enable/disable HWP.
 *
 * @remarks If CPUID.06H:EAX.[13] = 1
 */
#define IA32_PM_CTL1                                                 0x00000DB1

typedef union
{
  struct
  {
    /**
     * @brief HDC_Allow_Block <b>(R/W)</b>
     *
     * [Bit 0] Allow/Block this logical processor for package level HDC control.
     *
     * @remarks If CPUID.06H:EAX.[13] = 1
     * @see Vol3B[14.5.3(Logical-Processor Level HDC Control)]
     */
    UINT64 HdcAllowBlock                                           : 1;
#define IA32_PM_CTL1_REGISTER_HDC_ALLOW_BLOCK_BIT                    0
#define IA32_PM_CTL1_REGISTER_HDC_ALLOW_BLOCK_MASK                   0x01
#define IA32_PM_CTL1_REGISTER_HDC_ALLOW_BLOCK(_)                     (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 63;
  };

  UINT64 Flags;
} IA32_PM_CTL1_REGISTER;

/**
 * Per-Logical_Processor HDC Idle Residency.
 *
 * @remarks If CPUID.06H:EAX.[13] = 1
 */
#define IA32_THREAD_STALL                                            0x00000DB2

typedef struct
{
  UINT64 StallCycleCount;
} IA32_THREAD_STALL_REGISTER;

/**
 * Extended Feature Enables.
 *
 * @remarks If CPUID.06H:EAX.[13] = 1
 */
#define IA32_EFER                                                    0xC0000080

typedef union
{
  struct
  {
    /**
     * @brief SYSCALL Enable <b>(R/W)</b>
     *
     * [Bit 0] Enables SYSCALL/SYSRET instructions in 64-bit mode.
     */
    UINT64 SyscallEnable                                           : 1;
#define IA32_EFER_REGISTER_SYSCALL_ENABLE_BIT                        0
#define IA32_EFER_REGISTER_SYSCALL_ENABLE_MASK                       0x01
#define IA32_EFER_REGISTER_SYSCALL_ENABLE(_)                         (((_) >> 0) & 0x01)
    UINT64 Reserved1                                               : 7;

    /**
     * @brief IA-32e Mode Enable <b>(R/W)</b>
     *
     * [Bit 8] Enables IA-32e mode operation.
     */
    UINT64 Ia32EModeEnable                                         : 1;
#define IA32_EFER_REGISTER_IA32E_MODE_ENABLE_BIT                     8
#define IA32_EFER_REGISTER_IA32E_MODE_ENABLE_MASK                    0x01
#define IA32_EFER_REGISTER_IA32E_MODE_ENABLE(_)                      (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * @brief IA-32e Mode Active <b>(R)</b>
     *
     * [Bit 10] Indicates IA-32e mode is active when set.
     */
    UINT64 Ia32EModeActive                                         : 1;
#define IA32_EFER_REGISTER_IA32E_MODE_ACTIVE_BIT                     10
#define IA32_EFER_REGISTER_IA32E_MODE_ACTIVE_MASK                    0x01
#define IA32_EFER_REGISTER_IA32E_MODE_ACTIVE(_)                      (((_) >> 10) & 0x01)

    /**
     * [Bit 11] Execute Disable Bit Enable.
     */
    UINT64 ExecuteDisableBitEnable                                 : 1;
#define IA32_EFER_REGISTER_EXECUTE_DISABLE_BIT_ENABLE_BIT            11
#define IA32_EFER_REGISTER_EXECUTE_DISABLE_BIT_ENABLE_MASK           0x01
#define IA32_EFER_REGISTER_EXECUTE_DISABLE_BIT_ENABLE(_)             (((_) >> 11) & 0x01)
    UINT64 Reserved3                                               : 52;
  };

  UINT64 Flags;
} IA32_EFER_REGISTER;

/**
 * System Call Target Address.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_STAR                                                    0xC0000081

/**
 * @brief IA-32e Mode System Call Target Address <b>(R/W)</b>
 *
 * Target RIP for the called procedure when SYSCALL is executed in 64-bit mode.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_LSTAR                                                   0xC0000082

/**
 * @brief IA-32e Mode System Call Target Address <b>(R/W)</b>
 *
 * Not used, as the SYSCALL instruction is not recognized in compatibility mode.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_CSTAR                                                   0xC0000083

/**
 * System Call Flag Mask.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_FMASK                                                   0xC0000084

/**
 * Map of BASE Address of FS.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_FS_BASE                                                 0xC0000100

/**
 * Map of BASE Address of GS.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_GS_BASE                                                 0xC0000101

/**
 * Swap Target of BASE Address of GS.
 *
 * @remarks If CPUID.80000001:EDX.[29] = 1
 */
#define IA32_KERNEL_GS_BASE                                          0xC0000102

/**
 * Auxiliary TSC.
 *
 * @remarks If CPUID.80000001H: EDX[27] = 1 or CPUID.(EAX=7,ECX=0):ECX[bit 22] = 1
 */
#define IA32_TSC_AUX                                                 0xC0000103

typedef union
{
  struct
  {
    /**
     * [Bits 31:0] AUX. Auxiliary signature of TSC.
     */
    UINT64 TscAuxiliarySignature                                   : 32;
#define IA32_TSC_AUX_REGISTER_TSC_AUXILIARY_SIGNATURE_BIT            0
#define IA32_TSC_AUX_REGISTER_TSC_AUXILIARY_SIGNATURE_MASK           0xFFFFFFFF
#define IA32_TSC_AUX_REGISTER_TSC_AUXILIARY_SIGNATURE(_)             (((_) >> 0) & 0xFFFFFFFF)
    UINT64 Reserved1                                               : 32;
  };

  UINT64 Flags;
} IA32_TSC_AUX_REGISTER;

/**
 * @}
 */

/**
 * @defgroup PAGING \
 *           Paging
 * @{
 */
/**
 * @defgroup PAGING_32 \
 *           32-Bit Paging
 *
 * A logical processor uses 32-bit paging if CR0.PG = 1 and CR4.PAE = 0. 32-bit paging translates 32-bit linear addresses
 * to 40-bit physical addresses. Although 40 bits corresponds to 1 TByte, linear addresses are limited to 32 bits; at most
 * 4 GBytes of linear-address space may be accessed at any given time.
 * 32-bit paging uses a hierarchy of paging structures to produce a translation for a linear address. CR3 is used to locate
 * the first paging-structure, the page directory. 32-bit paging may map linear addresses to either 4-KByte pages or
 * 4-MByte pages.
 *
 * @see Vol3A[4.5(4-LEVEL PAGING)] (reference)
 * @{
 */
/**
 * @brief Format of a 32-Bit Page-Directory Entry that Maps a 4-MByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to map a 4-MByte page.
     */
    UINT32 Present                                                 : 1;
#define PDE_4MB_32_PRESENT_BIT                                       0
#define PDE_4MB_32_PRESENT_MASK                                      0x01
#define PDE_4MB_32_PRESENT(_)                                        (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 4-MByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Write                                                   : 1;
#define PDE_4MB_32_WRITE_BIT                                         1
#define PDE_4MB_32_WRITE_MASK                                        0x01
#define PDE_4MB_32_WRITE(_)                                          (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 4-MByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Supervisor                                              : 1;
#define PDE_4MB_32_SUPERVISOR_BIT                                    2
#define PDE_4MB_32_SUPERVISOR_MASK                                   0x01
#define PDE_4MB_32_SUPERVISOR(_)                                     (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 4-MByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelWriteThrough                                   : 1;
#define PDE_4MB_32_PAGE_LEVEL_WRITE_THROUGH_BIT                      3
#define PDE_4MB_32_PAGE_LEVEL_WRITE_THROUGH_MASK                     0x01
#define PDE_4MB_32_PAGE_LEVEL_WRITE_THROUGH(_)                       (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 4-MByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelCacheDisable                                   : 1;
#define PDE_4MB_32_PAGE_LEVEL_CACHE_DISABLE_BIT                      4
#define PDE_4MB_32_PAGE_LEVEL_CACHE_DISABLE_MASK                     0x01
#define PDE_4MB_32_PAGE_LEVEL_CACHE_DISABLE(_)                       (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether software has accessed the 4-MByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT32 Accessed                                                : 1;
#define PDE_4MB_32_ACCESSED_BIT                                      5
#define PDE_4MB_32_ACCESSED_MASK                                     0x01
#define PDE_4MB_32_ACCESSED(_)                                       (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Dirty; indicates whether software has written to the 4-MByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT32 Dirty                                                   : 1;
#define PDE_4MB_32_DIRTY_BIT                                         6
#define PDE_4MB_32_DIRTY_MASK                                        0x01
#define PDE_4MB_32_DIRTY(_)                                          (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Page size; must be 1 (otherwise, this entry references a page table).
     */
    UINT32 LargePage                                               : 1;
#define PDE_4MB_32_LARGE_PAGE_BIT                                    7
#define PDE_4MB_32_LARGE_PAGE_MASK                                   0x01
#define PDE_4MB_32_LARGE_PAGE(_)                                     (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
     *
     * @see Vol3A[4.10(Caching Translation Information)]
     */
    UINT32 Global                                                  : 1;
#define PDE_4MB_32_GLOBAL_BIT                                        8
#define PDE_4MB_32_GLOBAL_MASK                                       0x01
#define PDE_4MB_32_GLOBAL(_)                                         (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT32 Ignored1                                                : 3;
#define PDE_4MB_32_IGNORED_1_BIT                                     9
#define PDE_4MB_32_IGNORED_1_MASK                                    0x07
#define PDE_4MB_32_IGNORED_1(_)                                      (((_) >> 9) & 0x07)

    /**
     * [Bit 12] Indirectly determines the memory type used to access the 4-MByte page referenced by this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 Pat                                                     : 1;
#define PDE_4MB_32_PAT_BIT                                           12
#define PDE_4MB_32_PAT_MASK                                          0x01
#define PDE_4MB_32_PAT(_)                                            (((_) >> 12) & 0x01)

    /**
     * [Bits 20:13] Bits (M-1):32 of physical address of the 4-MByte page referenced by this entry.
     */
    UINT32 PageFrameNumberLow                                      : 8;
#define PDE_4MB_32_PAGE_FRAME_NUMBER_LOW_BIT                         13
#define PDE_4MB_32_PAGE_FRAME_NUMBER_LOW_MASK                        0xFF
#define PDE_4MB_32_PAGE_FRAME_NUMBER_LOW(_)                          (((_) >> 13) & 0xFF)
    UINT32 Reserved1                                               : 1;

    /**
     * [Bits 31:22] Bits 31:22 of physical address of the 4-MByte page referenced by this entry.
     */
    UINT32 PageFrameNumberHigh                                     : 10;
#define PDE_4MB_32_PAGE_FRAME_NUMBER_HIGH_BIT                        22
#define PDE_4MB_32_PAGE_FRAME_NUMBER_HIGH_MASK                       0x3FF
#define PDE_4MB_32_PAGE_FRAME_NUMBER_HIGH(_)                         (((_) >> 22) & 0x3FF)
  };

  UINT32 Flags;
} PDE_4MB_32;

/**
 * @brief Format of a 32-Bit Page-Directory Entry that References a Page Table
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to reference a page table.
     */
    UINT32 Present                                                 : 1;
#define PDE_32_PRESENT_BIT                                           0
#define PDE_32_PRESENT_MASK                                          0x01
#define PDE_32_PRESENT(_)                                            (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 4-MByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Write                                                   : 1;
#define PDE_32_WRITE_BIT                                             1
#define PDE_32_WRITE_MASK                                            0x01
#define PDE_32_WRITE(_)                                              (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 4-MByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Supervisor                                              : 1;
#define PDE_32_SUPERVISOR_BIT                                        2
#define PDE_32_SUPERVISOR_MASK                                       0x01
#define PDE_32_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page table referenced by this
     * entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelWriteThrough                                   : 1;
#define PDE_32_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PDE_32_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PDE_32_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page table referenced by this
     * entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelCacheDisable                                   : 1;
#define PDE_32_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PDE_32_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PDE_32_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT32 Accessed                                                : 1;
#define PDE_32_ACCESSED_BIT                                          5
#define PDE_32_ACCESSED_MASK                                         0x01
#define PDE_32_ACCESSED(_)                                           (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Ignored.
     */
    UINT32 Ignored1                                                : 1;
#define PDE_32_IGNORED_1_BIT                                         6
#define PDE_32_IGNORED_1_MASK                                        0x01
#define PDE_32_IGNORED_1(_)                                          (((_) >> 6) & 0x01)

    /**
     * [Bit 7] If CR4.PSE = 1, must be 0 (otherwise, this entry maps a 4-MByte page); otherwise, ignored.
     */
    UINT32 LargePage                                               : 1;
#define PDE_32_LARGE_PAGE_BIT                                        7
#define PDE_32_LARGE_PAGE_MASK                                       0x01
#define PDE_32_LARGE_PAGE(_)                                         (((_) >> 7) & 0x01)

    /**
     * [Bits 11:8] Ignored.
     */
    UINT32 Ignored2                                                : 4;
#define PDE_32_IGNORED_2_BIT                                         8
#define PDE_32_IGNORED_2_MASK                                        0x0F
#define PDE_32_IGNORED_2(_)                                          (((_) >> 8) & 0x0F)

    /**
     * [Bits 31:12] Physical address of 4-KByte aligned page table referenced by this entry.
     */
    UINT32 PageFrameNumber                                         : 20;
#define PDE_32_PAGE_FRAME_NUMBER_BIT                                 12
#define PDE_32_PAGE_FRAME_NUMBER_MASK                                0xFFFFF
#define PDE_32_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFF)
  };

  UINT32 Flags;
} PDE_32;

/**
 * @brief Format of a 32-Bit Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to map a 4-KByte page.
     */
    UINT32 Present                                                 : 1;
#define PTE_32_PRESENT_BIT                                           0
#define PTE_32_PRESENT_MASK                                          0x01
#define PTE_32_PRESENT(_)                                            (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Write                                                   : 1;
#define PTE_32_WRITE_BIT                                             1
#define PTE_32_WRITE_MASK                                            0x01
#define PTE_32_WRITE(_)                                              (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT32 Supervisor                                              : 1;
#define PTE_32_SUPERVISOR_BIT                                        2
#define PTE_32_SUPERVISOR_MASK                                       0x01
#define PTE_32_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 4-KByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelWriteThrough                                   : 1;
#define PTE_32_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PTE_32_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PTE_32_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 4-KByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 PageLevelCacheDisable                                   : 1;
#define PTE_32_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PTE_32_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PTE_32_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether software has accessed the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT32 Accessed                                                : 1;
#define PTE_32_ACCESSED_BIT                                          5
#define PTE_32_ACCESSED_MASK                                         0x01
#define PTE_32_ACCESSED(_)                                           (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Dirty; indicates whether software has written to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT32 Dirty                                                   : 1;
#define PTE_32_DIRTY_BIT                                             6
#define PTE_32_DIRTY_MASK                                            0x01
#define PTE_32_DIRTY(_)                                              (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Indirectly determines the memory type used to access the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT32 Pat                                                     : 1;
#define PTE_32_PAT_BIT                                               7
#define PTE_32_PAT_MASK                                              0x01
#define PTE_32_PAT(_)                                                (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
     *
     * @see Vol3A[4.10(Caching Translation Information)]
     */
    UINT32 Global                                                  : 1;
#define PTE_32_GLOBAL_BIT                                            8
#define PTE_32_GLOBAL_MASK                                           0x01
#define PTE_32_GLOBAL(_)                                             (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT32 Ignored1                                                : 3;
#define PTE_32_IGNORED_1_BIT                                         9
#define PTE_32_IGNORED_1_MASK                                        0x07
#define PTE_32_IGNORED_1(_)                                          (((_) >> 9) & 0x07)

    /**
     * [Bits 31:12] Physical address of 4-KByte aligned page table referenced by this entry.
     */
    UINT32 PageFrameNumber                                         : 20;
#define PTE_32_PAGE_FRAME_NUMBER_BIT                                 12
#define PTE_32_PAGE_FRAME_NUMBER_MASK                                0xFFFFF
#define PTE_32_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFF)
  };

  UINT32 Flags;
} PTE_32;

/**
 * @brief Format of a common Page-Table Entry
 */
typedef union
{
  struct
  {
    UINT32 Present                                                 : 1;
#define PT_ENTRY_32_PRESENT_BIT                                      0
#define PT_ENTRY_32_PRESENT_MASK                                     0x01
#define PT_ENTRY_32_PRESENT(_)                                       (((_) >> 0) & 0x01)
    UINT32 Write                                                   : 1;
#define PT_ENTRY_32_WRITE_BIT                                        1
#define PT_ENTRY_32_WRITE_MASK                                       0x01
#define PT_ENTRY_32_WRITE(_)                                         (((_) >> 1) & 0x01)
    UINT32 Supervisor                                              : 1;
#define PT_ENTRY_32_SUPERVISOR_BIT                                   2
#define PT_ENTRY_32_SUPERVISOR_MASK                                  0x01
#define PT_ENTRY_32_SUPERVISOR(_)                                    (((_) >> 2) & 0x01)
    UINT32 PageLevelWriteThrough                                   : 1;
#define PT_ENTRY_32_PAGE_LEVEL_WRITE_THROUGH_BIT                     3
#define PT_ENTRY_32_PAGE_LEVEL_WRITE_THROUGH_MASK                    0x01
#define PT_ENTRY_32_PAGE_LEVEL_WRITE_THROUGH(_)                      (((_) >> 3) & 0x01)
    UINT32 PageLevelCacheDisable                                   : 1;
#define PT_ENTRY_32_PAGE_LEVEL_CACHE_DISABLE_BIT                     4
#define PT_ENTRY_32_PAGE_LEVEL_CACHE_DISABLE_MASK                    0x01
#define PT_ENTRY_32_PAGE_LEVEL_CACHE_DISABLE(_)                      (((_) >> 4) & 0x01)
    UINT32 Accessed                                                : 1;
#define PT_ENTRY_32_ACCESSED_BIT                                     5
#define PT_ENTRY_32_ACCESSED_MASK                                    0x01
#define PT_ENTRY_32_ACCESSED(_)                                      (((_) >> 5) & 0x01)
    UINT32 Dirty                                                   : 1;
#define PT_ENTRY_32_DIRTY_BIT                                        6
#define PT_ENTRY_32_DIRTY_MASK                                       0x01
#define PT_ENTRY_32_DIRTY(_)                                         (((_) >> 6) & 0x01)
    UINT32 LargePage                                               : 1;
#define PT_ENTRY_32_LARGE_PAGE_BIT                                   7
#define PT_ENTRY_32_LARGE_PAGE_MASK                                  0x01
#define PT_ENTRY_32_LARGE_PAGE(_)                                    (((_) >> 7) & 0x01)
    UINT32 Global                                                  : 1;
#define PT_ENTRY_32_GLOBAL_BIT                                       8
#define PT_ENTRY_32_GLOBAL_MASK                                      0x01
#define PT_ENTRY_32_GLOBAL(_)                                        (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT32 Ignored1                                                : 3;
#define PT_ENTRY_32_IGNORED_1_BIT                                    9
#define PT_ENTRY_32_IGNORED_1_MASK                                   0x07
#define PT_ENTRY_32_IGNORED_1(_)                                     (((_) >> 9) & 0x07)

    /**
     * [Bits 31:12] Physical address of the 4-KByte page referenced by this entry.
     */
    UINT32 PageFrameNumber                                         : 20;
#define PT_ENTRY_32_PAGE_FRAME_NUMBER_BIT                            12
#define PT_ENTRY_32_PAGE_FRAME_NUMBER_MASK                           0xFFFFF
#define PT_ENTRY_32_PAGE_FRAME_NUMBER(_)                             (((_) >> 12) & 0xFFFFF)
  };

  UINT32 Flags;
} PT_ENTRY_32;

/**
 * @}
 */

/**
 * @defgroup PAGING_64 \
 *           64-Bit (4-Level Paging)
 *
 * A logical processor uses 4-level paging if CR0.PG = 1, CR4.PAE = 1, and IA32_EFER.LME = 1. With 4-level paging, linear
 * address are translated using a hierarchy of in-memory paging structures located using the contents of CR3. 4-level
 * paging translates 48-bit linear addresses to 52-bit physical addresses. Although 52 bits corresponds to 4 PBytes, linear
 * addresses are limited to 48 bits; at most 256 TBytes of linear-address space may be accessed at any given time.
 * 4-level paging uses a hierarchy of paging structures to produce a translation for a linear address. CR3 is used to
 * locate the first paging-structure, the PML4 table. Use of CR3 with 4-level paging depends on whether processcontext
 * identifiers (PCIDs) have been enabled by setting CR4.PCIDE.
 *
 * @see Vol3A[4.5(4-LEVEL PAGING)] (reference)
 * @{
 */
/**
 * @brief Format of a 4-Level PML4 Entry (PML4E) that References a Page-Directory-Pointer Table
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to reference a page-directory-pointer table.
     */
    UINT64 Present                                                 : 1;
#define PML4E_64_PRESENT_BIT                                         0
#define PML4E_64_PRESENT_MASK                                        0x01
#define PML4E_64_PRESENT(_)                                          (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 512-GByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PML4E_64_WRITE_BIT                                           1
#define PML4E_64_WRITE_MASK                                          0x01
#define PML4E_64_WRITE(_)                                            (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 512-GByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PML4E_64_SUPERVISOR_BIT                                      2
#define PML4E_64_SUPERVISOR_MASK                                     0x01
#define PML4E_64_SUPERVISOR(_)                                       (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page-directory-pointer table
     * referenced by this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH_BIT                        3
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH_MASK                       0x01
#define PML4E_64_PAGE_LEVEL_WRITE_THROUGH(_)                         (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page-directory-pointer table
     * referenced by this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE_BIT                        4
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE_MASK                       0x01
#define PML4E_64_PAGE_LEVEL_CACHE_DISABLE(_)                         (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PML4E_64_ACCESSED_BIT                                        5
#define PML4E_64_ACCESSED_MASK                                       0x01
#define PML4E_64_ACCESSED(_)                                         (((_) >> 5) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 7] Reserved (must be 0).
     */
    UINT64 MustBeZero                                              : 1;
#define PML4E_64_MUST_BE_ZERO_BIT                                    7
#define PML4E_64_MUST_BE_ZERO_MASK                                   0x01
#define PML4E_64_MUST_BE_ZERO(_)                                     (((_) >> 7) & 0x01)

    /**
     * [Bits 11:8] Ignored.
     */
    UINT64 Ignored1                                                : 4;
#define PML4E_64_IGNORED_1_BIT                                       8
#define PML4E_64_IGNORED_1_MASK                                      0x0F
#define PML4E_64_IGNORED_1(_)                                        (((_) >> 8) & 0x0F)

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned page-directory-pointer table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define PML4E_64_PAGE_FRAME_NUMBER_BIT                               12
#define PML4E_64_PAGE_FRAME_NUMBER_MASK                              0xFFFFFFFFF
#define PML4E_64_PAGE_FRAME_NUMBER(_)                                (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 62:52] Ignored.
     */
    UINT64 Ignored2                                                : 11;
#define PML4E_64_IGNORED_2_BIT                                       52
#define PML4E_64_IGNORED_2_MASK                                      0x7FF
#define PML4E_64_IGNORED_2(_)                                        (((_) >> 52) & 0x7FF)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 512-GByte region
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PML4E_64_EXECUTE_DISABLE_BIT                                 63
#define PML4E_64_EXECUTE_DISABLE_MASK                                0x01
#define PML4E_64_EXECUTE_DISABLE(_)                                  (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PML4E_64;

/**
 * @brief Format of a 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to map a 1-GByte page.
     */
    UINT64 Present                                                 : 1;
#define PDPTE_1GB_64_PRESENT_BIT                                     0
#define PDPTE_1GB_64_PRESENT_MASK                                    0x01
#define PDPTE_1GB_64_PRESENT(_)                                      (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 1-GByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PDPTE_1GB_64_WRITE_BIT                                       1
#define PDPTE_1GB_64_WRITE_MASK                                      0x01
#define PDPTE_1GB_64_WRITE(_)                                        (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 1-GByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PDPTE_1GB_64_SUPERVISOR_BIT                                  2
#define PDPTE_1GB_64_SUPERVISOR_MASK                                 0x01
#define PDPTE_1GB_64_SUPERVISOR(_)                                   (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 1-GByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PDPTE_1GB_64_PAGE_LEVEL_WRITE_THROUGH_BIT                    3
#define PDPTE_1GB_64_PAGE_LEVEL_WRITE_THROUGH_MASK                   0x01
#define PDPTE_1GB_64_PAGE_LEVEL_WRITE_THROUGH(_)                     (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 1-GByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PDPTE_1GB_64_PAGE_LEVEL_CACHE_DISABLE_BIT                    4
#define PDPTE_1GB_64_PAGE_LEVEL_CACHE_DISABLE_MASK                   0x01
#define PDPTE_1GB_64_PAGE_LEVEL_CACHE_DISABLE(_)                     (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether software has accessed the 1-GByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PDPTE_1GB_64_ACCESSED_BIT                                    5
#define PDPTE_1GB_64_ACCESSED_MASK                                   0x01
#define PDPTE_1GB_64_ACCESSED(_)                                     (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Dirty; indicates whether software has written to the 1-GByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Dirty                                                   : 1;
#define PDPTE_1GB_64_DIRTY_BIT                                       6
#define PDPTE_1GB_64_DIRTY_MASK                                      0x01
#define PDPTE_1GB_64_DIRTY(_)                                        (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Page size; must be 1 (otherwise, this entry references a page directory).
     */
    UINT64 LargePage                                               : 1;
#define PDPTE_1GB_64_LARGE_PAGE_BIT                                  7
#define PDPTE_1GB_64_LARGE_PAGE_MASK                                 0x01
#define PDPTE_1GB_64_LARGE_PAGE(_)                                   (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
     *
     * @see Vol3A[4.10(Caching Translation Information)]
     */
    UINT64 Global                                                  : 1;
#define PDPTE_1GB_64_GLOBAL_BIT                                      8
#define PDPTE_1GB_64_GLOBAL_MASK                                     0x01
#define PDPTE_1GB_64_GLOBAL(_)                                       (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT64 Ignored1                                                : 3;
#define PDPTE_1GB_64_IGNORED_1_BIT                                   9
#define PDPTE_1GB_64_IGNORED_1_MASK                                  0x07
#define PDPTE_1GB_64_IGNORED_1(_)                                    (((_) >> 9) & 0x07)

    /**
     * [Bit 12] Indirectly determines the memory type used to access the 1-GByte page referenced by this entry.
     *
     * @note The PAT is supported on all processors that support 4-level paging.
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 Pat                                                     : 1;
#define PDPTE_1GB_64_PAT_BIT                                         12
#define PDPTE_1GB_64_PAT_MASK                                        0x01
#define PDPTE_1GB_64_PAT(_)                                          (((_) >> 12) & 0x01)
    UINT64 Reserved1                                               : 17;

    /**
     * [Bits 47:30] Physical address of the 1-GByte page referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 18;
#define PDPTE_1GB_64_PAGE_FRAME_NUMBER_BIT                           30
#define PDPTE_1GB_64_PAGE_FRAME_NUMBER_MASK                          0x3FFFF
#define PDPTE_1GB_64_PAGE_FRAME_NUMBER(_)                            (((_) >> 30) & 0x3FFFF)
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 58:52] Ignored.
     */
    UINT64 Ignored2                                                : 7;
#define PDPTE_1GB_64_IGNORED_2_BIT                                   52
#define PDPTE_1GB_64_IGNORED_2_MASK                                  0x7F
#define PDPTE_1GB_64_IGNORED_2(_)                                    (((_) >> 52) & 0x7F)

    /**
     * [Bits 62:59] Protection key; if CR4.PKE = 1, determines the protection key of the page; ignored otherwise.
     *
     * @see Vol3A[4.6.2(Protection Keys)]
     */
    UINT64 ProtectionKey                                           : 4;
#define PDPTE_1GB_64_PROTECTION_KEY_BIT                              59
#define PDPTE_1GB_64_PROTECTION_KEY_MASK                             0x0F
#define PDPTE_1GB_64_PROTECTION_KEY(_)                               (((_) >> 59) & 0x0F)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte page
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PDPTE_1GB_64_EXECUTE_DISABLE_BIT                             63
#define PDPTE_1GB_64_EXECUTE_DISABLE_MASK                            0x01
#define PDPTE_1GB_64_EXECUTE_DISABLE(_)                              (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PDPTE_1GB_64;

/**
 * @brief Format of a 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that References a Page Directory
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to reference a page directory.
     */
    UINT64 Present                                                 : 1;
#define PDPTE_64_PRESENT_BIT                                         0
#define PDPTE_64_PRESENT_MASK                                        0x01
#define PDPTE_64_PRESENT(_)                                          (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 1-GByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PDPTE_64_WRITE_BIT                                           1
#define PDPTE_64_WRITE_MASK                                          0x01
#define PDPTE_64_WRITE(_)                                            (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 1-GByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PDPTE_64_SUPERVISOR_BIT                                      2
#define PDPTE_64_SUPERVISOR_MASK                                     0x01
#define PDPTE_64_SUPERVISOR(_)                                       (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page directory referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                        3
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                       0x01
#define PDPTE_64_PAGE_LEVEL_WRITE_THROUGH(_)                         (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page directory referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                        4
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                       0x01
#define PDPTE_64_PAGE_LEVEL_CACHE_DISABLE(_)                         (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PDPTE_64_ACCESSED_BIT                                        5
#define PDPTE_64_ACCESSED_MASK                                       0x01
#define PDPTE_64_ACCESSED(_)                                         (((_) >> 5) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 7] Page size; must be 0 (otherwise, this entry maps a 1-GByte page).
     */
    UINT64 LargePage                                               : 1;
#define PDPTE_64_LARGE_PAGE_BIT                                      7
#define PDPTE_64_LARGE_PAGE_MASK                                     0x01
#define PDPTE_64_LARGE_PAGE(_)                                       (((_) >> 7) & 0x01)

    /**
     * [Bits 11:8] Ignored.
     */
    UINT64 Ignored1                                                : 4;
#define PDPTE_64_IGNORED_1_BIT                                       8
#define PDPTE_64_IGNORED_1_MASK                                      0x0F
#define PDPTE_64_IGNORED_1(_)                                        (((_) >> 8) & 0x0F)

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned page directory referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define PDPTE_64_PAGE_FRAME_NUMBER_BIT                               12
#define PDPTE_64_PAGE_FRAME_NUMBER_MASK                              0xFFFFFFFFF
#define PDPTE_64_PAGE_FRAME_NUMBER(_)                                (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 62:52] Ignored.
     */
    UINT64 Ignored2                                                : 11;
#define PDPTE_64_IGNORED_2_BIT                                       52
#define PDPTE_64_IGNORED_2_MASK                                      0x7FF
#define PDPTE_64_IGNORED_2(_)                                        (((_) >> 52) & 0x7FF)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte region
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PDPTE_64_EXECUTE_DISABLE_BIT                                 63
#define PDPTE_64_EXECUTE_DISABLE_MASK                                0x01
#define PDPTE_64_EXECUTE_DISABLE(_)                                  (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PDPTE_64;

/**
 * @brief Format of a 4-Level Page-Directory Entry that Maps a 2-MByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to map a 2-MByte page.
     */
    UINT64 Present                                                 : 1;
#define PDE_2MB_64_PRESENT_BIT                                       0
#define PDE_2MB_64_PRESENT_MASK                                      0x01
#define PDE_2MB_64_PRESENT(_)                                        (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 2-MByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PDE_2MB_64_WRITE_BIT                                         1
#define PDE_2MB_64_WRITE_MASK                                        0x01
#define PDE_2MB_64_WRITE(_)                                          (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PDE_2MB_64_SUPERVISOR_BIT                                    2
#define PDE_2MB_64_SUPERVISOR_MASK                                   0x01
#define PDE_2MB_64_SUPERVISOR(_)                                     (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 2-MByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH_BIT                      3
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH_MASK                     0x01
#define PDE_2MB_64_PAGE_LEVEL_WRITE_THROUGH(_)                       (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 2-MByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE_BIT                      4
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE_MASK                     0x01
#define PDE_2MB_64_PAGE_LEVEL_CACHE_DISABLE(_)                       (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether software has accessed the 2-MByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PDE_2MB_64_ACCESSED_BIT                                      5
#define PDE_2MB_64_ACCESSED_MASK                                     0x01
#define PDE_2MB_64_ACCESSED(_)                                       (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Dirty; indicates whether software has written to the 2-MByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Dirty                                                   : 1;
#define PDE_2MB_64_DIRTY_BIT                                         6
#define PDE_2MB_64_DIRTY_MASK                                        0x01
#define PDE_2MB_64_DIRTY(_)                                          (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Page size; must be 1 (otherwise, this entry references a page directory).
     */
    UINT64 LargePage                                               : 1;
#define PDE_2MB_64_LARGE_PAGE_BIT                                    7
#define PDE_2MB_64_LARGE_PAGE_MASK                                   0x01
#define PDE_2MB_64_LARGE_PAGE(_)                                     (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
     *
     * @see Vol3A[4.10(Caching Translation Information)]
     */
    UINT64 Global                                                  : 1;
#define PDE_2MB_64_GLOBAL_BIT                                        8
#define PDE_2MB_64_GLOBAL_MASK                                       0x01
#define PDE_2MB_64_GLOBAL(_)                                         (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT64 Ignored1                                                : 3;
#define PDE_2MB_64_IGNORED_1_BIT                                     9
#define PDE_2MB_64_IGNORED_1_MASK                                    0x07
#define PDE_2MB_64_IGNORED_1(_)                                      (((_) >> 9) & 0x07)

    /**
     * [Bit 12] Indirectly determines the memory type used to access the 2-MByte page referenced by this entry.
     *
     * @note The PAT is supported on all processors that support 4-level paging.
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 Pat                                                     : 1;
#define PDE_2MB_64_PAT_BIT                                           12
#define PDE_2MB_64_PAT_MASK                                          0x01
#define PDE_2MB_64_PAT(_)                                            (((_) >> 12) & 0x01)
    UINT64 Reserved1                                               : 17;

    /**
     * [Bits 47:30] Physical address of the 1-GByte page referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 18;
#define PDE_2MB_64_PAGE_FRAME_NUMBER_BIT                             30
#define PDE_2MB_64_PAGE_FRAME_NUMBER_MASK                            0x3FFFF
#define PDE_2MB_64_PAGE_FRAME_NUMBER(_)                              (((_) >> 30) & 0x3FFFF)
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 58:52] Ignored.
     */
    UINT64 Ignored2                                                : 7;
#define PDE_2MB_64_IGNORED_2_BIT                                     52
#define PDE_2MB_64_IGNORED_2_MASK                                    0x7F
#define PDE_2MB_64_IGNORED_2(_)                                      (((_) >> 52) & 0x7F)

    /**
     * [Bits 62:59] Protection key; if CR4.PKE = 1, determines the protection key of the page; ignored otherwise.
     *
     * @see Vol3A[4.6.2(Protection Keys)]
     */
    UINT64 ProtectionKey                                           : 4;
#define PDE_2MB_64_PROTECTION_KEY_BIT                                59
#define PDE_2MB_64_PROTECTION_KEY_MASK                               0x0F
#define PDE_2MB_64_PROTECTION_KEY(_)                                 (((_) >> 59) & 0x0F)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte page
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PDE_2MB_64_EXECUTE_DISABLE_BIT                               63
#define PDE_2MB_64_EXECUTE_DISABLE_MASK                              0x01
#define PDE_2MB_64_EXECUTE_DISABLE(_)                                (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PDE_2MB_64;

/**
 * @brief Format of a 4-Level Page-Directory Entry that References a Page Table
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to reference a page table.
     */
    UINT64 Present                                                 : 1;
#define PDE_64_PRESENT_BIT                                           0
#define PDE_64_PRESENT_MASK                                          0x01
#define PDE_64_PRESENT(_)                                            (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 2-MByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PDE_64_WRITE_BIT                                             1
#define PDE_64_WRITE_MASK                                            0x01
#define PDE_64_WRITE(_)                                              (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte region controlled by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PDE_64_SUPERVISOR_BIT                                        2
#define PDE_64_SUPERVISOR_MASK                                       0x01
#define PDE_64_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the page table referenced by this
     * entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PDE_64_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the page table referenced by this
     * entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PDE_64_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether this entry has been used for linear-address translation.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PDE_64_ACCESSED_BIT                                          5
#define PDE_64_ACCESSED_MASK                                         0x01
#define PDE_64_ACCESSED(_)                                           (((_) >> 5) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 7] Page size; must be 0 (otherwise, this entry maps a 2-MByte page).
     */
    UINT64 LargePage                                               : 1;
#define PDE_64_LARGE_PAGE_BIT                                        7
#define PDE_64_LARGE_PAGE_MASK                                       0x01
#define PDE_64_LARGE_PAGE(_)                                         (((_) >> 7) & 0x01)

    /**
     * [Bits 11:8] Ignored.
     */
    UINT64 Ignored1                                                : 4;
#define PDE_64_IGNORED_1_BIT                                         8
#define PDE_64_IGNORED_1_MASK                                        0x0F
#define PDE_64_IGNORED_1(_)                                          (((_) >> 8) & 0x0F)

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned page table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define PDE_64_PAGE_FRAME_NUMBER_BIT                                 12
#define PDE_64_PAGE_FRAME_NUMBER_MASK                                0xFFFFFFFFF
#define PDE_64_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 62:52] Ignored.
     */
    UINT64 Ignored2                                                : 11;
#define PDE_64_IGNORED_2_BIT                                         52
#define PDE_64_IGNORED_2_MASK                                        0x7FF
#define PDE_64_IGNORED_2(_)                                          (((_) >> 52) & 0x7FF)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-MByte region
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PDE_64_EXECUTE_DISABLE_BIT                                   63
#define PDE_64_EXECUTE_DISABLE_MASK                                  0x01
#define PDE_64_EXECUTE_DISABLE(_)                                    (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PDE_64;

/**
 * @brief Format of a 4-Level Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Present; must be 1 to map a 4-KByte page.
     */
    UINT64 Present                                                 : 1;
#define PTE_64_PRESENT_BIT                                           0
#define PTE_64_PRESENT_MASK                                          0x01
#define PTE_64_PRESENT(_)                                            (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Write                                                   : 1;
#define PTE_64_WRITE_BIT                                             1
#define PTE_64_WRITE_MASK                                            0x01
#define PTE_64_WRITE(_)                                              (((_) >> 1) & 0x01)

    /**
     * [Bit 2] User/supervisor; if 0, user-mode accesses are not allowed to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 Supervisor                                              : 1;
#define PTE_64_SUPERVISOR_BIT                                        2
#define PTE_64_SUPERVISOR_MASK                                       0x01
#define PTE_64_SUPERVISOR(_)                                         (((_) >> 2) & 0x01)

    /**
     * [Bit 3] Page-level write-through; indirectly determines the memory type used to access the 4-KByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelWriteThrough                                   : 1;
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH_BIT                          3
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH_MASK                         0x01
#define PTE_64_PAGE_LEVEL_WRITE_THROUGH(_)                           (((_) >> 3) & 0x01)

    /**
     * [Bit 4] Page-level cache disable; indirectly determines the memory type used to access the 4-KByte page referenced by
     * this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 PageLevelCacheDisable                                   : 1;
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE_BIT                          4
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE_MASK                         0x01
#define PTE_64_PAGE_LEVEL_CACHE_DISABLE(_)                           (((_) >> 4) & 0x01)

    /**
     * [Bit 5] Accessed; indicates whether software has accessed the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Accessed                                                : 1;
#define PTE_64_ACCESSED_BIT                                          5
#define PTE_64_ACCESSED_MASK                                         0x01
#define PTE_64_ACCESSED(_)                                           (((_) >> 5) & 0x01)

    /**
     * [Bit 6] Dirty; indicates whether software has written to the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.8(Accessed and Dirty Flags)]
     */
    UINT64 Dirty                                                   : 1;
#define PTE_64_DIRTY_BIT                                             6
#define PTE_64_DIRTY_MASK                                            0x01
#define PTE_64_DIRTY(_)                                              (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Indirectly determines the memory type used to access the 4-KByte page referenced by this entry.
     *
     * @see Vol3A[4.9.2(Paging and Memory Typing When the PAT is Supported (Pentium III and More Recent Processor Families))]
     */
    UINT64 Pat                                                     : 1;
#define PTE_64_PAT_BIT                                               7
#define PTE_64_PAT_MASK                                              0x01
#define PTE_64_PAT(_)                                                (((_) >> 7) & 0x01)

    /**
     * [Bit 8] Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise.
     *
     * @see Vol3A[4.10(Caching Translation Information)]
     */
    UINT64 Global                                                  : 1;
#define PTE_64_GLOBAL_BIT                                            8
#define PTE_64_GLOBAL_MASK                                           0x01
#define PTE_64_GLOBAL(_)                                             (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT64 Ignored1                                                : 3;
#define PTE_64_IGNORED_1_BIT                                         9
#define PTE_64_IGNORED_1_MASK                                        0x07
#define PTE_64_IGNORED_1(_)                                          (((_) >> 9) & 0x07)

    /**
     * [Bits 47:12] Physical address of the 4-KByte page referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define PTE_64_PAGE_FRAME_NUMBER_BIT                                 12
#define PTE_64_PAGE_FRAME_NUMBER_MASK                                0xFFFFFFFFF
#define PTE_64_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 58:52] Ignored.
     */
    UINT64 Ignored2                                                : 7;
#define PTE_64_IGNORED_2_BIT                                         52
#define PTE_64_IGNORED_2_MASK                                        0x7F
#define PTE_64_IGNORED_2(_)                                          (((_) >> 52) & 0x7F)

    /**
     * [Bits 62:59] Protection key; if CR4.PKE = 1, determines the protection key of the page; ignored otherwise.
     *
     * @see Vol3A[4.6.2(Protection Keys)]
     */
    UINT64 ProtectionKey                                           : 4;
#define PTE_64_PROTECTION_KEY_BIT                                    59
#define PTE_64_PROTECTION_KEY_MASK                                   0x0F
#define PTE_64_PROTECTION_KEY(_)                                     (((_) >> 59) & 0x0F)

    /**
     * [Bit 63] If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte page
     * controlled by this entry); otherwise, reserved (must be 0).
     *
     * @see Vol3A[4.6(Access Rights)]
     */
    UINT64 ExecuteDisable                                          : 1;
#define PTE_64_EXECUTE_DISABLE_BIT                                   63
#define PTE_64_EXECUTE_DISABLE_MASK                                  0x01
#define PTE_64_EXECUTE_DISABLE(_)                                    (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PTE_64;

/**
 * @brief Format of a common Page-Table Entry
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
#define PT_ENTRY_64_PRESENT_BIT                                      0
#define PT_ENTRY_64_PRESENT_MASK                                     0x01
#define PT_ENTRY_64_PRESENT(_)                                       (((_) >> 0) & 0x01)
    UINT64 Write                                                   : 1;
#define PT_ENTRY_64_WRITE_BIT                                        1
#define PT_ENTRY_64_WRITE_MASK                                       0x01
#define PT_ENTRY_64_WRITE(_)                                         (((_) >> 1) & 0x01)
    UINT64 Supervisor                                              : 1;
#define PT_ENTRY_64_SUPERVISOR_BIT                                   2
#define PT_ENTRY_64_SUPERVISOR_MASK                                  0x01
#define PT_ENTRY_64_SUPERVISOR(_)                                    (((_) >> 2) & 0x01)
    UINT64 PageLevelWriteThrough                                   : 1;
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH_BIT                     3
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH_MASK                    0x01
#define PT_ENTRY_64_PAGE_LEVEL_WRITE_THROUGH(_)                      (((_) >> 3) & 0x01)
    UINT64 PageLevelCacheDisable                                   : 1;
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE_BIT                     4
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE_MASK                    0x01
#define PT_ENTRY_64_PAGE_LEVEL_CACHE_DISABLE(_)                      (((_) >> 4) & 0x01)
    UINT64 Accessed                                                : 1;
#define PT_ENTRY_64_ACCESSED_BIT                                     5
#define PT_ENTRY_64_ACCESSED_MASK                                    0x01
#define PT_ENTRY_64_ACCESSED(_)                                      (((_) >> 5) & 0x01)
    UINT64 Dirty                                                   : 1;
#define PT_ENTRY_64_DIRTY_BIT                                        6
#define PT_ENTRY_64_DIRTY_MASK                                       0x01
#define PT_ENTRY_64_DIRTY(_)                                         (((_) >> 6) & 0x01)
    UINT64 LargePage                                               : 1;
#define PT_ENTRY_64_LARGE_PAGE_BIT                                   7
#define PT_ENTRY_64_LARGE_PAGE_MASK                                  0x01
#define PT_ENTRY_64_LARGE_PAGE(_)                                    (((_) >> 7) & 0x01)
    UINT64 Global                                                  : 1;
#define PT_ENTRY_64_GLOBAL_BIT                                       8
#define PT_ENTRY_64_GLOBAL_MASK                                      0x01
#define PT_ENTRY_64_GLOBAL(_)                                        (((_) >> 8) & 0x01)

    /**
     * [Bits 11:9] Ignored.
     */
    UINT64 Ignored1                                                : 3;
#define PT_ENTRY_64_IGNORED_1_BIT                                    9
#define PT_ENTRY_64_IGNORED_1_MASK                                   0x07
#define PT_ENTRY_64_IGNORED_1(_)                                     (((_) >> 9) & 0x07)

    /**
     * [Bits 47:12] Physical address of the 4-KByte page referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define PT_ENTRY_64_PAGE_FRAME_NUMBER_BIT                            12
#define PT_ENTRY_64_PAGE_FRAME_NUMBER_MASK                           0xFFFFFFFFF
#define PT_ENTRY_64_PAGE_FRAME_NUMBER(_)                             (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved1                                               : 4;

    /**
     * [Bits 58:52] Ignored.
     */
    UINT64 Ignored2                                                : 7;
#define PT_ENTRY_64_IGNORED_2_BIT                                    52
#define PT_ENTRY_64_IGNORED_2_MASK                                   0x7F
#define PT_ENTRY_64_IGNORED_2(_)                                     (((_) >> 52) & 0x7F)
    UINT64 ProtectionKey                                           : 4;
#define PT_ENTRY_64_PROTECTION_KEY_BIT                               59
#define PT_ENTRY_64_PROTECTION_KEY_MASK                              0x0F
#define PT_ENTRY_64_PROTECTION_KEY(_)                                (((_) >> 59) & 0x0F)
    UINT64 ExecuteDisable                                          : 1;
#define PT_ENTRY_64_EXECUTE_DISABLE_BIT                              63
#define PT_ENTRY_64_EXECUTE_DISABLE_MASK                             0x01
#define PT_ENTRY_64_EXECUTE_DISABLE(_)                               (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} PT_ENTRY_64;

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup SEGMENT_DESCRIPTORS \
 *           Segment descriptors
 * @{
 */
/**
 * @brief Pseudo-Descriptor Format (32-bit)
 *
 * @see Vol3A[3.5.1(Segment Descriptor Tables)] (reference)
 */
#include <pshpack1.h>
typedef struct
{
  UINT16 Limit;
  UINT32 BaseAddress;
} DESCRIPTOR_32;
#include <poppack.h>

/**
 * @brief Pseudo-Descriptor Format (64-bit)
 *
 * @see Vol3A[3.5.1(Segment Descriptor Tables)] (reference)
 */
#include <pshpack1.h>
typedef struct
{
  UINT16 Limit;
  UINT64 BaseAddress;
} DESCRIPTOR_64;
#include <poppack.h>

/**
 * @brief General Segment Descriptor (32-bit)
 *
 * A segment descriptor is a data structure in a GDT or LDT that provides the processor with the size and location of a
 * segment, as well as access control and status information. Segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 *
 * @see Vol3A[5.2(FIELDS AND FLAGS USED FOR SEGMENT-LEVEL AND PAGE-LEVEL PROTECTION)]
 * @see Vol3A[5.2.1(Code-Segment Descriptor in 64-bit Mode)]
 * @see Vol3A[5.8.3(Call Gates)]
 * @see Vol3A[6.11(IDT DESCRIPTORS)]
 * @see Vol3A[6.14.1(64-Bit Mode IDT)]
 * @see Vol3A[7.2.2(TSS Descriptor)]
 * @see Vol3A[7.2.3(TSS Descriptor in 64-bit mode)]
 * @see Vol3A[7.2.5(Task-Gate Descriptor)]
 * @see Vol3A[3.4.5(Segment Descriptors)] (reference)
 */
typedef struct
{
  UINT16 SegmentLimitLow;
  UINT16 BaseAddressLow;
  /**
   * @brief Segment descriptor fields
   */
  union
  {
    struct
    {
      /**
       * [Bits 7:0] Base address field (23:16); see description of $BASE_LOW for more details.
       */
      UINT32 BaseAddressMiddle                                     : 8;
#define BITS_BASE_ADDRESS_MIDDLE_BIT                                 0
#define BITS_BASE_ADDRESS_MIDDLE_MASK                                0xFF
#define BITS_BASE_ADDRESS_MIDDLE(_)                                  (((_) >> 0) & 0xFF)

      /**
       * @brief Type field
       *
       * [Bits 11:8] Indicates the segment or gate type and specifies the kinds of access that can be made to the segment and the
       * direction of growth. The interpretation of this field depends on whether the descriptor type flag specifies an
       * application (code or data) descriptor or a system descriptor. The encoding of the type field is different for code,
       * data, and system descriptors.
       *
       * @see Vol3A[3.4.5.1(Code- and Data-Segment Descriptor Types)]
       */
      UINT32 Type                                                  : 4;
#define BITS_TYPE_BIT                                                8
#define BITS_TYPE_MASK                                               0x0F
#define BITS_TYPE(_)                                                 (((_) >> 8) & 0x0F)

      /**
       * @brief S (descriptor type) flag
       *
       * [Bit 12] Specifies whether the segment descriptor is for a system segment (S flag is clear) or a code or data segment (S
       * flag is set).
       */
      UINT32 DescriptorType                                        : 1;
#define BITS_DESCRIPTOR_TYPE_BIT                                     12
#define BITS_DESCRIPTOR_TYPE_MASK                                    0x01
#define BITS_DESCRIPTOR_TYPE(_)                                      (((_) >> 12) & 0x01)

      /**
       * @brief DPL (descriptor privilege level) field
       *
       * [Bits 14:13] Specifies the privilege level of the segment. The privilege level can range from 0 to 3, with 0 being the
       * most privileged level. The DPL is used to control access to the segment. See Section 5.5, "Privilege Levels", for a
       * description of the relationship of the DPL to the CPL of the executing code segment and the RPL of a segment selector.
       */
      UINT32 DescriptorPrivilegeLevel                              : 2;
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL_BIT                          13
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL_MASK                         0x03
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL(_)                           (((_) >> 13) & 0x03)

      /**
       * @brief P (segment-present) flag
       *
       * [Bit 15] Indicates whether the segment is present in memory (set) or not present (clear). If this flag is clear, the
       * processor generates a segment-not-present exception (\#NP) when a segment selector that points to the segment descriptor
       * is loaded into a segment register. Memory management software can use this flag to control which segments are actually
       * loaded into physical memory at a given time. It offers a control in addition to paging for managing virtual memory.
       */
      UINT32 Present                                               : 1;
#define BITS_PRESENT_BIT                                             15
#define BITS_PRESENT_MASK                                            0x01
#define BITS_PRESENT(_)                                              (((_) >> 15) & 0x01)

      /**
       * [Bits 19:16] Segment limit field (19:16); see description of $LIMIT_LOW for more details.
       */
      UINT32 SegmentLimitHigh                                      : 4;
#define BITS_SEGMENT_LIMIT_HIGH_BIT                                  16
#define BITS_SEGMENT_LIMIT_HIGH_MASK                                 0x0F
#define BITS_SEGMENT_LIMIT_HIGH(_)                                   (((_) >> 16) & 0x0F)

      /**
       * @brief Available bit
       *
       * [Bit 20] Bit 20 of the second doubleword of the segment descriptor is available for use by system software.
       */
      UINT32 System                                                : 1;
#define BITS_SYSTEM_BIT                                              20
#define BITS_SYSTEM_MASK                                             0x01
#define BITS_SYSTEM(_)                                               (((_) >> 20) & 0x01)

      /**
       * @brief L (64-bit code segment) flag
       *
       * [Bit 21] In IA-32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a code segment
       * contains native 64-bit code. A value of 1 indicates instructions in this code segment are executed in 64-bit mode. A
       * value of 0 indicates the instructions in this code segment are executed in compatibility mode. If L-bit is set, then
       * D-bit must be cleared. When not in IA-32e mode or for non-code segments, bit 21 is reserved and should always be set to
       * 0.
       */
      UINT32 LongMode                                              : 1;
#define BITS_LONG_MODE_BIT                                           21
#define BITS_LONG_MODE_MASK                                          0x01
#define BITS_LONG_MODE(_)                                            (((_) >> 21) & 0x01)

      /**
       * @brief D/B (default operation size/default stack pointer size and/or upper bound) flag
       *
       * [Bit 22] Performs different functions depending on whether the segment descriptor is an executable code segment, an
       * expand-down data segment, or a stack segment. (This flag should always be set to 1 for 32-bit code and data segments and
       * to 0 for 16-bit code and data segments.)
       * - Executable code segment. The flag is called the D flag and it indicates the default length for effective addresses and
       * operands referenced by instructions in the segment. If the flag is set, 32-bit addresses and 32-bit or 8-bit operands
       * are assumed; if it is clear, 16-bit addresses and 16-bit or 8-bit operands are assumed. The instruction prefix 66H can
       * be used to select an operand size other than the default, and the prefix 67H can be used select an address size other
       * than the default.
       * - Stack segment (data segment pointed to by the SS register). The flag is called the B (big) flag and it specifies the
       * size of the stack pointer used for implicit stack operations (such as pushes, pops, and calls). If the flag is set, a
       * 32-bit stack pointer is used, which is stored in the 32-bit ESP register; if the flag is clear, a 16-bit stack pointer
       * is used, which is stored in the 16- bit SP register. If the stack segment is set up to be an expand-down data segment
       * (described in the next paragraph), the B flag also specifies the upper bound of the stack segment.
       * - Expand-down data segment. The flag is called the B flag and it specifies the upper bound of the segment. If the flag
       * is set, the upper bound is FFFFFFFFH (4 GBytes); if the flag is clear, the upper bound is FFFFH (64 KBytes).
       */
      UINT32 DefaultBig                                            : 1;
#define BITS_DEFAULT_BIG_BIT                                         22
#define BITS_DEFAULT_BIG_MASK                                        0x01
#define BITS_DEFAULT_BIG(_)                                          (((_) >> 22) & 0x01)

      /**
       * @brief G (granularity) flag
       *
       * [Bit 23] Determines the scaling of the segment limit field. When the granularity flag is clear, the segment limit is
       * interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units. (This flag does not
       * affect the granularity of the base address; it is always byte granular.) When the granularity flag is set, the twelve
       * least significant bits of an offset are not tested when checking the offset against the segment limit. For example, when
       * the granularity flag is set, a limit of 0 results in valid offsets from 0 to 4095.
       */
      UINT32 Granularity                                           : 1;
#define BITS_GRANULARITY_BIT                                         23
#define BITS_GRANULARITY_MASK                                        0x01
#define BITS_GRANULARITY(_)                                          (((_) >> 23) & 0x01)

      /**
       * [Bits 31:24] Base address field (31:24); see description of $BASE_LOW for more details.
       */
      UINT32 BaseAddressHigh                                       : 8;
#define BITS_BASE_ADDRESS_HIGH_BIT                                   24
#define BITS_BASE_ADDRESS_HIGH_MASK                                  0xFF
#define BITS_BASE_ADDRESS_HIGH(_)                                    (((_) >> 24) & 0xFF)
    };

    UINT32 Flags;
  } Bits;

} SEGMENT_DESCRIPTOR_32;

/**
 * @brief General Segment Descriptor (64-bit)
 *
 * A segment descriptor is a data structure in a GDT or LDT that provides the processor with the size and location of a
 * segment, as well as access control and status information. Segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 *
 * @see Vol3A[3.4.5(Segment Descriptors)] (reference)
 */
typedef struct
{
  UINT16 SegmentLimitLow;
  UINT16 BaseAddressLow;
  /**
   * @brief Segment descriptor fields
   */
  union
  {
    struct
    {
      /**
       * [Bits 7:0] Base address field (23:16); see description of $BASE_LOW for more details.
       */
      UINT32 BaseAddressMiddle                                     : 8;
#define BITS_BASE_ADDRESS_MIDDLE_BIT                                 0
#define BITS_BASE_ADDRESS_MIDDLE_MASK                                0xFF
#define BITS_BASE_ADDRESS_MIDDLE(_)                                  (((_) >> 0) & 0xFF)

      /**
       * @brief Type field
       *
       * [Bits 11:8] Indicates the segment or gate type and specifies the kinds of access that can be made to the segment and the
       * direction of growth. The interpretation of this field depends on whether the descriptor type flag specifies an
       * application (code or data) descriptor or a system descriptor. The encoding of the type field is different for code,
       * data, and system descriptors.
       *
       * @see Vol3A[3.4.5.1(Code- and Data-Segment Descriptor Types)]
       */
      UINT32 Type                                                  : 4;
#define BITS_TYPE_BIT                                                8
#define BITS_TYPE_MASK                                               0x0F
#define BITS_TYPE(_)                                                 (((_) >> 8) & 0x0F)

      /**
       * @brief S (descriptor type) flag
       *
       * [Bit 12] Specifies whether the segment descriptor is for a system segment (S flag is clear) or a code or data segment (S
       * flag is set).
       */
      UINT32 DescriptorType                                        : 1;
#define BITS_DESCRIPTOR_TYPE_BIT                                     12
#define BITS_DESCRIPTOR_TYPE_MASK                                    0x01
#define BITS_DESCRIPTOR_TYPE(_)                                      (((_) >> 12) & 0x01)

      /**
       * @brief DPL (descriptor privilege level) field
       *
       * [Bits 14:13] Specifies the privilege level of the segment. The privilege level can range from 0 to 3, with 0 being the
       * most privileged level. The DPL is used to control access to the segment. See Section 5.5, "Privilege Levels", for a
       * description of the relationship of the DPL to the CPL of the executing code segment and the RPL of a segment selector.
       */
      UINT32 DescriptorPrivilegeLevel                              : 2;
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL_BIT                          13
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL_MASK                         0x03
#define BITS_DESCRIPTOR_PRIVILEGE_LEVEL(_)                           (((_) >> 13) & 0x03)

      /**
       * @brief P (segment-present) flag
       *
       * [Bit 15] Indicates whether the segment is present in memory (set) or not present (clear). If this flag is clear, the
       * processor generates a segment-not-present exception (\#NP) when a segment selector that points to the segment descriptor
       * is loaded into a segment register. Memory management software can use this flag to control which segments are actually
       * loaded into physical memory at a given time. It offers a control in addition to paging for managing virtual memory.
       */
      UINT32 Present                                               : 1;
#define BITS_PRESENT_BIT                                             15
#define BITS_PRESENT_MASK                                            0x01
#define BITS_PRESENT(_)                                              (((_) >> 15) & 0x01)

      /**
       * [Bits 19:16] Segment limit field (19:16); see description of $LIMIT_LOW for more details.
       */
      UINT32 SegmentLimitHigh                                      : 4;
#define BITS_SEGMENT_LIMIT_HIGH_BIT                                  16
#define BITS_SEGMENT_LIMIT_HIGH_MASK                                 0x0F
#define BITS_SEGMENT_LIMIT_HIGH(_)                                   (((_) >> 16) & 0x0F)

      /**
       * @brief Available bit
       *
       * [Bit 20] Bit 20 of the second doubleword of the segment descriptor is available for use by system software.
       */
      UINT32 System                                                : 1;
#define BITS_SYSTEM_BIT                                              20
#define BITS_SYSTEM_MASK                                             0x01
#define BITS_SYSTEM(_)                                               (((_) >> 20) & 0x01)

      /**
       * @brief L (64-bit code segment) flag
       *
       * [Bit 21] In IA-32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a code segment
       * contains native 64-bit code. A value of 1 indicates instructions in this code segment are executed in 64-bit mode. A
       * value of 0 indicates the instructions in this code segment are executed in compatibility mode. If L-bit is set, then
       * D-bit must be cleared. When not in IA-32e mode or for non-code segments, bit 21 is reserved and should always be set to
       * 0.
       */
      UINT32 LongMode                                              : 1;
#define BITS_LONG_MODE_BIT                                           21
#define BITS_LONG_MODE_MASK                                          0x01
#define BITS_LONG_MODE(_)                                            (((_) >> 21) & 0x01)

      /**
       * @brief D/B (default operation size/default stack pointer size and/or upper bound) flag
       *
       * [Bit 22] Performs different functions depending on whether the segment descriptor is an executable code segment, an
       * expand-down data segment, or a stack segment. (This flag should always be set to 1 for 32-bit code and data segments and
       * to 0 for 16-bit code and data segments.)
       * - Executable code segment. The flag is called the D flag and it indicates the default length for effective addresses and
       * operands referenced by instructions in the segment. If the flag is set, 32-bit addresses and 32-bit or 8-bit operands
       * are assumed; if it is clear, 16-bit addresses and 16-bit or 8-bit operands are assumed. The instruction prefix 66H can
       * be used to select an operand size other than the default, and the prefix 67H can be used select an address size other
       * than the default.
       * - Stack segment (data segment pointed to by the SS register). The flag is called the B (big) flag and it specifies the
       * size of the stack pointer used for implicit stack operations (such as pushes, pops, and calls). If the flag is set, a
       * 32-bit stack pointer is used, which is stored in the 32-bit ESP register; if the flag is clear, a 16-bit stack pointer
       * is used, which is stored in the 16- bit SP register. If the stack segment is set up to be an expand-down data segment
       * (described in the next paragraph), the B flag also specifies the upper bound of the stack segment.
       * - Expand-down data segment. The flag is called the B flag and it specifies the upper bound of the segment. If the flag
       * is set, the upper bound is FFFFFFFFH (4 GBytes); if the flag is clear, the upper bound is FFFFH (64 KBytes).
       */
      UINT32 DefaultBig                                            : 1;
#define BITS_DEFAULT_BIG_BIT                                         22
#define BITS_DEFAULT_BIG_MASK                                        0x01
#define BITS_DEFAULT_BIG(_)                                          (((_) >> 22) & 0x01)

      /**
       * @brief G (granularity) flag
       *
       * [Bit 23] Determines the scaling of the segment limit field. When the granularity flag is clear, the segment limit is
       * interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units. (This flag does not
       * affect the granularity of the base address; it is always byte granular.) When the granularity flag is set, the twelve
       * least significant bits of an offset are not tested when checking the offset against the segment limit. For example, when
       * the granularity flag is set, a limit of 0 results in valid offsets from 0 to 4095.
       */
      UINT32 Granularity                                           : 1;
#define BITS_GRANULARITY_BIT                                         23
#define BITS_GRANULARITY_MASK                                        0x01
#define BITS_GRANULARITY(_)                                          (((_) >> 23) & 0x01)

      /**
       * [Bits 31:24] Base address field (31:24); see description of $BASE_LOW for more details.
       */
      UINT32 BaseAddressHigh                                       : 8;
#define BITS_BASE_ADDRESS_HIGH_BIT                                   24
#define BITS_BASE_ADDRESS_HIGH_MASK                                  0xFF
#define BITS_BASE_ADDRESS_HIGH(_)                                    (((_) >> 24) & 0xFF)
    };

    UINT32 Flags;
  } Bits;

  UINT32 BaseAddressUpper;
  UINT32 MustBeZero;
} SEGMENT_DESCRIPTOR_64;

/**
 * @defgroup CODE_AND_DATA_SEGMENT_DESCRIPTOR_TYPE \
 *           Code- and Data-Segment Descriptor Types
 *
 * When the S (descriptor type) flag in a segment descriptor is set, the descriptor is for either a code or a data segment.
 * The highest order bit of the type field (bit 11 of the second double word of the segment descriptor) then determines
 * whether the descriptor is for a data segment (clear) or a code segment (set). For data segments, the three low-order
 * bits of the type field (bits 8, 9, and 10) are interpreted as accessed (A), write-enable (W), and expansion-direction
 * (E). See Table 3-1 for a description of the encoding of the bits in the type field for code and data segments. Data
 * segments can be read-only or read/write segments, depending on the setting of the write-enable bit.
 *
 * @see Vol3A[3.4.5.1(Code- and Data-Segment Descriptor Types)] (reference)
 * @{
 */
/**
 * Read-Only.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY                               0x00000000

/**
 * Data Read-Only, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_ACCESSED                      0x00000001

/**
 * Data Read/Write.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE                              0x00000002

/**
 * Data Read/Write, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_ACCESSED                     0x00000003

/**
 * Data Read-Only, expand-down.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_EXPAND_DOWN                   0x00000004

/**
 * Data Read-Only, expand-down, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_EXPAND_DOWN_ACCESSED          0x00000005

/**
 * Data Read/Write, expand-down.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_EXPAND_DOWN                  0x00000006

/**
 * Data Read/Write, expand-down, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_EXPAND_DOWN_ACCESSED         0x00000007

/**
 * Code Execute-Only.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY                            0x00000008

/**
 * Code Execute-Only, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_ACCESSED                   0x00000009

/**
 * Code Execute/Read.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ                            0x0000000A

/**
 * Code Execute/Read, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_ACCESSED                   0x0000000B

/**
 * Code Execute-Only, conforming.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_CONFORMING                 0x0000000C

/**
 * Code Execute-Only, conforming, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_CONFORMING_ACCESSED        0x0000000D

/**
 * Code Execute/Read, conforming.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_CONFORMING                 0x0000000E

/**
 * Code Execute/Read, conforming, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_CONFORMING_ACCESSED        0x0000000F

/**
 * @}
 */

/**
 * @defgroup SYSTEM_DESCRIPTOR_TYPE \
 *           System Descriptor Types
 *
 * When the S (descriptor type) flag in a segment descriptor is clear, the descriptor type is a system descriptor. The
 * processor recognizes the following types of system descriptors:
 * - Local descriptor-table (LDT) segment descriptor.
 * - Task-state segment (TSS) descriptor.
 * - Call-gate descriptor.
 * - Interrupt-gate descriptor.
 * - Trap-gate descriptor.
 * - Task-gate descriptor.
 * These descriptor types fall into two categories: system-segment descriptors and gate descriptors. Systemsegment
 * descriptors point to system segments (LDT and TSS segments). Gate descriptors are in themselves "gates," which hold
 * pointers to procedure entry points in code segments (call, interrupt, and trap gates) or which hold segment selectors
 * for TSS's (task gates).
 *
 * @see Vol3A[3.5(SYSTEM DESCRIPTOR TYPES)] (reference)
 * @{
 */
/**
 * - 32-Bit Mode: Reserved
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_1                                   0x00000000

/**
 * - 32-Bit Mode: 16-bit TSS (Available)
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TSS_16_AVAILABLE                             0x00000001

/**
 * - 32-Bit Mode: LDT
 * - IA-32e Mode: LDT
 */
#define DESCRIPTOR_TYPE_LDT                                          0x00000002

/**
 * - 32-Bit Mode: 16-bit TSS (Busy)
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TSS_16_BUSY                                  0x00000003

/**
 * - 32-Bit Mode: 16-bit Call Gate
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_CALL_GATE_16                                 0x00000004

/**
 * - 32-Bit Mode: Task Gate
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TASK_GATE                                    0x00000005

/**
 * - 32-Bit Mode: 16-bit Interrupt Gate
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_INTERRUPT_GATE_16                            0x00000006

/**
 * - 32-Bit Mode: 16-bit Trap Gate
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TRAP_GATE_16                                 0x00000007

/**
 * - 32-Bit Mode: Reserved
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_2                                   0x00000008

/**
 * - 32-Bit Mode: 32-bit TSS (Available)
 * - IA-32e Mode: 64-bit TSS (Available)
 */
#define DESCRIPTOR_TYPE_TSS_AVAILABLE                                0x00000009

/**
 * - 32-Bit Mode: Reserved
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_3                                   0x0000000A

/**
 * - 32-Bit Mode: 32-bit TSS (Busy)
 * - IA-32e Mode: 64-bit TSS (Busy)
 */
#define DESCRIPTOR_TYPE_TSS_BUSY                                     0x0000000B

/**
 * - 32-Bit Mode: 32-bit Call Gate
 * - IA-32e Mode: 64-bit Call Gate
 */
#define DESCRIPTOR_TYPE_CALL_GATE                                    0x0000000C

/**
 * - 32-Bit Mode: Reserved
 * - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_4                                   0x0000000D

/**
 * - 32-Bit Mode: 32-bit Interrupt Gate
 * - IA-32e Mode: 64-bit Interrupt Gate
 */
#define DESCRIPTOR_TYPE_INTERRUPT_GATE                               0x0000000E

/**
 * - 32-Bit Mode: 32-bit Trap Gate
 * - IA-32e Mode: 64-bit Trap Gate
 */
#define DESCRIPTOR_TYPE_TRAP_GATE                                    0x0000000F

/**
 * @}
 */

/**
 * @brief A segment selector is a 16-bit identifier for a segment. It does not point directly to the segment, but instead
 *        points to the segment descriptor that defines the segment
 *
 * @see Vol3A[3.4.2(Segment Selectors)] (reference)
 */
typedef union
{
  struct
  {
    /**
     * [Bits 1:0] Specifies the privilege level of the selector. The privilege level can range from 0 to 3, with 0 being the
     * most privileged level.
     *
     * @see Vol3A[5.5(Privilege Levels)]
     */
    UINT16 RequestPrivilegeLevel                                   : 2;
#define SELECTOR_REQUEST_PRIVILEGE_LEVEL_BIT                         0
#define SELECTOR_REQUEST_PRIVILEGE_LEVEL_MASK                        0x03
#define SELECTOR_REQUEST_PRIVILEGE_LEVEL(_)                          (((_) >> 0) & 0x03)

    /**
     * [Bit 2] Specifies the descriptor table to use: clearing this flag selects the GDT; setting this flag selects the current
     * LDT.
     */
    UINT16 Table                                                   : 1;
#define SELECTOR_TABLE_BIT                                           2
#define SELECTOR_TABLE_MASK                                          0x01
#define SELECTOR_TABLE(_)                                            (((_) >> 2) & 0x01)

    /**
     * [Bits 16:3] Selects one of 8192 descriptors in the GDT or LDT. The processor multiplies the index value by 8 (the number
     * of bytes in a segment descriptor) and adds the result to the base address of the GDT or LDT (from the GDTR or LDTR
     * register, respectively).
     */
    UINT16 Index                                                   : 14;
#define SELECTOR_INDEX_BIT                                           3
#define SELECTOR_INDEX_MASK                                          0x3FFF
#define SELECTOR_INDEX(_)                                            (((_) >> 3) & 0x3FFF)
  };

  UINT16 Flags;
} SELECTOR;

/**
 * @}
 */

/**
 * @defgroup VMX \
 *           VMX
 * @{
 */
/**
 * @defgroup VMX_BASIC_EXIT_REASONS \
 *           VMX Basic Exit Reasons
 *
 * VMX Basic Exit Reasons.
 *
 * @see Vol3D[C(VMX BASIC EXIT REASONS)] (reference)
 * @{
 */
/**
 * @brief Exception or non-maskable interrupt (NMI)
 *
 * Either:
 * -# Guest software caused an exception and the bit in the exception bitmap associated with exception's vector was 1. This
 * case includes executions of BOUND that cause \#BR, executions of INT1 (they cause \#DB), executions of INT3 (they cause
 * \#BP), executions of INTO that cause \#OF, and executions of UD0, UD1, and UD2 (they cause \#UD).
 * -# An NMI was delivered to the logical processor and the "NMI exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXCEPTION_OR_NMI                             0x00000000

/**
 * @brief External interrupt
 *
 * An external interrupt arrived and the "external-interrupt exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXTERNAL_INTERRUPT                           0x00000001

/**
 * @brief Triple fault
 *
 * The logical processor encountered an exception while attempting to call the double-fault handler and that exception did
 * not itself cause a VM exit due to the exception bitmap.
 */
#define VMX_EXIT_REASON_TRIPLE_FAULT                                 0x00000002

/**
 * @brief INIT signal
 *
 * An INIT signal arrived.
 */
#define VMX_EXIT_REASON_INIT_SIGNAL                                  0x00000003

/**
 * @brief Start-up IPI (SIPI)
 *
 * A SIPI arrived while the logical processor was in the "wait-for-SIPI" state.
 */
#define VMX_EXIT_REASON_STARTUP_IPI                                  0x00000004

/**
 * @brief I/O system-management interrupt (SMI)
 *
 * An SMI arrived immediately after retirement of an I/O instruction and caused an SMM VM exit.
 *
 * @see Vol3C[34.15.2(SMM VM Exits)]
 */
#define VMX_EXIT_REASON_IO_SMI                                       0x00000005

/**
 * @brief Other SMI
 *
 * An SMI arrived and caused an SMM VM exit but not immediately after retirement of an I/O instruction.
 *
 * @see Vol3C[34.15.2(SMM VM Exits)]
 */
#define VMX_EXIT_REASON_SMI                                          0x00000006

/**
 * @brief Interrupt window exiting
 *
 * At the beginning of an instruction, RFLAGS.IF was 1; events were not blocked by STI or by MOV SS; and the
 * "interrupt-window exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_INTERRUPT_WINDOW                             0x00000007

/**
 * @brief NMI window exiting
 *
 * At the beginning of an instruction, there was no virtual-NMI blocking; events were not blocked by MOV SS; and the
 * "NMI-window exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_NMI_WINDOW                                   0x00000008

/**
 * @brief Task switch
 *
 * Guest software attempted a task switch.
 */
#define VMX_EXIT_REASON_TASK_SWITCH                                  0x00000009

/**
 * @brief CPUID
 *
 * Guest software attempted to execute CPUID.
 */
#define VMX_EXIT_REASON_EXECUTE_CPUID                                0x0000000A

/**
 * @brief GETSEC
 *
 * Guest software attempted to execute GETSEC.
 */
#define VMX_EXIT_REASON_EXECUTE_GETSEC                               0x0000000B

/**
 * @brief HLT
 *
 * Guest software attempted to execute HLT and the "HLT exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_HLT                                  0x0000000C

/**
 * @brief INVD
 *
 * Guest software attempted to execute INVD.
 */
#define VMX_EXIT_REASON_EXECUTE_INVD                                 0x0000000D

/**
 * @brief INVLPG
 *
 * Guest software attempted to execute INVLPG and the "INVLPG exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_INVLPG                               0x0000000E

/**
 * @brief RDPMC
 *
 * Guest software attempted to execute RDPMC and the "RDPMC exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDPMC                                0x0000000F

/**
 * @brief RDTSC
 *
 * Guest software attempted to execute RDTSC and the "RDTSC exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDTSC                                0x00000010

/**
 * @brief RSM in SMM
 *
 * Guest software attempted to execute RSM in SMM.
 */
#define VMX_EXIT_REASON_EXECUTE_RSM_IN_SMM                           0x00000011

/**
 * @brief VMCALL
 *
 * VMCALL was executed either by guest software (causing an ordinary VM exit) or by the executive monitor (causing an SMM
 * VM exit).
 *
 * @see Vol3C[34.15.2(SMM VM Exits)]
 */
#define VMX_EXIT_REASON_EXECUTE_VMCALL                               0x00000012

/**
 * @brief VMCLEAR
 *
 * Guest software attempted to execute VMCLEAR.
 */
#define VMX_EXIT_REASON_EXECUTE_VMCLEAR                              0x00000013

/**
 * @brief VMLAUNCH
 *
 * Guest software attempted to execute VMLAUNCH.
 */
#define VMX_EXIT_REASON_EXECUTE_VMLAUNCH                             0x00000014

/**
 * @brief VMPTRLD
 *
 * Guest software attempted to execute VMPTRLD.
 */
#define VMX_EXIT_REASON_EXECUTE_VMPTRLD                              0x00000015

/**
 * @brief VMPTRST
 *
 * Guest software attempted to execute VMPTRST.
 */
#define VMX_EXIT_REASON_EXECUTE_VMPTRST                              0x00000016

/**
 * @brief VMREAD
 *
 * Guest software attempted to execute VMREAD.
 */
#define VMX_EXIT_REASON_EXECUTE_VMREAD                               0x00000017

/**
 * @brief VMRESUME
 *
 * Guest software attempted to execute VMRESUME.
 */
#define VMX_EXIT_REASON_EXECUTE_VMRESUME                             0x00000018

/**
 * @brief VMWRITE
 *
 * Guest software attempted to execute VMWRITE.
 */
#define VMX_EXIT_REASON_EXECUTE_VMWRITE                              0x00000019

/**
 * @brief VMXOFF
 *
 * Guest software attempted to execute VMXOFF.
 */
#define VMX_EXIT_REASON_EXECUTE_VMXOFF                               0x0000001A

/**
 * @brief VMXON
 *
 * Guest software attempted to execute VMXON.
 */
#define VMX_EXIT_REASON_EXECUTE_VMXON                                0x0000001B

/**
 * @brief Control-register accesses
 *
 * Guest software attempted to access CR0, CR3, CR4, or CR8 using CLTS, LMSW, or MOV CR and the VM-execution control fields
 * indicate that a VM exit should occur. This basic exit reason is not used for trap-like VM exits following executions of
 * the MOV to CR8 instruction when the "use TPR shadow" VM-execution control is 1. Such VM exits instead use basic exit
 * reason 43.
 *
 * @see Vol3C[25.1(INSTRUCTIONS THAT CAUSE VM EXITS)]
 */
#define VMX_EXIT_REASON_MOV_CR                                       0x0000001C

/**
 * @brief Debug-register accesses
 *
 * Guest software attempted a MOV to or from a debug register and the "MOV-DR exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_MOV_DR                                       0x0000001D

/**
 * @brief I/O instruction
 *
 * Guest software attempted to execute an I/O instruction and either:
 * -# The "use I/O bitmaps" VM-execution control was 0 and the "unconditional I/O exiting" VM-execution control was 1.
 * -# The "use I/O bitmaps" VM-execution control was 1 and a bit in the I/O bitmap associated with one of the ports
 * accessed by the I/O instruction was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_IO_INSTRUCTION                       0x0000001E

/**
 * @brief RDMSR
 *
 * Guest software attempted to execute RDMSR and either:
 * -# The "use MSR bitmaps" VM-execution control was 0.
 * -# The value of RCX is neither in the range 00000000H - 00001FFFH nor in the range C0000000H - C0001FFFH.
 * -# The value of RCX was in the range 00000000H - 00001FFFH and the nth bit in read bitmap for low MSRs is 1, where n was
 * the value of RCX.
 * -# The value of RCX is in the range C0000000H - C0001FFFH and the nth bit in read bitmap for high MSRs is 1, where n is
 * the value of RCX & 00001FFFH.
 */
#define VMX_EXIT_REASON_EXECUTE_RDMSR                                0x0000001F

/**
 * @brief WRMSR
 *
 * Guest software attempted to execute WRMSR and either:
 * -# The "use MSR bitmaps" VM-execution control was 0.
 * -# The value of RCX is neither in the range 00000000H - 00001FFFH nor in the range C0000000H - C0001FFFH.
 * -# The value of RCX was in the range 00000000H - 00001FFFH and the nth bit in write bitmap for low MSRs is 1, where n
 * was the value of RCX.
 * -# The value of RCX is in the range C0000000H - C0001FFFH and the nth bit in write bitmap for high MSRs is 1, where n is
 * the value of RCX & 00001FFFH.
 */
#define VMX_EXIT_REASON_EXECUTE_WRMSR                                0x00000020

/**
 * @brief VM-entry failure due to invalid guest state
 *
 * A VM entry failed one of the checks identified in Section 26.3.1.
 */
#define VMX_EXIT_REASON_ERROR_INVALID_GUEST_STATE                    0x00000021

/**
 * @brief VM-entry failure due to MSR loading
 *
 * A VM entry failed in an attempt to load MSRs. See Section 26.4.
 */
#define VMX_EXIT_REASON_ERROR_MSR_LOAD                               0x00000022

/**
 * @brief Guest software executed MWAIT
 *
 * Guest software attempted to execute MWAIT and the "MWAIT exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_MWAIT                                0x00000024

/**
 * @brief VM-exit due to monitor trap flag
 *
 * A VM entry occurred due to the 1-setting of the "monitor trap flag" VM-execution control and injection of an MTF VM exit
 * as part of VM entry.
 *
 * @see Vol3C[25.5.2(Monitor Trap Flag)]
 */
#define VMX_EXIT_REASON_MONITOR_TRAP_FLAG                            0x00000025

/**
 * @brief Guest software attempted to execute MONITOR
 *
 * Guest software attempted to execute MONITOR and the "MONITOR exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_MONITOR                              0x00000027

/**
 * @brief Guest software attempted to execute PAUSE
 *
 * Either guest software attempted to execute PAUSE and the "PAUSE exiting" VM-execution control was 1 or the "PAUSE-loop
 * exiting" VM-execution control was 1 and guest software executed a PAUSE loop with execution time exceeding PLE_Window.
 *
 * @see Vol3C[25.1.3(Instructions That Cause VM Exits Conditionally)]
 */
#define VMX_EXIT_REASON_EXECUTE_PAUSE                                0x00000028

/**
 * @brief VM-entry failure due to machine-check
 *
 * A machine-check event occurred during VM entry.
 *
 * @see Vol3C[26.8(MACHINE-CHECK EVENTS DURING VM ENTRY)]
 */
#define VMX_EXIT_REASON_ERROR_MACHINE_CHECK                          0x00000029

/**
 * @brief TPR below threshold
 *
 * The logical processor determined that the value of bits 7:4 of the byte at offset 080H on the virtual-APIC page was
 * below that of the TPR threshold VM-execution control field while the "use TPR shadow" VMexecution control was 1 either
 * as part of TPR virtualization or VM entry.
 *
 * @see Vol3C[29.1.2(TPR Virtualization)]
 * @see Vol3C[26.6.7(VM Exits Induced by the TPR Threshold)]
 */
#define VMX_EXIT_REASON_TPR_BELOW_THRESHOLD                          0x0000002B

/**
 * @brief APIC access
 *
 * Guest software attempted to access memory at a physical address on the APIC-access page and the "virtualize APIC
 * accesses" VM-execution control was 1.
 *
 * @see Vol3C[29.4(VIRTUALIZING MEMORY-MAPPED APIC ACCESSES)]
 */
#define VMX_EXIT_REASON_APIC_ACCESS                                  0x0000002C

/**
 * @brief Virtualized EOI
 *
 * EOI virtualization was performed for a virtual interrupt whose vector indexed a bit set in the EOIexit bitmap.
 */
#define VMX_EXIT_REASON_VIRTUALIZED_EOI                              0x0000002D

/**
 * @brief Access to GDTR or IDTR
 *
 * Guest software attempted to execute LGDT, LIDT, SGDT, or SIDT and the "descriptor-table exiting" VM-execution control
 * was 1.
 */
#define VMX_EXIT_REASON_GDTR_IDTR_ACCESS                             0x0000002E

/**
 * @brief Access to LDTR or TR
 *
 * Guest software attempted to execute LLDT, LTR, SLDT, or STR and the "descriptor-table exiting" VM-execution control was
 * 1.
 */
#define VMX_EXIT_REASON_LDTR_TR_ACCESS                               0x0000002F

/**
 * @brief EPT violation
 *
 * An attempt to access memory with a guest-physical address was disallowed by the configuration of the EPT paging
 * structures.
 */
#define VMX_EXIT_REASON_EPT_VIOLATION                                0x00000030

/**
 * @brief EPT misconfiguration
 *
 * An attempt to access memory with a guest-physical address encountered a misconfigured EPT paging-structure entry.
 */
#define VMX_EXIT_REASON_EPT_MISCONFIGURATION                         0x00000031

/**
 * @brief INVEPT
 *
 * Guest software attempted to execute INVEPT.
 */
#define VMX_EXIT_REASON_EXECUTE_INVEPT                               0x00000032

/**
 * @brief RDTSCP
 *
 * Guest software attempted to execute RDTSCP and the "enable RDTSCP" and "RDTSC exiting" VM-execution controls were both
 * 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDTSCP                               0x00000033

/**
 * @brief VMX-preemption timer expired
 *
 * The preemption timer counted down to zero.
 */
#define VMX_EXIT_REASON_VMX_PREEMPTION_TIMER_EXPIRED                 0x00000034

/**
 * @brief INVVPID
 *
 * Guest software attempted to execute INVVPID.
 */
#define VMX_EXIT_REASON_EXECUTE_INVVPID                              0x00000035

/**
 * @brief WBINVD
 *
 * Guest software attempted to execute WBINVD and the "WBINVD exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_WBINVD                               0x00000036

/**
 * @brief XSETBV - Guest software attempted to execute XSETBV
 *
 * Guest software attempted to execute XSETBV.
 */
#define VMX_EXIT_REASON_EXECUTE_XSETBV                               0x00000037

/**
 * @brief APIC write
 *
 * Guest software completed a write to the virtual-APIC page that must be virtualized by VMM software.
 *
 * @see Vol3C[29.4.3.3(APIC-Write VM Exits)]
 */
#define VMX_EXIT_REASON_APIC_WRITE                                   0x00000038

/**
 * @brief RDRAND
 *
 * Guest software attempted to execute RDRAND and the "RDRAND exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDRAND                               0x00000039

/**
 * @brief INVPCID
 *
 * Guest software attempted to execute INVPCID and the "enable INVPCID" and "INVLPG exiting" VM-execution controls were
 * both 1.
 */
#define VMX_EXIT_REASON_EXECUTE_INVPCID                              0x0000003A

/**
 * @brief VMFUNC
 *
 * Guest software invoked a VM function with the VMFUNC instruction and the VM function either was not enabled or generated
 * a function-specific condition causing a VM exit.
 */
#define VMX_EXIT_REASON_EXECUTE_VMFUNC                               0x0000003B

/**
 * @brief ENCLS
 *
 * Guest software attempted to execute ENCLS and "enable ENCLS exiting" VM-execution control was 1 and either:
 * -# EAX < 63 and the corresponding bit in the ENCLS-exiting bitmap is 1; or
 * -# EAX >= 63 and bit 63 in the ENCLS-exiting bitmap is 1.
 */
#define VMX_EXIT_REASON_EXECUTE_ENCLS                                0x0000003C

/**
 * @brief RDSEED
 *
 * Guest software attempted to execute RDSEED and the "RDSEED exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDSEED                               0x0000003D

/**
 * @brief Page-modification log full
 *
 * The processor attempted to create a page-modification log entry and the value of the PML index was not in the range
 * 0-511.
 */
#define VMX_EXIT_REASON_PAGE_MODIFICATION_LOG_FULL                   0x0000003E

/**
 * @brief XSAVES
 *
 * Guest software attempted to execute XSAVES, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the logical-AND of
 * the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
 */
#define VMX_EXIT_REASON_EXECUTE_XSAVES                               0x0000003F

/**
 * @brief XRSTORS
 *
 * Guest software attempted to execute XRSTORS, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the logical-AND of
 * the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
 */
#define VMX_EXIT_REASON_EXECUTE_XRSTORS                              0x00000040

/**
 * @}
 */

/**
 * @defgroup VMX_INSTRUCTION_ERROR_NUMBERS \
 *           VM Instruction Error Numbers
 *
 * VM Instruction Error Numbers.
 *
 * @see Vol3C[30.4(VM INSTRUCTION ERROR NUMBERS)] (reference)
 * @{
 */
/**
 * VMCALL executed in VMX root operation.
 */
#define VMX_ERROR_VMCALL_IN_VMX_ROOT_OPERATION                       0x00000001

/**
 * VMCLEAR with invalid physical address.
 */
#define VMX_ERROR_VMCLEAR_INVALID_PHYSICAL_ADDRESS                   0x00000002

/**
 * VMCLEAR with VMXON pointer.
 */
#define VMX_ERROR_VMCLEAR_INVALID_VMXON_POINTER                      0x00000003

/**
 * VMLAUNCH with non-clear VMCS.
 */
#define VMX_ERROR_VMLAUCH_NON_CLEAR_VMCS                             0x00000004

/**
 * VMRESUME with non-launched VMCS.
 */
#define VMX_ERROR_VMRESUME_NON_LAUNCHED_VMCS                         0x00000005

/**
 * VMRESUME after VMXOFF (VMXOFF and VMXON between VMLAUNCH and VMRESUME).
 */
#define VMX_ERROR_VMRESUME_AFTER_VMXOFF                              0x00000006

/**
 * VM entry with invalid control field(s).
 */
#define VMX_ERROR_VMENTRY_INVALID_CONTROL_FIELDS                     0x00000007

/**
 * VM entry with invalid host-state field(s).
 */
#define VMX_ERROR_VMENTRY_INVALID_HOST_STATE                         0x00000008

/**
 * VMPTRLD with invalid physical address.
 */
#define VMX_ERROR_VMPTRLD_INVALID_PHYSICAL_ADDRESS                   0x00000009

/**
 * VMPTRLD with VMXON pointer.
 */
#define VMX_ERROR_VMPTRLD_VMXON_POINTER                              0x0000000A

/**
 * VMPTRLD with incorrect VMCS revision identifier.
 */
#define VMX_ERROR_VMPTRLD_INCORRECT_VMCS_REVISION_ID                 0x0000000B

/**
 * VMREAD/VMWRITE from/to unsupported VMCS component.
 */
#define VMX_ERROR_VMREAD_VMWRITE_INVALID_COMPONENT                   0x0000000C

/**
 * VMWRITE to read-only VMCS component.
 */
#define VMX_ERROR_VMWRITE_READONLY_COMPONENT                         0x0000000D

/**
 * VMXON executed in VMX root operation.
 */
#define VMX_ERROR_VMXON_IN_VMX_ROOT_OP                               0x0000000F

/**
 * VM entry with invalid executive-VMCS pointer.
 */
#define VMX_ERROR_VMENTRY_INVALID_VMCS_EXECUTIVE_POINTER             0x00000010

/**
 * VM entry with non-launched executive VMCS.
 */
#define VMX_ERROR_VMENTRY_NON_LAUNCHED_EXECUTIVE_VMCS                0x00000011

/**
 * VM entry with executive-VMCS pointer not VMXON pointer (when attempting to deactivate the dual-monitor treatment of SMIs
 * and SMM).
 */
#define VMX_ERROR_VMENTRY_EXECUTIVE_VMCS_PTR                         0x00000012

/**
 * VMCALL with non-clear VMCS (when attempting to activate the dual-monitor treatment of SMIs and SMM).
 */
#define VMX_ERROR_VMCALL_NON_CLEAR_VMCS                              0x00000013

/**
 * VMCALL with invalid VM-exit control fields.
 */
#define VMX_ERROR_VMCALL_INVALID_VMEXIT_FIELDS                       0x00000014

/**
 * VMCALL with incorrect MSEG revision identifier (when attempting to activate the dual-monitor treatment of SMIs and SMM).
 */
#define VMX_ERROR_VMCALL_INVALID_MSEG_REVISION_ID                    0x00000016

/**
 * VMXOFF under dual-monitor treatment of SMIs and SMM.
 */
#define VMX_ERROR_VMXOFF_DUAL_MONITOR                                0x00000017

/**
 * VMCALL with invalid SMM-monitor features (when attempting to activate the dual-monitor treatment of SMIs and SMM).
 */
#define VMX_ERROR_VMCALL_INVALID_SMM_MONITOR                         0x00000018

/**
 * VM entry with invalid VM-execution control fields in executive VMCS (when attempting to return from SMM).
 */
#define VMX_ERROR_VMENTRY_INVALID_VM_EXECUTION_CONTROL               0x00000019

/**
 * VM entry with events blocked by MOV SS.
 */
#define VMX_ERROR_VMENTRY_MOV_SS                                     0x0000001A

/**
 * Invalid operand to INVEPT/INVVPID.
 */
#define VMX_ERROR_INVEPT_INVVPID_INVALID_OPERAND                     0x0000001C

/**
 * @}
 */

/**
 * @defgroup VMX_EXCEPTIONS \
 *           Virtualization Exceptions
 *
 * Virtualization Exceptions.
 *
 * @see Vol3C[25.5.6(Virtualization Exceptions)] (reference)
 * @{
 */
typedef struct
{
  UINT32 Reason;
  UINT32 ExceptionMask;
  UINT64 Exit;
  UINT64 GuestLinearAddress;
  UINT64 GuestPhysicalAddress;
  UINT16 CurrentEptpIndex;
} VIRTUALIZATION_EXCEPTION_INFORMATION;

/**
 * @}
 */

/**
 * @defgroup VMX_BASIC_EXIT_INFORMATION \
 *           Basic VM-Exit Information
 *
 * Basic VM-Exit Information.
 *
 * @see Vol3C[27.2.1(Basic VM-Exit Information)] (reference)
 * @{
 */
/**
 * @brief Exit Qualification for Debug Exceptions
 */
typedef union
{
  struct
  {
    /**
     * @brief B3 - B0
     *
     * [Bits 3:0] When set, each of these bits indicates that the corresponding breakpoint condition was met. Any of these bits
     * may be set even if its corresponding enabling bit in DR7 is not set.
     */
    UINT64 BreakpointCondition                                     : 4;
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_BREAKPOINT_CONDITION_BIT 0
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_BREAKPOINT_CONDITION_MASK 0x0F
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_BREAKPOINT_CONDITION(_) (((_) >> 0) & 0x0F)
    UINT64 Reserved1                                               : 9;

    /**
     * @brief BD
     *
     * [Bit 13] When set, this bit indicates that the cause of the debug exception is "debug register access detected."
     */
    UINT64 DebugRegisterAccessDetected                             : 1;
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_DEBUG_REGISTER_ACCESS_DETECTED_BIT 13
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_DEBUG_REGISTER_ACCESS_DETECTED_MASK 0x01
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_DEBUG_REGISTER_ACCESS_DETECTED(_) (((_) >> 13) & 0x01)

    /**
     * @brief BS
     *
     * [Bit 14] When set, this bit indicates that the cause of the debug exception is either the execution of a single
     * instruction (if RFLAGS.TF = 1 and IA32_DEBUGCTL.BTF = 0) or a taken branch (if RFLAGS.TF = DEBUGCTL.BTF = 1).
     */
    UINT64 SingleInstruction                                       : 1;
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_SINGLE_INSTRUCTION_BIT 14
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_SINGLE_INSTRUCTION_MASK 0x01
#define VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION_SINGLE_INSTRUCTION(_) (((_) >> 14) & 0x01)
    UINT64 Reserved2                                               : 49;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION;

/**
 * @brief Exit Qualification for Task Switch
 */
typedef union
{
  struct
  {
    /**
     * [Bits 15:0] Selector of task-state segment (TSS) to which the guest attempted to switch.
     */
    UINT64 Selector                                                : 16;
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SELECTOR_BIT              0
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SELECTOR_MASK             0xFFFF
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SELECTOR(_)               (((_) >> 0) & 0xFFFF)
    UINT64 Reserved1                                               : 14;

    /**
     * [Bits 31:30] Source of task switch initiation.
     */
    UINT64 Source                                                  : 2;
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SOURCE_BIT                30
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SOURCE_MASK               0x03
#define VMX_EXIT_QUALIFICATION_TASK_SWITCH_SOURCE(_)                 (((_) >> 30) & 0x03)
#define VMX_EXIT_QUALIFICATION_TYPE_CALL_INSTRUCTION                 0x00000000
#define VMX_EXIT_QUALIFICATION_TYPE_IRET_INSTRUCTION                 0x00000001
#define VMX_EXIT_QUALIFICATION_TYPE_JMP_INSTRUCTION                  0x00000002
#define VMX_EXIT_QUALIFICATION_TYPE_TASK_GATE_IN_IDT                 0x00000003
    UINT64 Reserved2                                               : 32;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_TASK_SWITCH;

/**
 * @brief Exit Qualification for Control-Register Accesses
 */
typedef union
{
  struct
  {
    /**
     * [Bits 3:0] Number of control register (0 for CLTS and LMSW). Bit 3 is always 0 on processors that do not support Intel
     * 64 architecture as they do not support CR8.
     */
    UINT64 ControlRegister                                         : 4;
#define VMX_EXIT_QUALIFICATION_MOV_CR_CONTROL_REGISTER_BIT           0
#define VMX_EXIT_QUALIFICATION_MOV_CR_CONTROL_REGISTER_MASK          0x0F
#define VMX_EXIT_QUALIFICATION_MOV_CR_CONTROL_REGISTER(_)            (((_) >> 0) & 0x0F)
#define VMX_EXIT_QUALIFICATION_REGISTER_CR0                          0x00000000
#define VMX_EXIT_QUALIFICATION_REGISTER_CR2                          0x00000002
#define VMX_EXIT_QUALIFICATION_REGISTER_CR3                          0x00000003
#define VMX_EXIT_QUALIFICATION_REGISTER_CR4                          0x00000004
#define VMX_EXIT_QUALIFICATION_REGISTER_CR8                          0x00000008

    /**
     * [Bits 5:4] Access type.
     */
    UINT64 AccessType                                              : 2;
#define VMX_EXIT_QUALIFICATION_MOV_CR_ACCESS_TYPE_BIT                4
#define VMX_EXIT_QUALIFICATION_MOV_CR_ACCESS_TYPE_MASK               0x03
#define VMX_EXIT_QUALIFICATION_MOV_CR_ACCESS_TYPE(_)                 (((_) >> 4) & 0x03)
#define VMX_EXIT_QUALIFICATION_ACCESS_MOV_TO_CR                      0x00000000
#define VMX_EXIT_QUALIFICATION_ACCESS_MOV_FROM_CR                    0x00000001
#define VMX_EXIT_QUALIFICATION_ACCESS_CLTS                           0x00000002
#define VMX_EXIT_QUALIFICATION_ACCESS_LMSW                           0x00000003

    /**
     * [Bit 6] LMSW operand type. For CLTS and MOV CR, cleared to 0.
     */
    UINT64 LmswOperandType                                         : 1;
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_OPERAND_TYPE_BIT          6
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_OPERAND_TYPE_MASK         0x01
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_OPERAND_TYPE(_)           (((_) >> 6) & 0x01)
#define VMX_EXIT_QUALIFICATION_LMSW_OP_REGISTER                      0x00000000
#define VMX_EXIT_QUALIFICATION_LMSW_OP_MEMORY                        0x00000001
    UINT64 Reserved1                                               : 1;

    /**
     * [Bits 11:8] For MOV CR, the general-purpose register.
     */
    UINT64 GeneralPurposeRegister                                  : 4;
#define VMX_EXIT_QUALIFICATION_MOV_CR_GENERAL_PURPOSE_REGISTER_BIT   8
#define VMX_EXIT_QUALIFICATION_MOV_CR_GENERAL_PURPOSE_REGISTER_MASK  0x0F
#define VMX_EXIT_QUALIFICATION_MOV_CR_GENERAL_PURPOSE_REGISTER(_)    (((_) >> 8) & 0x0F)
#define VMX_EXIT_QUALIFICATION_GENREG_RAX                            0x00000000
#define VMX_EXIT_QUALIFICATION_GENREG_RCX                            0x00000001
#define VMX_EXIT_QUALIFICATION_GENREG_RDX                            0x00000002
#define VMX_EXIT_QUALIFICATION_GENREG_RBX                            0x00000003
#define VMX_EXIT_QUALIFICATION_GENREG_RSP                            0x00000004
#define VMX_EXIT_QUALIFICATION_GENREG_RBP                            0x00000005
#define VMX_EXIT_QUALIFICATION_GENREG_RSI                            0x00000006
#define VMX_EXIT_QUALIFICATION_GENREG_RDI                            0x00000007
#define VMX_EXIT_QUALIFICATION_GENREG_R8                             0x00000008
#define VMX_EXIT_QUALIFICATION_GENREG_R9                             0x00000009
#define VMX_EXIT_QUALIFICATION_GENREG_R10                            0x0000000A
#define VMX_EXIT_QUALIFICATION_GENREG_R11                            0x0000000B
#define VMX_EXIT_QUALIFICATION_GENREG_R12                            0x0000000C
#define VMX_EXIT_QUALIFICATION_GENREG_R13                            0x0000000D
#define VMX_EXIT_QUALIFICATION_GENREG_R14                            0x0000000E
#define VMX_EXIT_QUALIFICATION_GENREG_R15                            0x0000000F
    UINT64 Reserved2                                               : 4;

    /**
     * [Bits 31:16] For LMSW, the LMSW source data. For CLTS and MOV CR, cleared to 0.
     */
    UINT64 LmswSourceData                                          : 16;
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_SOURCE_DATA_BIT           16
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_SOURCE_DATA_MASK          0xFFFF
#define VMX_EXIT_QUALIFICATION_MOV_CR_LMSW_SOURCE_DATA(_)            (((_) >> 16) & 0xFFFF)
    UINT64 Reserved3                                               : 32;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_MOV_CR;

/**
 * @brief Exit Qualification for MOV DR
 */
typedef union
{
  struct
  {
    /**
     * [Bits 2:0] Number of debug register.
     */
    UINT64 DebugRegister                                           : 3;
#define VMX_EXIT_QUALIFICATION_MOV_DR_DEBUG_REGISTER_BIT             0
#define VMX_EXIT_QUALIFICATION_MOV_DR_DEBUG_REGISTER_MASK            0x07
#define VMX_EXIT_QUALIFICATION_MOV_DR_DEBUG_REGISTER(_)              (((_) >> 0) & 0x07)
#define VMX_EXIT_QUALIFICATION_REGISTER_DR0                          0x00000000
#define VMX_EXIT_QUALIFICATION_REGISTER_DR1                          0x00000001
#define VMX_EXIT_QUALIFICATION_REGISTER_DR2                          0x00000002
#define VMX_EXIT_QUALIFICATION_REGISTER_DR3                          0x00000003
#define VMX_EXIT_QUALIFICATION_REGISTER_DR6                          0x00000006
#define VMX_EXIT_QUALIFICATION_REGISTER_DR7                          0x00000007
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 4] Direction of access (0 = MOV to DR; 1 = MOV from DR).
     */
    UINT64 DirectionOfAccess                                       : 1;
#define VMX_EXIT_QUALIFICATION_MOV_DR_DIRECTION_OF_ACCESS_BIT        4
#define VMX_EXIT_QUALIFICATION_MOV_DR_DIRECTION_OF_ACCESS_MASK       0x01
#define VMX_EXIT_QUALIFICATION_MOV_DR_DIRECTION_OF_ACCESS(_)         (((_) >> 4) & 0x01)
#define VMX_EXIT_QUALIFICATION_DIRECTION_MOV_TO_DR                   0x00000000
#define VMX_EXIT_QUALIFICATION_DIRECTION_MOV_FROM_DR                 0x00000001
    UINT64 Reserved2                                               : 3;

    /**
     * [Bits 11:8] General-purpose register.
     */
    UINT64 GeneralPurposeRegister                                  : 4;
#define VMX_EXIT_QUALIFICATION_MOV_DR_GENERAL_PURPOSE_REGISTER_BIT   8
#define VMX_EXIT_QUALIFICATION_MOV_DR_GENERAL_PURPOSE_REGISTER_MASK  0x0F
#define VMX_EXIT_QUALIFICATION_MOV_DR_GENERAL_PURPOSE_REGISTER(_)    (((_) >> 8) & 0x0F)
#define VMX_EXIT_QUALIFICATION_GENREG_RAX                            0x00000000
#define VMX_EXIT_QUALIFICATION_GENREG_RCX                            0x00000001
#define VMX_EXIT_QUALIFICATION_GENREG_RDX                            0x00000002
#define VMX_EXIT_QUALIFICATION_GENREG_RBX                            0x00000003
#define VMX_EXIT_QUALIFICATION_GENREG_RSP                            0x00000004
#define VMX_EXIT_QUALIFICATION_GENREG_RBP                            0x00000005
#define VMX_EXIT_QUALIFICATION_GENREG_RSI                            0x00000006
#define VMX_EXIT_QUALIFICATION_GENREG_RDI                            0x00000007
#define VMX_EXIT_QUALIFICATION_GENREG_R8                             0x00000008
#define VMX_EXIT_QUALIFICATION_GENREG_R9                             0x00000009
#define VMX_EXIT_QUALIFICATION_GENREG_R10                            0x0000000A
#define VMX_EXIT_QUALIFICATION_GENREG_R11                            0x0000000B
#define VMX_EXIT_QUALIFICATION_GENREG_R12                            0x0000000C
#define VMX_EXIT_QUALIFICATION_GENREG_R13                            0x0000000D
#define VMX_EXIT_QUALIFICATION_GENREG_R14                            0x0000000E
#define VMX_EXIT_QUALIFICATION_GENREG_R15                            0x0000000F
    UINT64 Reserved3                                               : 52;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_MOV_DR;

/**
 * @brief Exit Qualification for I/O Instructions
 */
typedef union
{
  struct
  {
    /**
     * [Bits 2:0] Size of access.
     */
    UINT64 SizeOfAccess                                            : 3;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_SIZE_OF_ACCESS_BIT     0
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_SIZE_OF_ACCESS_MASK    0x07
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_SIZE_OF_ACCESS(_)      (((_) >> 0) & 0x07)
#define VMX_EXIT_QUALIFICATION_WIDTH_1_BYTE                          0x00000000
#define VMX_EXIT_QUALIFICATION_WIDTH_2_BYTE                          0x00000001
#define VMX_EXIT_QUALIFICATION_WIDTH_4_BYTE                          0x00000003

    /**
     * [Bit 3] Direction of the attempted access (0 = OUT, 1 = IN).
     */
    UINT64 DirectionOfAccess                                       : 1;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_DIRECTION_OF_ACCESS_BIT 3
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_DIRECTION_OF_ACCESS_MASK 0x01
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_DIRECTION_OF_ACCESS(_) (((_) >> 3) & 0x01)
#define VMX_EXIT_QUALIFICATION_DIRECTION_OUT                         0x00000000
#define VMX_EXIT_QUALIFICATION_DIRECTION_IN                          0x00000001

    /**
     * [Bit 4] String instruction (0 = not string; 1 = string).
     */
    UINT64 StringInstruction                                       : 1;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_STRING_INSTRUCTION_BIT 4
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_STRING_INSTRUCTION_MASK 0x01
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_STRING_INSTRUCTION(_)  (((_) >> 4) & 0x01)
#define VMX_EXIT_QUALIFICATION_IS_STRING_NOT_STRING                  0x00000000
#define VMX_EXIT_QUALIFICATION_IS_STRING_STRING                      0x00000001

    /**
     * [Bit 5] REP prefixed (0 = not REP; 1 = REP).
     */
    UINT64 RepPrefixed                                             : 1;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_REP_PREFIXED_BIT       5
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_REP_PREFIXED_MASK      0x01
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_REP_PREFIXED(_)        (((_) >> 5) & 0x01)
#define VMX_EXIT_QUALIFICATION_IS_REP_NOT_REP                        0x00000000
#define VMX_EXIT_QUALIFICATION_IS_REP_REP                            0x00000001

    /**
     * [Bit 6] Operand encoding (0 = DX, 1 = immediate).
     */
    UINT64 OperandEncoding                                         : 1;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_OPERAND_ENCODING_BIT   6
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_OPERAND_ENCODING_MASK  0x01
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_OPERAND_ENCODING(_)    (((_) >> 6) & 0x01)
#define VMX_EXIT_QUALIFICATION_ENCODING_DX                           0x00000000
#define VMX_EXIT_QUALIFICATION_ENCODING_IMMEDIATE                    0x00000001
    UINT64 Reserved1                                               : 9;

    /**
     * [Bits 31:16] Port number (as specified in DX or in an immediate operand).
     */
    UINT64 PortNumber                                              : 16;
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_PORT_NUMBER_BIT        16
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_PORT_NUMBER_MASK       0xFFFF
#define VMX_EXIT_QUALIFICATION_IO_INSTRUCTION_PORT_NUMBER(_)         (((_) >> 16) & 0xFFFF)
    UINT64 Reserved2                                               : 32;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_IO_INSTRUCTION;

/**
 * @brief Exit Qualification for APIC-Access VM Exits from Linear Accesses and Guest-Physical Accesses
 */
typedef union
{
  struct
  {
    /**
     * [Bits 11:0] - If the APIC-access VM exit is due to a linear access, the offset of access within the APIC page.
     * - Undefined if the APIC-access VM exit is due a guest-physical access.
     */
    UINT64 PageOffset                                              : 12;
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_PAGE_OFFSET_BIT           0
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_PAGE_OFFSET_MASK          0xFFF
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_PAGE_OFFSET(_)            (((_) >> 0) & 0xFFF)

    /**
     * [Bits 15:12] Access type.
     */
    UINT64 AccessType                                              : 4;
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_ACCESS_TYPE_BIT           12
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_ACCESS_TYPE_MASK          0x0F
#define VMX_EXIT_QUALIFICATION_APIC_ACCESS_ACCESS_TYPE(_)            (((_) >> 12) & 0x0F)
    /**
     * Linear access for a data read during instruction execution.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_LINEAR_READ                      0x00000000

    /**
     * Linear access for a data write during instruction execution.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_LINEAR_WRITE                     0x00000001

    /**
     * Linear access for an instruction fetch.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_LINEAR_INSTRUCTION_FETCH         0x00000002

    /**
     * Linear access (read or write) during event delivery.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_LINEAR_EVENT_DELIVERY            0x00000003

    /**
     * Guest-physical access during event delivery.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_PHYSICAL_EVENT_DELIVERY          0x0000000A

    /**
     * Guest-physical access for an instruction fetch or during instruction execution.
     */
#define VMX_EXIT_QUALIFICATION_TYPE_PHYSICAL_INSTRUCTION_FETCH       0x0000000F

    UINT64 Reserved1                                               : 48;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_APIC_ACCESS;

/**
 * @brief Exit Qualification for EPT Violations
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Set if the access causing the EPT violation was a data read.
     */
    UINT64 ReadAccess                                              : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READ_ACCESS_BIT         0
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READ_ACCESS_MASK        0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READ_ACCESS(_)          (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Set if the access causing the EPT violation was a data write.
     */
    UINT64 WriteAccess                                             : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_WRITE_ACCESS_BIT        1
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_WRITE_ACCESS_MASK       0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_WRITE_ACCESS(_)         (((_) >> 1) & 0x01)

    /**
     * [Bit 2] Set if the access causing the EPT violation was an instruction fetch.
     */
    UINT64 ExecuteAccess                                           : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_ACCESS_BIT      2
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_ACCESS_MASK     0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_ACCESS(_)       (((_) >> 2) & 0x01)

    /**
     * [Bit 3] The logical-AND of bit 0 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation (indicates whether the guest-physical address was readable).
     */
    UINT64 EptReadable                                             : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_READABLE_BIT        3
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_READABLE_MASK       0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_READABLE(_)         (((_) >> 3) & 0x01)

    /**
     * [Bit 4] The logical-AND of bit 1 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation (indicates whether the guest-physical address was writeable).
     */
    UINT64 EptWriteable                                            : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_WRITEABLE_BIT       4
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_WRITEABLE_MASK      0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_WRITEABLE(_)        (((_) >> 4) & 0x01)

    /**
     * [Bit 5] The logical-AND of bit 2 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation.
     * If the "mode-based execute control for EPT" VM-execution control is 0, this indicates whether the guest-physical address
     * was executable. If that control is 1, this indicates whether the guest-physical address was executable for
     * supervisor-mode linear addresses.
     */
    UINT64 EptExecutable                                           : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE_BIT      5
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE_MASK     0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE(_)       (((_) >> 5) & 0x01)

    /**
     * [Bit 6] If the "mode-based execute control" VM-execution control is 0, the value of this bit is undefined. If that
     * control is 1, this bit is the logical-AND of bit 10 in the EPT paging-structures entries used to translate the
     * guest-physical address of the access causing the EPT violation. In this case, it indicates whether the guest-physical
     * address was executable for user-mode linear addresses.
     */
    UINT64 EptExecutableForUserMode                                : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE_FOR_USER_MODE_BIT 6
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE_FOR_USER_MODE_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EPT_EXECUTABLE_FOR_USER_MODE(_) (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Set if the guest linear-address field is valid. The guest linear-address field is valid for all EPT violations
     * except those resulting from an attempt to load the guest PDPTEs as part of the execution of the MOV CR instruction.
     */
    UINT64 ValidGuestLinearAddress                                 : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_VALID_GUEST_LINEAR_ADDRESS_BIT 7
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_VALID_GUEST_LINEAR_ADDRESS_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_VALID_GUEST_LINEAR_ADDRESS(_) (((_) >> 7) & 0x01)

    /**
     * [Bit 8] If bit 7 is 1:
     * - Set if the access causing the EPT violation is to a guest-physical address that is the translation of a linear
     * address.
     * - Clear if the access causing the EPT violation is to a paging-structure entry as part of a page walk or the update of
     * an accessed or dirty bit.
     * Reserved if bit 7 is 0 (cleared to 0).
     */
    UINT64 CausedByTranslation                                     : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_CAUSED_BY_TRANSLATION_BIT 8
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_CAUSED_BY_TRANSLATION_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_CAUSED_BY_TRANSLATION(_) (((_) >> 8) & 0x01)

    /**
     * [Bit 9] This bit is 0 if the linear address is a supervisor-mode linear address and 1 if it is a user-mode linear
     * address. Otherwise, this bit is undefined.
     *
     * @remarks If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations. (If
     *          CR0.PG = 0, the translation of every linear address is a user-mode linear address and thus this bit will be 1.)
     */
    UINT64 UserModeLinearAddress                                   : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_USER_MODE_LINEAR_ADDRESS_BIT 9
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_USER_MODE_LINEAR_ADDRESS_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_USER_MODE_LINEAR_ADDRESS(_) (((_) >> 9) & 0x01)

    /**
     * [Bit 10] This bit is 0 if paging translates the linear address to a read-only page and 1 if it translates to a
     * read/write page. Otherwise, this bit is undefined
     *
     * @remarks If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations. (If
     *          CR0.PG = 0, every linear address is read/write and thus this bit will be 1.)
     */
    UINT64 ReadableWritablePage                                    : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READABLE_WRITABLE_PAGE_BIT 10
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READABLE_WRITABLE_PAGE_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_READABLE_WRITABLE_PAGE(_) (((_) >> 10) & 0x01)

    /**
     * [Bit 11] This bit is 0 if paging translates the linear address to an executable page and 1 if it translates to an
     * execute-disable page. Otherwise, this bit is undefined.
     *
     * @remarks If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations. (If
     *          CR0.PG = 0, CR4.PAE = 0, or IA32_EFER.NXE = 0, every linear address is executable and thus this bit will be 0.)
     */
    UINT64 ExecuteDisablePage                                      : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_DISABLE_PAGE_BIT 11
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_DISABLE_PAGE_MASK 0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_EXECUTE_DISABLE_PAGE(_) (((_) >> 11) & 0x01)

    /**
     * [Bit 12] NMI unblocking due to IRET.
     */
    UINT64 NmiUnblocking                                           : 1;
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_NMI_UNBLOCKING_BIT      12
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_NMI_UNBLOCKING_MASK     0x01
#define VMX_EXIT_QUALIFICATION_EPT_VIOLATION_NMI_UNBLOCKING(_)       (((_) >> 12) & 0x01)
    UINT64 Reserved1                                               : 51;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_EPT_VIOLATION;

/**
 * @}
 */

/**
 * @defgroup EPT \
 *           The extended page-table mechanism
 *
 * The extended page-table mechanism (EPT) is a feature that can be used to support the virtualization of physical memory.
 * When EPT is in use, certain addresses that would normally be treated as physical addresses (and used to access memory)
 * are instead treated as guest-physical addresses. Guest-physical addresses are translated by traversing a set of EPT
 * paging structures to produce physical addresses that are used to access memory.
 *
 * @see Vol3C[28.2(THE EXTENDED PAGE TABLE MECHANISM (EPT))] (reference)
 * @{
 */
/**
 * @brief Extended-Page-Table Pointer (EPTP)
 *
 * The extended-page-table pointer (EPTP) contains the address of the base of EPT PML4 table, as well as other EPT
 * configuration information.
 *
 * @see Vol3C[28.2.2(EPT Translation Mechanism]
 * @see Vol3C[24.6.11(Extended-Page-Table Pointer (EPTP)] (reference)
 */
typedef union
{
  struct
  {
    /**
     * [Bits 2:0] EPT paging-structure memory type:
     * - 0 = Uncacheable (UC)
     * - 6 = Write-back (WB)
     * Other values are reserved.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 MemoryType                                              : 3;
#define EPT_POINTER_MEMORY_TYPE_BIT                                  0
#define EPT_POINTER_MEMORY_TYPE_MASK                                 0x07
#define EPT_POINTER_MEMORY_TYPE(_)                                   (((_) >> 0) & 0x07)

    /**
     * [Bits 5:3] This value is 1 less than the EPT page-walk length.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 PageWalkLength                                          : 3;
#define EPT_POINTER_PAGE_WALK_LENGTH_BIT                             3
#define EPT_POINTER_PAGE_WALK_LENGTH_MASK                            0x07
#define EPT_POINTER_PAGE_WALK_LENGTH(_)                              (((_) >> 3) & 0x07)

    /**
     * [Bit 6] Setting this control to 1 enables accessed and dirty flags for EPT.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 EnableAccessAndDirtyFlags                               : 1;
#define EPT_POINTER_ENABLE_ACCESS_AND_DIRTY_FLAGS_BIT                6
#define EPT_POINTER_ENABLE_ACCESS_AND_DIRTY_FLAGS_MASK               0x01
#define EPT_POINTER_ENABLE_ACCESS_AND_DIRTY_FLAGS(_)                 (((_) >> 6) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bits 47:12] Bits N-1:12 of the physical address of the 4-KByte aligned EPT PML4 table.
     */
    UINT64 PageFrameNumber                                         : 36;
#define EPT_POINTER_PAGE_FRAME_NUMBER_BIT                            12
#define EPT_POINTER_PAGE_FRAME_NUMBER_MASK                           0xFFFFFFFFF
#define EPT_POINTER_PAGE_FRAME_NUMBER(_)                             (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved2                                               : 16;
  };

  UINT64 Flags;
} EPT_POINTER;

/**
 * @brief Format of an EPT PML4 Entry (PML4E) that References an EPT Page-Directory-Pointer Table
 *
 * A 4-KByte naturally aligned EPT PML4 table is located at the physical address specified in bits 51:12 of the
 * extended-page-table pointer (EPTP), a VM-execution control field. An EPT PML4 table comprises 512 64-bit entries (EPT
 * PML4Es). An EPT PML4E is selected using the physical address defined as follows:
 * - Bits 63:52 are all 0.
 * - Bits 51:12 are from the EPTP.
 * - Bits 11:3 are bits 47:39 of the guest-physical address.
 * - Bits 2:0 are all 0.
 * Because an EPT PML4E is identified using bits 47:39 of the guest-physical address, it controls access to a 512- GByte
 * region of the guest-physical-address space.
 *
 * @see Vol3C[24.6.11(Extended-Page-Table Pointer (EPTP)]
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 512-GByte region controlled by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPT_PML4_READ_ACCESS_BIT                                     0
#define EPT_PML4_READ_ACCESS_MASK                                    0x01
#define EPT_PML4_READ_ACCESS(_)                                      (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 512-GByte region controlled by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPT_PML4_WRITE_ACCESS_BIT                                    1
#define EPT_PML4_WRITE_ACCESS_MASK                                   0x01
#define EPT_PML4_WRITE_ACCESS(_)                                     (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 512-GByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 512-GByte region controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPT_PML4_EXECUTE_ACCESS_BIT                                  2
#define EPT_PML4_EXECUTE_ACCESS_MASK                                 0x01
#define EPT_PML4_EXECUTE_ACCESS(_)                                   (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 512-GByte region
     * controlled by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPT_PML4_ACCESSED_BIT                                        8
#define EPT_PML4_ACCESSED_MASK                                       0x01
#define EPT_PML4_ACCESSED(_)                                         (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 512-GByte region
     * controlled by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPT_PML4_USER_MODE_EXECUTE_BIT                               10
#define EPT_PML4_USER_MODE_EXECUTE_MASK                              0x01
#define EPT_PML4_USER_MODE_EXECUTE(_)                                (((_) >> 10) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned EPT page-directory-pointer table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define EPT_PML4_PAGE_FRAME_NUMBER_BIT                               12
#define EPT_PML4_PAGE_FRAME_NUMBER_MASK                              0xFFFFFFFFF
#define EPT_PML4_PAGE_FRAME_NUMBER(_)                                (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved4                                               : 16;
  };

  UINT64 Flags;
} EPT_PML4;

/**
 * @brief Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 1-GByte page referenced by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPDPTE_1GB_READ_ACCESS_BIT                                   0
#define EPDPTE_1GB_READ_ACCESS_MASK                                  0x01
#define EPDPTE_1GB_READ_ACCESS(_)                                    (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 1-GByte page referenced by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPDPTE_1GB_WRITE_ACCESS_BIT                                  1
#define EPDPTE_1GB_WRITE_ACCESS_MASK                                 0x01
#define EPDPTE_1GB_WRITE_ACCESS(_)                                   (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 1-GByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 1-GByte page controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPDPTE_1GB_EXECUTE_ACCESS_BIT                                2
#define EPDPTE_1GB_EXECUTE_ACCESS_MASK                               0x01
#define EPDPTE_1GB_EXECUTE_ACCESS(_)                                 (((_) >> 2) & 0x01)

    /**
     * [Bits 5:3] EPT memory type for this 1-GByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 MemoryType                                              : 3;
#define EPDPTE_1GB_MEMORY_TYPE_BIT                                   3
#define EPDPTE_1GB_MEMORY_TYPE_MASK                                  0x07
#define EPDPTE_1GB_MEMORY_TYPE(_)                                    (((_) >> 3) & 0x07)

    /**
     * [Bit 6] Ignore PAT memory type for this 1-GByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 IgnorePat                                               : 1;
#define EPDPTE_1GB_IGNORE_PAT_BIT                                    6
#define EPDPTE_1GB_IGNORE_PAT_MASK                                   0x01
#define EPDPTE_1GB_IGNORE_PAT(_)                                     (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Must be 1 (otherwise, this entry references an EPT page directory).
     */
    UINT64 LargePage                                               : 1;
#define EPDPTE_1GB_LARGE_PAGE_BIT                                    7
#define EPDPTE_1GB_LARGE_PAGE_MASK                                   0x01
#define EPDPTE_1GB_LARGE_PAGE(_)                                     (((_) >> 7) & 0x01)

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 1-GByte page
     * referenced by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPDPTE_1GB_ACCESSED_BIT                                      8
#define EPDPTE_1GB_ACCESSED_MASK                                     0x01
#define EPDPTE_1GB_ACCESSED(_)                                       (((_) >> 8) & 0x01)

    /**
     * [Bit 9] If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 1-GByte page referenced
     * by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Dirty                                                   : 1;
#define EPDPTE_1GB_DIRTY_BIT                                         9
#define EPDPTE_1GB_DIRTY_MASK                                        0x01
#define EPDPTE_1GB_DIRTY(_)                                          (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-GByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPDPTE_1GB_USER_MODE_EXECUTE_BIT                             10
#define EPDPTE_1GB_USER_MODE_EXECUTE_MASK                            0x01
#define EPDPTE_1GB_USER_MODE_EXECUTE(_)                              (((_) >> 10) & 0x01)
    UINT64 Reserved1                                               : 19;

    /**
     * [Bits 47:30] Physical address of 4-KByte aligned EPT page-directory-pointer table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 18;
#define EPDPTE_1GB_PAGE_FRAME_NUMBER_BIT                             30
#define EPDPTE_1GB_PAGE_FRAME_NUMBER_MASK                            0x3FFFF
#define EPDPTE_1GB_PAGE_FRAME_NUMBER(_)                              (((_) >> 30) & 0x3FFFF)
    UINT64 Reserved2                                               : 15;

    /**
     * [Bit 63] Suppress \#VE. If the "EPT-violation \#VE" VM-execution control is 1, EPT violations caused by accesses to this
     * page are convertible to virtualization exceptions only if this bit is 0. If "EPT-violation \#VE" VMexecution control is
     * 0, this bit is ignored.
     *
     * @see Vol3C[25.5.6.1(Convertible EPT Violations)]
     */
    UINT64 SuppressVe                                              : 1;
#define EPDPTE_1GB_SUPPRESS_VE_BIT                                   63
#define EPDPTE_1GB_SUPPRESS_VE_MASK                                  0x01
#define EPDPTE_1GB_SUPPRESS_VE(_)                                    (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} EPDPTE_1GB;

/**
 * @brief Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that References an EPT Page Directory
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 1-GByte region controlled by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPDPTE_READ_ACCESS_BIT                                       0
#define EPDPTE_READ_ACCESS_MASK                                      0x01
#define EPDPTE_READ_ACCESS(_)                                        (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 1-GByte region controlled by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPDPTE_WRITE_ACCESS_BIT                                      1
#define EPDPTE_WRITE_ACCESS_MASK                                     0x01
#define EPDPTE_WRITE_ACCESS(_)                                       (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 1-GByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 1-GByte region controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPDPTE_EXECUTE_ACCESS_BIT                                    2
#define EPDPTE_EXECUTE_ACCESS_MASK                                   0x01
#define EPDPTE_EXECUTE_ACCESS(_)                                     (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 1-GByte region
     * controlled by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPDPTE_ACCESSED_BIT                                          8
#define EPDPTE_ACCESSED_MASK                                         0x01
#define EPDPTE_ACCESSED(_)                                           (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-GByte region controlled
     * by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPDPTE_USER_MODE_EXECUTE_BIT                                 10
#define EPDPTE_USER_MODE_EXECUTE_MASK                                0x01
#define EPDPTE_USER_MODE_EXECUTE(_)                                  (((_) >> 10) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned EPT page-directory-pointer table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define EPDPTE_PAGE_FRAME_NUMBER_BIT                                 12
#define EPDPTE_PAGE_FRAME_NUMBER_MASK                                0xFFFFFFFFF
#define EPDPTE_PAGE_FRAME_NUMBER(_)                                  (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved4                                               : 16;
  };

  UINT64 Flags;
} EPDPTE;

/**
 * @brief Format of an EPT Page-Directory Entry (PDE) that Maps a 2-MByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 2-MByte page referenced by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPDE_2MB_READ_ACCESS_BIT                                     0
#define EPDE_2MB_READ_ACCESS_MASK                                    0x01
#define EPDE_2MB_READ_ACCESS(_)                                      (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 2-MByte page referenced by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPDE_2MB_WRITE_ACCESS_BIT                                    1
#define EPDE_2MB_WRITE_ACCESS_MASK                                   0x01
#define EPDE_2MB_WRITE_ACCESS(_)                                     (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 2-MByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 2-MByte page controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPDE_2MB_EXECUTE_ACCESS_BIT                                  2
#define EPDE_2MB_EXECUTE_ACCESS_MASK                                 0x01
#define EPDE_2MB_EXECUTE_ACCESS(_)                                   (((_) >> 2) & 0x01)

    /**
     * [Bits 5:3] EPT memory type for this 2-MByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 MemoryType                                              : 3;
#define EPDE_2MB_MEMORY_TYPE_BIT                                     3
#define EPDE_2MB_MEMORY_TYPE_MASK                                    0x07
#define EPDE_2MB_MEMORY_TYPE(_)                                      (((_) >> 3) & 0x07)

    /**
     * [Bit 6] Ignore PAT memory type for this 2-MByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 IgnorePat                                               : 1;
#define EPDE_2MB_IGNORE_PAT_BIT                                      6
#define EPDE_2MB_IGNORE_PAT_MASK                                     0x01
#define EPDE_2MB_IGNORE_PAT(_)                                       (((_) >> 6) & 0x01)

    /**
     * [Bit 7] Must be 1 (otherwise, this entry references an EPT page table).
     */
    UINT64 LargePage                                               : 1;
#define EPDE_2MB_LARGE_PAGE_BIT                                      7
#define EPDE_2MB_LARGE_PAGE_MASK                                     0x01
#define EPDE_2MB_LARGE_PAGE(_)                                       (((_) >> 7) & 0x01)

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 2-MByte page
     * referenced by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPDE_2MB_ACCESSED_BIT                                        8
#define EPDE_2MB_ACCESSED_MASK                                       0x01
#define EPDE_2MB_ACCESSED(_)                                         (((_) >> 8) & 0x01)

    /**
     * [Bit 9] If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 2-MByte page referenced
     * by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Dirty                                                   : 1;
#define EPDE_2MB_DIRTY_BIT                                           9
#define EPDE_2MB_DIRTY_MASK                                          0x01
#define EPDE_2MB_DIRTY(_)                                            (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-MByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPDE_2MB_USER_MODE_EXECUTE_BIT                               10
#define EPDE_2MB_USER_MODE_EXECUTE_MASK                              0x01
#define EPDE_2MB_USER_MODE_EXECUTE(_)                                (((_) >> 10) & 0x01)
    UINT64 Reserved1                                               : 10;

    /**
     * [Bits 47:21] Physical address of 4-KByte aligned EPT page-directory-pointer table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 27;
#define EPDE_2MB_PAGE_FRAME_NUMBER_BIT                               21
#define EPDE_2MB_PAGE_FRAME_NUMBER_MASK                              0x7FFFFFF
#define EPDE_2MB_PAGE_FRAME_NUMBER(_)                                (((_) >> 21) & 0x7FFFFFF)
    UINT64 Reserved2                                               : 15;

    /**
     * [Bit 63] Suppress \#VE. If the "EPT-violation \#VE" VM-execution control is 1, EPT violations caused by accesses to this
     * page are convertible to virtualization exceptions only if this bit is 0. If "EPT-violation \#VE" VMexecution control is
     * 0, this bit is ignored.
     *
     * @see Vol3C[25.5.6.1(Convertible EPT Violations)]
     */
    UINT64 SuppressVe                                              : 1;
#define EPDE_2MB_SUPPRESS_VE_BIT                                     63
#define EPDE_2MB_SUPPRESS_VE_MASK                                    0x01
#define EPDE_2MB_SUPPRESS_VE(_)                                      (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} EPDE_2MB;

/**
 * @brief Format of an EPT Page-Directory Entry (PDE) that References an EPT Page Table
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 2-MByte region controlled by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPDE_READ_ACCESS_BIT                                         0
#define EPDE_READ_ACCESS_MASK                                        0x01
#define EPDE_READ_ACCESS(_)                                          (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 2-MByte region controlled by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPDE_WRITE_ACCESS_BIT                                        1
#define EPDE_WRITE_ACCESS_MASK                                       0x01
#define EPDE_WRITE_ACCESS(_)                                         (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 2-MByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 2-MByte region controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPDE_EXECUTE_ACCESS_BIT                                      2
#define EPDE_EXECUTE_ACCESS_MASK                                     0x01
#define EPDE_EXECUTE_ACCESS(_)                                       (((_) >> 2) & 0x01)
    UINT64 Reserved1                                               : 5;

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 2-MByte region
     * controlled by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPDE_ACCESSED_BIT                                            8
#define EPDE_ACCESSED_MASK                                           0x01
#define EPDE_ACCESSED(_)                                             (((_) >> 8) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-MByte region controlled
     * by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPDE_USER_MODE_EXECUTE_BIT                                   10
#define EPDE_USER_MODE_EXECUTE_MASK                                  0x01
#define EPDE_USER_MODE_EXECUTE(_)                                    (((_) >> 10) & 0x01)
    UINT64 Reserved3                                               : 1;

    /**
     * [Bits 47:12] Physical address of 4-KByte aligned EPT page table referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define EPDE_PAGE_FRAME_NUMBER_BIT                                   12
#define EPDE_PAGE_FRAME_NUMBER_MASK                                  0xFFFFFFFFF
#define EPDE_PAGE_FRAME_NUMBER(_)                                    (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved4                                               : 16;
  };

  UINT64 Flags;
} EPDE;

/**
 * @brief Format of an EPT Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Read access; indicates whether reads are allowed from the 4-KByte page referenced by this entry.
     */
    UINT64 ReadAccess                                              : 1;
#define EPTE_READ_ACCESS_BIT                                         0
#define EPTE_READ_ACCESS_MASK                                        0x01
#define EPTE_READ_ACCESS(_)                                          (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Write access; indicates whether writes are allowed from the 4-KByte page referenced by this entry.
     */
    UINT64 WriteAccess                                             : 1;
#define EPTE_WRITE_ACCESS_BIT                                        1
#define EPTE_WRITE_ACCESS_MASK                                       0x01
#define EPTE_WRITE_ACCESS(_)                                         (((_) >> 1) & 0x01)

    /**
     * [Bit 2] If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 4-KByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 4-KByte page controlled by this entry.
     */
    UINT64 ExecuteAccess                                           : 1;
#define EPTE_EXECUTE_ACCESS_BIT                                      2
#define EPTE_EXECUTE_ACCESS_MASK                                     0x01
#define EPTE_EXECUTE_ACCESS(_)                                       (((_) >> 2) & 0x01)

    /**
     * [Bits 5:3] EPT memory type for this 4-KByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 MemoryType                                              : 3;
#define EPTE_MEMORY_TYPE_BIT                                         3
#define EPTE_MEMORY_TYPE_MASK                                        0x07
#define EPTE_MEMORY_TYPE(_)                                          (((_) >> 3) & 0x07)

    /**
     * [Bit 6] Ignore PAT memory type for this 4-KByte page.
     *
     * @see Vol3C[28.2.6(EPT and memory Typing)]
     */
    UINT64 IgnorePat                                               : 1;
#define EPTE_IGNORE_PAT_BIT                                          6
#define EPTE_IGNORE_PAT_MASK                                         0x01
#define EPTE_IGNORE_PAT(_)                                           (((_) >> 6) & 0x01)
    UINT64 Reserved1                                               : 1;

    /**
     * [Bit 8] If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 4-KByte page
     * referenced by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Accessed                                                : 1;
#define EPTE_ACCESSED_BIT                                            8
#define EPTE_ACCESSED_MASK                                           0x01
#define EPTE_ACCESSED(_)                                             (((_) >> 8) & 0x01)

    /**
     * [Bit 9] If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 4-KByte page referenced
     * by this entry. Ignored if bit 6 of EPTP is 0.
     *
     * @see Vol3C[28.2.4(Accessed and Dirty Flags for EPT)]
     */
    UINT64 Dirty                                                   : 1;
#define EPTE_DIRTY_BIT                                               9
#define EPTE_DIRTY_MASK                                              0x01
#define EPTE_DIRTY(_)                                                (((_) >> 9) & 0x01)

    /**
     * [Bit 10] Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control
     * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 4-KByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     */
    UINT64 UserModeExecute                                         : 1;
#define EPTE_USER_MODE_EXECUTE_BIT                                   10
#define EPTE_USER_MODE_EXECUTE_MASK                                  0x01
#define EPTE_USER_MODE_EXECUTE(_)                                    (((_) >> 10) & 0x01)
    UINT64 Reserved2                                               : 1;

    /**
     * [Bits 47:12] Physical address of the 4-KByte page referenced by this entry.
     */
    UINT64 PageFrameNumber                                         : 36;
#define EPTE_PAGE_FRAME_NUMBER_BIT                                   12
#define EPTE_PAGE_FRAME_NUMBER_MASK                                  0xFFFFFFFFF
#define EPTE_PAGE_FRAME_NUMBER(_)                                    (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved3                                               : 15;

    /**
     * [Bit 63] Suppress \#VE. If the "EPT-violation \#VE" VM-execution control is 1, EPT violations caused by accesses to this
     * page are convertible to virtualization exceptions only if this bit is 0. If "EPT-violation \#VE" VMexecution control is
     * 0, this bit is ignored.
     *
     * @see Vol3C[25.5.6.1(Convertible EPT Violations)]
     */
    UINT64 SuppressVe                                              : 1;
#define EPTE_SUPPRESS_VE_BIT                                         63
#define EPTE_SUPPRESS_VE_MASK                                        0x01
#define EPTE_SUPPRESS_VE(_)                                          (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} EPTE;

/**
 * @brief Format of a common EPT Entry
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
#define EPT_ENTRY_READ_ACCESS_BIT                                    0
#define EPT_ENTRY_READ_ACCESS_MASK                                   0x01
#define EPT_ENTRY_READ_ACCESS(_)                                     (((_) >> 0) & 0x01)
    UINT64 WriteAccess                                             : 1;
#define EPT_ENTRY_WRITE_ACCESS_BIT                                   1
#define EPT_ENTRY_WRITE_ACCESS_MASK                                  0x01
#define EPT_ENTRY_WRITE_ACCESS(_)                                    (((_) >> 1) & 0x01)
    UINT64 ExecuteAccess                                           : 1;
#define EPT_ENTRY_EXECUTE_ACCESS_BIT                                 2
#define EPT_ENTRY_EXECUTE_ACCESS_MASK                                0x01
#define EPT_ENTRY_EXECUTE_ACCESS(_)                                  (((_) >> 2) & 0x01)
    UINT64 MemoryType                                              : 3;
#define EPT_ENTRY_MEMORY_TYPE_BIT                                    3
#define EPT_ENTRY_MEMORY_TYPE_MASK                                   0x07
#define EPT_ENTRY_MEMORY_TYPE(_)                                     (((_) >> 3) & 0x07)
    UINT64 IgnorePat                                               : 1;
#define EPT_ENTRY_IGNORE_PAT_BIT                                     6
#define EPT_ENTRY_IGNORE_PAT_MASK                                    0x01
#define EPT_ENTRY_IGNORE_PAT(_)                                      (((_) >> 6) & 0x01)
    UINT64 LargePage                                               : 1;
#define EPT_ENTRY_LARGE_PAGE_BIT                                     7
#define EPT_ENTRY_LARGE_PAGE_MASK                                    0x01
#define EPT_ENTRY_LARGE_PAGE(_)                                      (((_) >> 7) & 0x01)
    UINT64 Accessed                                                : 1;
#define EPT_ENTRY_ACCESSED_BIT                                       8
#define EPT_ENTRY_ACCESSED_MASK                                      0x01
#define EPT_ENTRY_ACCESSED(_)                                        (((_) >> 8) & 0x01)
    UINT64 Dirty                                                   : 1;
#define EPT_ENTRY_DIRTY_BIT                                          9
#define EPT_ENTRY_DIRTY_MASK                                         0x01
#define EPT_ENTRY_DIRTY(_)                                           (((_) >> 9) & 0x01)
    UINT64 UserModeExecute                                         : 1;
#define EPT_ENTRY_USER_MODE_EXECUTE_BIT                              10
#define EPT_ENTRY_USER_MODE_EXECUTE_MASK                             0x01
#define EPT_ENTRY_USER_MODE_EXECUTE(_)                               (((_) >> 10) & 0x01)
    UINT64 Reserved1                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
#define EPT_ENTRY_PAGE_FRAME_NUMBER_BIT                              12
#define EPT_ENTRY_PAGE_FRAME_NUMBER_MASK                             0xFFFFFFFFF
#define EPT_ENTRY_PAGE_FRAME_NUMBER(_)                               (((_) >> 12) & 0xFFFFFFFFF)
    UINT64 Reserved2                                               : 15;
    UINT64 SuppressVe                                              : 1;
#define EPT_ENTRY_SUPPRESS_VE_BIT                                    63
#define EPT_ENTRY_SUPPRESS_VE_MASK                                   0x01
#define EPT_ENTRY_SUPPRESS_VE(_)                                     (((_) >> 63) & 0x01)
  };

  UINT64 Flags;
} EPT_ENTRY;

/**
 * @defgroup EPT_TABLE_LEVEL \
 *           EPT Table level numbers
 *
 * EPT Table level numbers.
 * @{
 */
#define LEVEL_PML4E                                                  0x00000003
#define LEVEL_PDPTE                                                  0x00000002
#define LEVEL_PDE                                                    0x00000001
#define LEVEL_PTE                                                    0x00000000
/**
 * @}
 */

/**
 * @defgroup EPT_ENTRY_COUNT \
 *           EPT Entry counts
 *
 * EPT Entry counts.
 * @{
 */
#define PML4_ENTRY_COUNT                                             0x00000200
#define PDPTE_ENTRY_COUNT                                            0x00000200
#define PDE_ENTRY_COUNT                                              0x00000200
/**
 * @}
 */

/**
 * @defgroup EPT_MEMORY_TYPE \
 *           EPT memory type
 *
 * The effective memory type of a memory access using a guest-physical address (an access that is translated using EPT) is
 * the memory type that is used to access memory. The effective memory type is based on the value of bit 30 (cache
 * disable-CD) in control register CR0; the last EPT paging-structure entry used to translate the guestphysical address
 * (either an EPT PDE with bit 7 set to 1 or an EPT PTE); and the PAT memory type (see below):
 * - The PAT memory type depends on the value of CR0.PG:
 *   * If CR0.PG = 0, the PAT memory type is WB (writeback).
 *   * If CR0.PG = 1, the PAT memory type is the memory type selected from the IA32_PAT MSR.
 * - The EPT memory type is specified in bits 5:3 of the last EPT paging-structure entry: 0 = UC; 1 = WC; 4 = WT; 5 = WP;
 * and 6 = WB. Other values are reserved and cause EPT misconfigurations.
 * - If CR0.CD = 0, the effective memory type depends upon the value of bit 6 of the last EPT paging-structure entry:
 *   * If the value is 0, the effective memory type is the combination of the EPT memory type and the PAT memory type,
 *   using the EPT memory type in place of the MTRR memory type.
 *   * If the value is 1, the memory type used for the access is the EPT memory type. The PAT memory type is ignored.
 * - If CR0.CD = 1, the effective memory type is UC.
 *   The MTRRs have no effect on the memory type used for an access to a guest-physical address.
 *
 * @see MemoryType.yml
 * @see Vol3A[11.5.2.2(Selecting Memory Types for Pentium III and More Recent Processor Families)]
 * @see Vol3A[11.12.3(Selecting a Memory Type from the PAT)]
 * @see Vol3C[28.2.3(EPT-Induced VM Exits)]
 * @see Vol3A[11.11(MEMORY TYPE RANGE REGISTERS (MTRRS))] (reference)
 * @{
 */
#define EPT_MEMORY_TYPE_UNCACHEABLE                                  0x00000000
#define EPT_MEMORY_TYPE_WRITE_COMBINING                              0x00000001
#define EPT_MEMORY_TYPE_WRITE_THROUGH                                0x00000004
#define EPT_MEMORY_TYPE_WRITE_PROTECTED                              0x00000005
#define EPT_MEMORY_TYPE_WRITE_BACK                                   0x00000006
#define EPT_MEMORY_TYPE_UNCACHED                                     0x00000007
#define EPT_MEMORY_TYPE_INVALID                                      0x000000FF
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS \
 *           VMCS (VM Control Structure)
 *
 * Every component of the VMCS is encoded by a 32-bit field that can be used by VMREAD and VMWRITE. This enumerates all
 * fields in the VMCS and their encodings. Fields are grouped by width (16-bit, 32-bit, etc.) and type (guest-state,
 * host-state, etc.).
 *
 * @see Vol3D[B(APPENDIX B FIELD ENCODING IN VMCS)] (reference)
 * @{
 */
typedef union
{
  struct
  {
    /**
     * [Bit 0] Access type (0 = full; 1 = high); must be full for 16-bit, 32-bit, and natural-width fields.
     */
    UINT16 AccessType                                              : 1;
#define VMCS_COMPONENT_ENCODING_ACCESS_TYPE_BIT                      0
#define VMCS_COMPONENT_ENCODING_ACCESS_TYPE_MASK                     0x01
#define VMCS_COMPONENT_ENCODING_ACCESS_TYPE(_)                       (((_) >> 0) & 0x01)

    /**
     * [Bits 9:1] Index.
     */
    UINT16 Index                                                   : 9;
#define VMCS_COMPONENT_ENCODING_INDEX_BIT                            1
#define VMCS_COMPONENT_ENCODING_INDEX_MASK                           0x1FF
#define VMCS_COMPONENT_ENCODING_INDEX(_)                             (((_) >> 1) & 0x1FF)

    /**
     * [Bits 11:10] Type:
     * 0: control
     * 1: VM-exit information
     * 2: guest state
     * 3: host state
     */
    UINT16 Type                                                    : 2;
#define VMCS_COMPONENT_ENCODING_TYPE_BIT                             10
#define VMCS_COMPONENT_ENCODING_TYPE_MASK                            0x03
#define VMCS_COMPONENT_ENCODING_TYPE(_)                              (((_) >> 10) & 0x03)

    /**
     * [Bit 12] Reserved (must be 0).
     */
    UINT16 MustBeZero                                              : 1;
#define VMCS_COMPONENT_ENCODING_MUST_BE_ZERO_BIT                     12
#define VMCS_COMPONENT_ENCODING_MUST_BE_ZERO_MASK                    0x01
#define VMCS_COMPONENT_ENCODING_MUST_BE_ZERO(_)                      (((_) >> 12) & 0x01)

    /**
     * [Bits 14:13] Width:
     * 0: 16-bit
     * 1: 64-bit
     * 2: 32-bit
     * 3: natural-width
     */
    UINT16 Width                                                   : 2;
#define VMCS_COMPONENT_ENCODING_WIDTH_BIT                            13
#define VMCS_COMPONENT_ENCODING_WIDTH_MASK                           0x03
#define VMCS_COMPONENT_ENCODING_WIDTH(_)                             (((_) >> 13) & 0x03)
    UINT16 Reserved1                                               : 1;
  };

  UINT16 Flags;
} VMCS_COMPONENT_ENCODING;

/**
 * @defgroup VMCS_16_BIT \
 *           16-Bit Fields
 *
 * 16-Bit Fields.
 *
 * @see Vol3D[B.1(16-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_16_BIT_CONTROL_FIELDS \
 *           16-Bit Control Fields
 *
 * 16-Bit Control Fields.
 * @{
 */
/**
 * Virtual-processor identifier (VPID).
 *
 * @remarks This field exists only on processors that support the 1-setting of the "enable VPID" VM-execution control.
 */
#define VMCS_CTRL_VIRTUAL_PROCESSOR_IDENTIFIER                       0x00000000

/**
 * Posted-interrupt notification vector.
 *
 * @remarks This field exists only on processors that support the 1-setting of the "process posted interrupts" VM-execution
 *          control.
 */
#define VMCS_CTRL_POSTED_INTERRUPT_NOTIFICATION_VECTOR               0x00000002

/**
 * EPTP index.
 *
 * @remarks This field exists only on processors that support the 1-setting of the "EPT-violation \#VE" VM-execution
 *          control.
 */
#define VMCS_CTRL_EPTP_INDEX                                         0x00000004

/**
 * @}
 */

/**
 * @defgroup VMCS_16_BIT_GUEST_STATE_FIELDS \
 *           16-Bit Guest-State Fields
 *
 * 16-Bit Guest-State Fields.
 * @{
 */
/**
 * Guest ES selector.
 */
#define VMCS_GUEST_ES_SELECTOR                                       0x00000800

/**
 * Guest CS selector.
 */
#define VMCS_GUEST_CS_SELECTOR                                       0x00000802

/**
 * Guest SS selector.
 */
#define VMCS_GUEST_SS_SELECTOR                                       0x00000804

/**
 * Guest DS selector.
 */
#define VMCS_GUEST_DS_SELECTOR                                       0x00000806

/**
 * Guest FS selector.
 */
#define VMCS_GUEST_FS_SELECTOR                                       0x00000808

/**
 * Guest GS selector.
 */
#define VMCS_GUEST_GS_SELECTOR                                       0x0000080A

/**
 * Guest LDTR selector.
 */
#define VMCS_GUEST_LDTR_SELECTOR                                     0x0000080C

/**
 * Guest TR selector.
 */
#define VMCS_GUEST_TR_SELECTOR                                       0x0000080E

/**
 * Guest interrupt status.
 *
 * @remarks This field exists only on processors that support the 1-setting of the "virtual-interrupt delivery"
 *          VM-execution control.
 */
#define VMCS_GUEST_INTERRUPT_STATUS                                  0x00000810

/**
 * PML index.
 *
 * @remarks This field exists only on processors that support the 1-setting of the "enable PML" VM-execution control.
 */
#define VMCS_GUEST_PML_INDEX                                         0x00000812

/**
 * @}
 */

/**
 * @defgroup VMCS_16_BIT_HOST_STATE_FIELDS \
 *           16-Bit Host-State Fields
 *
 * 16-Bit Host-State Fields.
 * @{
 */
/**
 * Host ES selector.
 */
#define VMCS_HOST_ES_SELECTOR                                        0x00000C00

/**
 * Host CS selector.
 */
#define VMCS_HOST_CS_SELECTOR                                        0x00000C02

/**
 * Host SS selector.
 */
#define VMCS_HOST_SS_SELECTOR                                        0x00000C04

/**
 * Host DS selector.
 */
#define VMCS_HOST_DS_SELECTOR                                        0x00000C06

/**
 * Host FS selector.
 */
#define VMCS_HOST_FS_SELECTOR                                        0x00000C08

/**
 * Host GS selector.
 */
#define VMCS_HOST_GS_SELECTOR                                        0x00000C0A

/**
 * Host TR selector.
 */
#define VMCS_HOST_TR_SELECTOR                                        0x00000C0C

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT \
 *           64-Bit Fields
 *
 * 64-Bit Fields.
 *
 * @see Vol3D[B.2(64-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_64_BIT_CONTROL_FIELDS \
 *           64-Bit Control Fields
 *
 * 64-Bit Control Fields.
 * @{
 */
/**
 * Address of I/O bitmap A.
 */
#define VMCS_CTRL_IO_BITMAP_A_ADDRESS                                0x00002000

/**
 * Address of I/O bitmap B.
 */
#define VMCS_CTRL_IO_BITMAP_B_ADDRESS                                0x00002002

/**
 * Address of MSR bitmaps.
 */
#define VMCS_CTRL_MSR_BITMAP_ADDRESS                                 0x00002004

/**
 * VM-exit MSR-store address.
 */
#define VMCS_CTRL_VMEXIT_MSR_STORE_ADDRESS                           0x00002006

/**
 * VM-exit MSR-load address.
 */
#define VMCS_CTRL_VMEXIT_MSR_LOAD_ADDRESS                            0x00002008

/**
 * VM-entry MSR-load address.
 */
#define VMCS_CTRL_VMENTRY_MSR_LOAD_ADDRESS                           0x0000200A

/**
 * Executive-VMCS pointer.
 */
#define VMCS_CTRL_EXECUTIVE_VMCS_POINTER                             0x0000200C

/**
 * PML address.
 */
#define VMCS_CTRL_PML_ADDRESS                                        0x0000200E

/**
 * TSC offset.
 */
#define VMCS_CTRL_TSC_OFFSET                                         0x00002010

/**
 * Virtual-APIC address.
 */
#define VMCS_CTRL_VIRTUAL_APIC_ADDRESS                               0x00002012

/**
 * APIC-access address.
 */
#define VMCS_CTRL_APIC_ACCESS_ADDRESS                                0x00002014

/**
 * Posted-interrupt descriptor address
 */
#define VMCS_CTRL_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS                0x00002016

/**
 * VM-function controls.
 */
#define VMCS_CTRL_VMFUNC_CONTROLS                                    0x00002018

/**
 * EPT pointer.
 */
#define VMCS_CTRL_EPT_POINTER                                        0x0000201A

/**
 * EOI-exit bitmap 0.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_0                                  0x0000201C

/**
 * EOI-exit bitmap 1.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_1                                  0x0000201E

/**
 * EOI-exit bitmap 2.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_2                                  0x00002020

/**
 * EOI-exit bitmap 3.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_3                                  0x00002022

/**
 * EPTP-list address.
 */
#define VMCS_CTRL_EPT_POINTER_LIST_ADDRESS                           0x00002024

/**
 * VMREAD-bitmap address.
 */
#define VMCS_CTRL_VMREAD_BITMAP_ADDRESS                              0x00002026

/**
 * VMWRITE-bitmap address.
 */
#define VMCS_CTRL_VMWRITE_BITMAP_ADDRESS                             0x00002028

/**
 * Virtualization-exception information address.
 */
#define VMCS_CTRL_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS       0x0000202A

/**
 * XSS-exiting bitmap.
 */
#define VMCS_CTRL_XSS_EXITING_BITMAP                                 0x0000202C

/**
 * ENCLS-exiting bitmap.
 */
#define VMCS_CTRL_ENCLS_EXITING_BITMAP                               0x0000202E

/**
 * TSC multiplier.
 */
#define VMCS_CTRL_TSC_MULTIPLIER                                     0x00002032

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_READ_ONLY_DATA_FIELDS \
 *           64-Bit Read-Only Data Field
 *
 * 64-Bit Read-Only Data Field.
 * @{
 */
/**
 * Guest-physical address.
 */
#define VMCS_GUEST_PHYSICAL_ADDRESS                                  0x00002400

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_GUEST_STATE_FIELDS \
 *           64-Bit Guest-State Fields
 *
 * 64-Bit Guest-State Fields.
 * @{
 */
/**
 * VMCS link pointer.
 */
#define VMCS_GUEST_VMCS_LINK_POINTER                                 0x00002800

/**
 * Guest IA32_DEBUGCTL.
 */
#define VMCS_GUEST_DEBUGCTL                                          0x00002802

/**
 * Guest IA32_PAT.
 */
#define VMCS_GUEST_PAT                                               0x00002804

/**
 * Guest IA32_EFER.
 */
#define VMCS_GUEST_EFER                                              0x00002806

/**
 * Guest IA32_PERF_GLOBAL_CTRL.
 */
#define VMCS_GUEST_PERF_GLOBAL_CTRL                                  0x00002808

/**
 * Guest PDPTE0.
 */
#define VMCS_GUEST_PDPTE0                                            0x0000280A

/**
 * Guest PDPTE1.
 */
#define VMCS_GUEST_PDPTE1                                            0x0000280C

/**
 * Guest PDPTE2.
 */
#define VMCS_GUEST_PDPTE2                                            0x0000280E

/**
 * Guest PDPTE3.
 */
#define VMCS_GUEST_PDPTE3                                            0x00002810

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_HOST_STATE_FIELDS \
 *           64-Bit Host-State Fields
 *
 * 64-Bit Host-State Fields.
 * @{
 */
/**
 * Host IA32_PAT.
 */
#define VMCS_HOST_PAT                                                0x00002C00

/**
 * Host IA32_EFER.
 */
#define VMCS_HOST_EFER                                               0x00002C02

/**
 * Host IA32_PERF_GLOBAL_CTRL.
 */
#define VMCS_HOST_PERF_GLOBAL_CTRL                                   0x00002C04

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT \
 *           32-Bit Fields
 *
 * 32-Bit Fields.
 *
 * @see Vol3D[B.3(32-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_32_BIT_CONTROL_FIELDS \
 *           32-Bit Control Fields
 *
 * 32-Bit Control Fields.
 * @{
 */
/**
 * Pin-based VM-execution controls.
 */
#define VMCS_CTRL_PIN_BASED_VM_EXECUTION_CONTROLS                    0x00004000

/**
 * Primary processor-based VM-execution controls.
 */
#define VMCS_CTRL_PROCESSOR_BASED_VM_EXECUTION_CONTROLS              0x00004002

/**
 * Exception bitmap.
 */
#define VMCS_CTRL_EXCEPTION_BITMAP                                   0x00004004

/**
 * Page-fault error-code mask.
 */
#define VMCS_CTRL_PAGEFAULT_ERROR_CODE_MASK                          0x00004006

/**
 * Page-fault error-code match.
 */
#define VMCS_CTRL_PAGEFAULT_ERROR_CODE_MATCH                         0x00004008

/**
 * CR3-target count.
 */
#define VMCS_CTRL_CR3_TARGET_COUNT                                   0x0000400A

/**
 * VM-exit controls.
 */
#define VMCS_CTRL_VMEXIT_CONTROLS                                    0x0000400C

/**
 * VM-exit MSR-store count.
 */
#define VMCS_CTRL_VMEXIT_MSR_STORE_COUNT                             0x0000400E

/**
 * VM-exit MSR-load count.
 */
#define VMCS_CTRL_VMEXIT_MSR_LOAD_COUNT                              0x00004010

/**
 * VM-entry controls.
 */
#define VMCS_CTRL_VMENTRY_CONTROLS                                   0x00004012

/**
 * VM-entry MSR-load count.
 */
#define VMCS_CTRL_VMENTRY_MSR_LOAD_COUNT                             0x00004014

/**
 * VM-entry interruption-information field.
 */
#define VMCS_CTRL_VMENTRY_INTERRUPTION_INFORMATION_FIELD             0x00004016

/**
 * VM-entry exception error code.
 */
#define VMCS_CTRL_VMENTRY_EXCEPTION_ERROR_CODE                       0x00004018

/**
 * VM-entry instruction length.
 */
#define VMCS_CTRL_VMENTRY_INSTRUCTION_LENGTH                         0x0000401A

/**
 * TPR threshold.
 */
#define VMCS_CTRL_TPR_THRESHOLD                                      0x0000401C

/**
 * Secondary processor-based VM-execution controls.
 */
#define VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS    0x0000401E

/**
 * PLE_Gap.
 */
#define VMCS_CTRL_PLE_GAP                                            0x00004020

/**
 * PLE_Window.
 */
#define VMCS_CTRL_PLE_WINDOW                                         0x00004022

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_READ_ONLY_DATA_FIELDS \
 *           32-Bit Read-Only Data Fields
 *
 * 32-Bit Read-Only Data Fields.
 * @{
 */
/**
 * VM-instruction error.
 */
#define VMCS_VM_INSTRUCTION_ERROR                                    0x00004400

/**
 * Exit reason.
 */
#define VMCS_EXIT_REASON                                             0x00004402

/**
 * VM-exit interruption information.
 */
#define VMCS_VMEXIT_INTERRUPTION_INFORMATION                         0x00004404

/**
 * VM-exit interruption error code.
 */
#define VMCS_VMEXIT_INTERRUPTION_ERROR_CODE                          0x00004406

/**
 * IDT-vectoring information field.
 */
#define VMCS_IDT_VECTORING_INFORMATION                               0x00004408

/**
 * IDT-vectoring error code.
 */
#define VMCS_IDT_VECTORING_ERROR_CODE                                0x0000440A

/**
 * VM-exit instruction length.
 */
#define VMCS_VMEXIT_INSTRUCTION_LENGTH                               0x0000440C

/**
 * VM-exit instruction information.
 */
#define VMCS_VMEXIT_INSTRUCTION_INFO                                 0x0000440E

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_GUEST_STATE_FIELDS \
 *           32-Bit Guest-State Fields
 *
 * 32-Bit Guest-State Fields.
 * @{
 */
/**
 * Guest ES limit.
 */
#define VMCS_GUEST_ES_LIMIT                                          0x00004800

/**
 * Guest CS limit.
 */
#define VMCS_GUEST_CS_LIMIT                                          0x00004802

/**
 * Guest SS limit.
 */
#define VMCS_GUEST_SS_LIMIT                                          0x00004804

/**
 * Guest DS limit.
 */
#define VMCS_GUEST_DS_LIMIT                                          0x00004806

/**
 * Guest FS limit.
 */
#define VMCS_GUEST_FS_LIMIT                                          0x00004808

/**
 * Guest GS limit.
 */
#define VMCS_GUEST_GS_LIMIT                                          0x0000480A

/**
 * Guest LDTR limit.
 */
#define VMCS_GUEST_LDTR_LIMIT                                        0x0000480C

/**
 * Guest TR limit.
 */
#define VMCS_GUEST_TR_LIMIT                                          0x0000480E

/**
 * Guest GDTR limit.
 */
#define VMCS_GUEST_GDTR_LIMIT                                        0x00004810

/**
 * Guest IDTR limit.
 */
#define VMCS_GUEST_IDTR_LIMIT                                        0x00004812

/**
 * Guest ES access rights.
 */
#define VMCS_GUEST_ES_ACCESS_RIGHTS                                  0x00004814

/**
 * Guest CS access rights.
 */
#define VMCS_GUEST_CS_ACCESS_RIGHTS                                  0x00004816

/**
 * Guest SS access rights.
 */
#define VMCS_GUEST_SS_ACCESS_RIGHTS                                  0x00004818

/**
 * Guest DS access rights.
 */
#define VMCS_GUEST_DS_ACCESS_RIGHTS                                  0x0000481A

/**
 * Guest FS access rights.
 */
#define VMCS_GUEST_FS_ACCESS_RIGHTS                                  0x0000481C

/**
 * Guest GS access rights.
 */
#define VMCS_GUEST_GS_ACCESS_RIGHTS                                  0x0000481E

/**
 * Guest LDTR access rights.
 */
#define VMCS_GUEST_LDTR_ACCESS_RIGHTS                                0x00004820

/**
 * Guest TR access rights.
 */
#define VMCS_GUEST_TR_ACCESS_RIGHTS                                  0x00004822

/**
 * Guest interruptibility state.
 */
#define VMCS_GUEST_INTERRUPTIBILITY_STATE                            0x00004824

/**
 * Guest activity state.
 */
#define VMCS_GUEST_ACTIVITY_STATE                                    0x00004826

/**
 * Guest SMBASE.
 */
#define VMCS_GUEST_SMBASE                                            0x00004828

/**
 * Guest IA32_SYSENTER_CS.
 */
#define VMCS_GUEST_SYSENTER_CS                                       0x0000482A

/**
 * VMX-preemption timer value.
 */
#define VMCS_GUEST_VMX_PREEMPTION_TIMER_VALUE                        0x0000482E

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_HOST_STATE_FIELDS \
 *           32-Bit Host-State Field
 *
 * 32-Bit Host-State Field.
 * @{
 */
/**
 * Host IA32_SYSENTER_CS.
 */
#define VMCS_SYSENTER_CS                                             0x00004C00

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH \
 *           Natural-Width Fields
 *
 * Natural-Width Fields.
 *
 * @see Vol3D[B.4(NATURAL-WIDTH FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_NATURAL_WIDTH_CONTROL_FIELDS \
 *           Natural-Width Control Fields
 *
 * Natural-Width Control Fields
 * @{
 */
/**
 * CR0 guest/host mask.
 */
#define VMCS_CTRL_CR0_GUEST_HOST_MASK                                0x00006000

/**
 * CR4 guest/host mask.
 */
#define VMCS_CTRL_CR4_GUEST_HOST_MASK                                0x00006002

/**
 * CR0 read shadow.
 */
#define VMCS_CTRL_CR0_READ_SHADOW                                    0x00006004

/**
 * CR4 read shadow.
 */
#define VMCS_CTRL_CR4_READ_SHADOW                                    0x00006006

/**
 * CR3-target value 0.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_0                                 0x00006008

/**
 * CR3-target value 1.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_1                                 0x0000600A

/**
 * CR3-target value 2.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_2                                 0x0000600C

/**
 * CR3-target value 3.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_3                                 0x0000600E

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_READ_ONLY_DATA_FIELDS \
 *           Natural-Width Read-Only Data Fields
 *
 * Natural-Width Read-Only Data Fields.
 * @{
 */
/**
 * Exit qualification.
 */
#define VMCS_EXIT_QUALIFICATION                                      0x00006400

/**
 * I/O RCX.
 */
#define VMCS_IO_RCX                                                  0x00006402

/**
 * I/O RSI.
 */
#define VMCS_IO_RSX                                                  0x00006404

/**
 * I/O RDI.
 */
#define VMCS_IO_RDI                                                  0x00006406

/**
 * I/O RIP.
 */
#define VMCS_IO_RIP                                                  0x00006408

/**
 * Guest-linear address.
 */
#define VMCS_EXIT_GUEST_LINEAR_ADDRESS                               0x0000640A

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_GUEST_STATE_FIELDS \
 *           Natural-Width Guest-State Fields
 *
 * Natural-Width Guest-State Fields.
 * @{
 */
/**
 * Guest CR0.
 */
#define VMCS_GUEST_CR0                                               0x00006800

/**
 * Guest CR3.
 */
#define VMCS_GUEST_CR3                                               0x00006802

/**
 * Guest CR4.
 */
#define VMCS_GUEST_CR4                                               0x00006804

/**
 * Guest ES base.
 */
#define VMCS_GUEST_ES_BASE                                           0x00006806

/**
 * Guest CS base.
 */
#define VMCS_GUEST_CS_BASE                                           0x00006808

/**
 * Guest SS base.
 */
#define VMCS_GUEST_SS_BASE                                           0x0000680A

/**
 * Guest DS base.
 */
#define VMCS_GUEST_DS_BASE                                           0x0000680C

/**
 * Guest FS base.
 */
#define VMCS_GUEST_FS_BASE                                           0x0000680E

/**
 * Guest GS base.
 */
#define VMCS_GUEST_GS_BASE                                           0x00006810

/**
 * Guest LDTR base.
 */
#define VMCS_GUEST_LDTR_BASE                                         0x00006812

/**
 * Guest TR base.
 */
#define VMCS_GUEST_TR_BASE                                           0x00006814

/**
 * Guest GDTR base.
 */
#define VMCS_GUEST_GDTR_BASE                                         0x00006816

/**
 * Guest IDTR base.
 */
#define VMCS_GUEST_IDTR_BASE                                         0x00006818

/**
 * Guest DR7.
 */
#define VMCS_GUEST_DR7                                               0x0000681A

/**
 * Guest RSP.
 */
#define VMCS_GUEST_RSP                                               0x0000681C

/**
 * Guest RIP.
 */
#define VMCS_GUEST_RIP                                               0x0000681E

/**
 * Guest RFLAGS.
 */
#define VMCS_GUEST_RFLAGS                                            0x00006820

/**
 * Guest pending debug exceptions.
 */
#define VMCS_GUEST_PENDING_DEBUG_EXCEPTIONS                          0x00006822

/**
 * Guest IA32_SYSENTER_ESP.
 */
#define VMCS_GUEST_SYSENTER_ESP                                      0x00006824

/**
 * Guest IA32_SYSENTER_EIP.
 */
#define VMCS_GUEST_SYSENTER_EIP                                      0x00006826

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_HOST_STATE_FIELDS \
 *           Natural-Width Host-State Fields
 *
 * Natural-Width Host-State Fields.
 * @{
 */
/**
 * Host CR0.
 */
#define VMCS_HOST_CR0                                                0x00006C00

/**
 * Host CR3.
 */
#define VMCS_HOST_CR3                                                0x00006C02

/**
 * Host CR4.
 */
#define VMCS_HOST_CR4                                                0x00006C04

/**
 * Host FS base.
 */
#define VMCS_HOST_FS_BASE                                            0x00006C06

/**
 * Host GS base.
 */
#define VMCS_HOST_GS_BASE                                            0x00006C08

/**
 * Host TR base.
 */
#define VMCS_HOST_TR_BASE                                            0x00006C0A

/**
 * Host GDTR base.
 */
#define VMCS_HOST_GDTR_BASE                                          0x00006C0C

/**
 * Host IDTR base.
 */
#define VMCS_HOST_IDTR_BASE                                          0x00006C0E

/**
 * Host IA32_SYSENTER_ESP.
 */
#define VMCS_HOST_SYSENTER_ESP                                       0x00006C10

/**
 * Host IA32_SYSENTER_EIP.
 */
#define VMCS_HOST_SYSENTER_EIP                                       0x00006C12

/**
 * Host RSP.
 */
#define VMCS_HOST_RSP                                                0x00006C14

/**
 * Host RIP.
 */
#define VMCS_HOST_RIP                                                0x00006C16

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup APIC \
 *           Advanced Programmable Interrupt Controller (APIC)
 *
 * Software interacts with the local APIC by reading and writing its registers. APIC registers are memory-mapped to a
 * 4-KByte region of the processor's physical address space with an initial starting address of FEE00000H. For correct APIC
 * operation, this address space must be mapped to an area of memory that has been designated as strong uncacheable (UC).
 *
 * @remarks Registers are 32 bits, 64 bits, or 256 bits in width; all are aligned on 128-bit boundaries. All 32-bit
 *          registers should be accessed using 128-bit aligned 32-bit loads or stores. Some processors may support loads and stores
 *          of less than 32 bits to some of the APIC registers. This is model specific behavior and is not guaranteed to work on all
 *          processors. Any FP/MMX/SSE access to an APIC register, or any access that touches bytes 4 through 15 of an APIC register
 *          may cause undefined behavior and must not be executed. This undefined behavior could include hangs, incorrect results or
 *          unexpected exceptions, including machine checks, and may vary between implementations. Wider registers (64-bit or
 *          256-bit) must be accessed using multiple 32-bit loads or stores, with all accesses being 128-bit aligned.
 * @see Vol3A[10.4.1(The Local APIC Block Diagram)] (reference)
 * @{
 */
/**
 * Local APIC Base Address.
 *
 * @remarks Reserved.
 */
#define APIC_BASE_ADDRESS                                            0xFEE00000

/**
 * Local APIC ID Register.
 */
#define APIC_ID                                                      0xFEE00020

/**
 * Local APIC Version Register.
 */
#define APIC_VERSION                                                 0xFEE00030

/**
 * Task Priority Register (TPR).
 */
#define APIC_TASK_PRIORITY                                           0xFEE00080

/**
 * Arbitration Priority Register (APR).
 */
#define APIC_ARBITRATION_PRIORITY                                    0xFEE00090

/**
 * Processor Priority Register (PPR).
 */
#define APIC_PROCESSOR_PRIORITY                                      0xFEE000A0

/**
 * EOI Register.
 */
#define APIC_EOI                                                     0xFEE000B0

/**
 * Remote Read Register (RRD).
 */
#define APIC_REMOTE_READ                                             0xFEE000C0

/**
 * Logical Destination Register.
 */
#define APIC_LOGICAL_DESTINATION                                     0xFEE000D0

/**
 * Destination Format Register.
 *
 * @see Vol3A[10.6.2.2(Logical Destination Mode)]
 */
#define APIC_DESTINATION_FORMAT                                      0xFEE000E0

/**
 * Spurious Interrupt Vector Register.
 *
 * @see Vol3A[10.9(SPURIOUS INTERRUPT)]
 */
#define APIC_SPURIOUS_INTERRUPT_VECTOR                               0xFEE000F0

/**
 * In-Service Register (ISR); bits 31:0.
 */
#define APIC_IN_SERVICE_BITS_31_0                                    0xFEE00100

/**
 * In-Service Register (ISR); bits 63:32.
 */
#define APIC_IN_SERVICE_BITS_63_32                                   0xFEE00110

/**
 * In-Service Register (ISR); bits 95:64.
 */
#define APIC_IN_SERVICE_BITS_95_64                                   0xFEE00120

/**
 * In-Service Register (ISR); bits 127:96.
 */
#define APIC_IN_SERVICE_BITS_127_96                                  0xFEE00130

/**
 * In-Service Register (ISR); bits 159:128.
 */
#define APIC_IN_SERVICE_BITS_159_128                                 0xFEE00140

/**
 * In-Service Register (ISR); bits 191:160.
 */
#define APIC_IN_SERVICE_BITS_191_160                                 0xFEE00150

/**
 * In-Service Register (ISR); bits 223:192.
 */
#define APIC_IN_SERVICE_BITS_223_192                                 0xFEE00160

/**
 * In-Service Register (ISR); bits 255:224.
 */
#define APIC_IN_SERVICE_BITS_255_224                                 0xFEE00170

/**
 * Trigger Mode Register (TMR); bits 31:0.
 */
#define APIC_TRIGGER_MODE_BITS_31_0                                  0xFEE00180

/**
 * Trigger Mode Register (TMR); bits 63:32.
 */
#define APIC_TRIGGER_MODE_BITS_63_32                                 0xFEE00190

/**
 * Trigger Mode Register (TMR); bits 95:64.
 */
#define APIC_TRIGGER_MODE_BITS_95_64                                 0xFEE001A0

/**
 * Trigger Mode Register (TMR); bits 127:96.
 */
#define APIC_TRIGGER_MODE_BITS_127_96                                0xFEE001B0

/**
 * Trigger Mode Register (TMR); bits 159:128.
 */
#define APIC_TRIGGER_MODE_BITS_159_128                               0xFEE001C0

/**
 * Trigger Mode Register (TMR); bits 191:160.
 */
#define APIC_TRIGGER_MODE_BITS_191_160                               0xFEE001D0

/**
 * Trigger Mode Register (TMR); bits 223:192.
 */
#define APIC_TRIGGER_MODE_BITS_223_192                               0xFEE001E0

/**
 * Trigger Mode Register (TMR); bits 255:224.
 */
#define APIC_TRIGGER_MODE_BITS_255_224                               0xFEE001F0

/**
 * Interrupt Request Register (IRR); bits 31:0.
 */
#define APIC_INTERRUPT_REQUEST_BITS_31_0                             0xFEE00200

/**
 * Interrupt Request Register (IRR); bits 63:32.
 */
#define APIC_INTERRUPT_REQUEST_BITS_63_32                            0xFEE00210

/**
 * Interrupt Request Register (IRR); bits 95:64.
 */
#define APIC_INTERRUPT_REQUEST_BITS_95_64                            0xFEE00220

/**
 * Interrupt Request Register (IRR); bits 127:96.
 */
#define APIC_INTERRUPT_REQUEST_BITS_127_96                           0xFEE00230

/**
 * Interrupt Request Register (IRR); bits 159:128.
 */
#define APIC_INTERRUPT_REQUEST_BITS_159_128                          0xFEE00240

/**
 * Interrupt Request Register (IRR); bits 191:160.
 */
#define APIC_INTERRUPT_REQUEST_BITS_191_160                          0xFEE00250

/**
 * Interrupt Request Register (IRR); bits 223:192.
 */
#define APIC_INTERRUPT_REQUEST_BITS_223_192                          0xFEE00260

/**
 * Interrupt Request Register (IRR); bits 255:224.
 */
#define APIC_INTERRUPT_REQUEST_BITS_255_224                          0xFEE00270

/**
 * Error Status Register.
 */
#define APIC_ERROR_STATUS                                            0xFEE00280

/**
 * LVT Corrected Machine Check Interrupt (CMCI) Register.
 */
#define APIC_LVT_CORRECTED_MACHINE_CHECK_INTERRUPT                   0xFEE002F0

/**
 * Interrupt Command Register (ICR); bits 0-31.
 */
#define APIC_INTERRUPT_COMMAND_BITS_0_31                             0xFEE00300

/**
 * Interrupt Command Register (ICR); bits 32-63.
 */
#define APIC_INTERRUPT_COMMAND_BITS_32_63                            0xFEE00310

/**
 * LVT Timer Register.
 */
#define APIC_LVT_TIMER                                               0xFEE00320

/**
 * LVT Thermal Sensor Register.
 */
#define APIC_LVT_THERMAL_SENSOR                                      0xFEE00330

/**
 * LVT Performance Monitoring Counters Register.
 */
#define APIC_LVT_PERFORMANCE_MONITORING_COUNTERS                     0xFEE00340

/**
 * LVT LINT0 Register.
 */
#define APIC_LVT_LINT0                                               0xFEE00350

/**
 * LVT LINT1 Register.
 */
#define APIC_LVT_LINT1                                               0xFEE00360

/**
 * LVT Error Register.
 */
#define APIC_LVT_ERROR                                               0xFEE00370

/**
 * Initial Count Register (for Timer).
 */
#define APIC_INITIAL_COUNT                                           0xFEE00380

/**
 * Current Count Register (for Timer).
 */
#define APIC_CURRENT_COUNT                                           0xFEE00390

/**
 * Divide Configuration Register (for Timer).
 */
#define APIC_DIVIDE_CONFIGURATION                                    0xFEE003E0

/**
 * @}
 */

/**
 * The 32-bit EFLAGS register contains a group of status flags, a control flag, and a group of system flags. The status
 * flags (bits 0, 2, 4, 6, 7, and 11) of the EFLAGS register indicate the results of arithmetic instructions, such as the
 * ADD, SUB, MUL, and DIV instructions.
 * The system flags and IOPL field in the EFLAGS register control operating-system or executive operations.
 *
 * @see Vol1[3.4.3(EFLAGS)] (reference)
 */
typedef union
{
  struct
  {
    /**
     * @brief Carry flag
     *
     * [Bit 0] Set if an arithmetic operation generates a carry or a borrow out of the mostsignificant bit of the result;
     * cleared otherwise. This flag indicates an overflow condition for unsigned-integer arithmetic. It is also used in
     * multiple-precision arithmetic.
     */
    UINT32 CarryFlag                                               : 1;
#define EFLAGS_CARRY_FLAG_BIT                                        0
#define EFLAGS_CARRY_FLAG_MASK                                       0x01
#define EFLAGS_CARRY_FLAG(_)                                         (((_) >> 0) & 0x01)

    /**
     * [Bit 1] Reserved - always 1
     */
    UINT32 ReadAs1                                                 : 1;
#define EFLAGS_READ_AS_1_BIT                                         1
#define EFLAGS_READ_AS_1_MASK                                        0x01
#define EFLAGS_READ_AS_1(_)                                          (((_) >> 1) & 0x01)

    /**
     * @brief Parity flag
     *
     * [Bit 2] Set if the least-significant byte of the result contains an even number of 1 bits; cleared otherwise.
     */
    UINT32 ParityFlag                                              : 1;
#define EFLAGS_PARITY_FLAG_BIT                                       2
#define EFLAGS_PARITY_FLAG_MASK                                      0x01
#define EFLAGS_PARITY_FLAG(_)                                        (((_) >> 2) & 0x01)
    UINT32 Reserved1                                               : 1;

    /**
     * @brief Auxiliary Carry flag
     *
     * [Bit 4] Set if an arithmetic operation generates a carry or a borrow out of bit 3 of the result; cleared otherwise. This
     * flag is used in binary-coded decimal (BCD) arithmetic.
     */
    UINT32 AuxiliaryCarryFlag                                      : 1;
#define EFLAGS_AUXILIARY_CARRY_FLAG_BIT                              4
#define EFLAGS_AUXILIARY_CARRY_FLAG_MASK                             0x01
#define EFLAGS_AUXILIARY_CARRY_FLAG(_)                               (((_) >> 4) & 0x01)
    UINT32 Reserved2                                               : 1;

    /**
     * @brief Zero flag
     *
     * [Bit 6] Set if the result is zero; cleared otherwise.
     */
    UINT32 ZeroFlag                                                : 1;
#define EFLAGS_ZERO_FLAG_BIT                                         6
#define EFLAGS_ZERO_FLAG_MASK                                        0x01
#define EFLAGS_ZERO_FLAG(_)                                          (((_) >> 6) & 0x01)

    /**
     * @brief Sign flag
     *
     * [Bit 7] Set equal to the most-significant bit of the result, which is the sign bit of a signed integer. (0 indicates a
     * positive value and 1 indicates a negative value.)
     */
    UINT32 SignFlag                                                : 1;
#define EFLAGS_SIGN_FLAG_BIT                                         7
#define EFLAGS_SIGN_FLAG_MASK                                        0x01
#define EFLAGS_SIGN_FLAG(_)                                          (((_) >> 7) & 0x01)

    /**
     * @brief Trap flag
     *
     * [Bit 8] Set to enable single-step mode for debugging; clear to disable single-step mode.
     */
    UINT32 TrapFlag                                                : 1;
#define EFLAGS_TRAP_FLAG_BIT                                         8
#define EFLAGS_TRAP_FLAG_MASK                                        0x01
#define EFLAGS_TRAP_FLAG(_)                                          (((_) >> 8) & 0x01)

    /**
     * @brief Interrupt enable flag
     *
     * [Bit 9] Controls the response of the processor to maskable interrupt requests. Set to respond to maskable interrupts;
     * cleared to inhibit maskable interrupts.
     */
    UINT32 InterruptEnableFlag                                     : 1;
#define EFLAGS_INTERRUPT_ENABLE_FLAG_BIT                             9
#define EFLAGS_INTERRUPT_ENABLE_FLAG_MASK                            0x01
#define EFLAGS_INTERRUPT_ENABLE_FLAG(_)                              (((_) >> 9) & 0x01)

    /**
     * @brief Direction flag
     *
     * [Bit 10] Controls string instructions (MOVS, CMPS, SCAS, LODS, and STOS). Setting the DF flag causes the string
     * instructions to auto-decrement (to process strings from high addresses to low addresses). Clearing the DF flag causes
     * the string instructions to auto-increment (process strings from low addresses to high addresses).
     */
    UINT32 DirectionFlag                                           : 1;
#define EFLAGS_DIRECTION_FLAG_BIT                                    10
#define EFLAGS_DIRECTION_FLAG_MASK                                   0x01
#define EFLAGS_DIRECTION_FLAG(_)                                     (((_) >> 10) & 0x01)

    /**
     * @brief Overflow flag
     *
     * [Bit 11] Set if the integer result is too large a positive number or too small a negative number (excluding the
     * sign-bit) to fit in the destination operand; cleared otherwise. This flag indicates an overflow condition for
     * signed-integer (two's complement) arithmetic.
     */
    UINT32 OverflowFlag                                            : 1;
#define EFLAGS_OVERFLOW_FLAG_BIT                                     11
#define EFLAGS_OVERFLOW_FLAG_MASK                                    0x01
#define EFLAGS_OVERFLOW_FLAG(_)                                      (((_) >> 11) & 0x01)

    /**
     * @brief I/O privilege level field
     *
     * [Bits 13:12] Indicates the I/O privilege level of the currently running program or task. The current privilege level
     * (CPL) of the currently running program or task must be less than or equal to the I/O privilege level to access the I/O
     * address space. The POPF and IRET instructions can modify this field only when operating at a CPL of 0.
     */
    UINT32 IoPrivilegeLevel                                        : 2;
#define EFLAGS_IO_PRIVILEGE_LEVEL_BIT                                12
#define EFLAGS_IO_PRIVILEGE_LEVEL_MASK                               0x03
#define EFLAGS_IO_PRIVILEGE_LEVEL(_)                                 (((_) >> 12) & 0x03)

    /**
     * @brief Nested task flag
     *
     * [Bit 14] Controls the chaining of interrupted and called tasks. Set when the current task is linked to the previously
     * executed task; cleared when the current task is not linked to another task.
     */
    UINT32 NestedTaskFlag                                          : 1;
#define EFLAGS_NESTED_TASK_FLAG_BIT                                  14
#define EFLAGS_NESTED_TASK_FLAG_MASK                                 0x01
#define EFLAGS_NESTED_TASK_FLAG(_)                                   (((_) >> 14) & 0x01)
    UINT32 Reserved3                                               : 1;

    /**
     * @brief Resume flag
     *
     * [Bit 16] Controls the processor's response to debug exceptions.
     */
    UINT32 ResumeFlag                                              : 1;
#define EFLAGS_RESUME_FLAG_BIT                                       16
#define EFLAGS_RESUME_FLAG_MASK                                      0x01
#define EFLAGS_RESUME_FLAG(_)                                        (((_) >> 16) & 0x01)

    /**
     * @brief Virtual-8086 mode flag
     *
     * [Bit 17] Set to enable virtual-8086 mode; clear to return to protected mode without virtual-8086 mode semantics.
     */
    UINT32 Virtual8086ModeFlag                                     : 1;
#define EFLAGS_VIRTUAL_8086_MODE_FLAG_BIT                            17
#define EFLAGS_VIRTUAL_8086_MODE_FLAG_MASK                           0x01
#define EFLAGS_VIRTUAL_8086_MODE_FLAG(_)                             (((_) >> 17) & 0x01)

    /**
     * @brief Alignment check (or access control) flag
     *
     * [Bit 18] If the AM bit is set in the CR0 register, alignment checking of user-mode data accesses is enabled if and only
     * if this flag is 1. If the SMAP bit is set in the CR4 register, explicit supervisor-mode data accesses to user-mode pages
     * are allowed if and only if this bit is 1.
     *
     * @see Vol3A[4.6(ACCESS RIGHTS)]
     */
    UINT32 AlignmentCheckFlag                                      : 1;
#define EFLAGS_ALIGNMENT_CHECK_FLAG_BIT                              18
#define EFLAGS_ALIGNMENT_CHECK_FLAG_MASK                             0x01
#define EFLAGS_ALIGNMENT_CHECK_FLAG(_)                               (((_) >> 18) & 0x01)

    /**
     * @brief Virtual interrupt flag
     *
     * [Bit 19] Virtual image of the IF flag. Used in conjunction with the VIP flag. (To use this flag and the VIP flag the
     * virtual mode extensions are enabled by setting the VME flag in control register CR4.)
     */
    UINT32 VirtualInterruptFlag                                    : 1;
#define EFLAGS_VIRTUAL_INTERRUPT_FLAG_BIT                            19
#define EFLAGS_VIRTUAL_INTERRUPT_FLAG_MASK                           0x01
#define EFLAGS_VIRTUAL_INTERRUPT_FLAG(_)                             (((_) >> 19) & 0x01)

    /**
     * @brief Virtual interrupt pending flag
     *
     * [Bit 20] Set to indicate that an interrupt is pending; clear when no interrupt is pending. (Software sets and clears
     * this flag; the processor only reads it.) Used in conjunction with the VIF flag.
     */
    UINT32 VirtualInterruptPendingFlag                             : 1;
#define EFLAGS_VIRTUAL_INTERRUPT_PENDING_FLAG_BIT                    20
#define EFLAGS_VIRTUAL_INTERRUPT_PENDING_FLAG_MASK                   0x01
#define EFLAGS_VIRTUAL_INTERRUPT_PENDING_FLAG(_)                     (((_) >> 20) & 0x01)

    /**
     * @brief Identification flag
     *
     * [Bit 21] The ability of a program to set or clear this flag indicates support for the CPUID instruction.
     */
    UINT32 IdentificationFlag                                      : 1;
#define EFLAGS_IDENTIFICATION_FLAG_BIT                               21
#define EFLAGS_IDENTIFICATION_FLAG_MASK                              0x01
#define EFLAGS_IDENTIFICATION_FLAG(_)                                (((_) >> 21) & 0x01)
    UINT32 Reserved4                                               : 10;
  };

  UINT32 Flags;
} EFLAGS;

/**
 * @defgroup MEMORY_TYPE \
 *           Memory caching type
 *
 * The processor allows any area of system memory to be cached in the L1, L2, and L3 caches. In individual pages or regions
 * of system memory, it allows the type of caching (also called memory type) to be specified.
 *
 * @see Vol3A[11.11(MEMORY TYPE RANGE REGISTERS (MTRRS))]
 * @see Vol3A[11.5(CACHE CONTROL)]
 * @see Vol3A[11.3(METHODS OF CACHING AVAILABLE)] (reference)
 * @{
 */
/**
 * @brief Strong Uncacheable (UC)
 *
 * System memory locations are not cached. All reads and writes appear on the system bus and are executed in program order
 * without reordering. No speculative memory accesses, pagetable walks, or prefetches of speculated branch targets are
 * made. This type of cache-control is useful for memory-mapped I/O devices. When used with normal RAM, it greatly reduces
 * processor performance.
 */
#define MEMORY_TYPE_UNCACHEABLE                                      0x00000000

/**
 * @brief Write Combining (WC)
 *
 * System memory locations are not cached (as with uncacheable memory) and coherency is not enforced by the processor's bus
 * coherency protocol. Speculative reads are allowed. Writes may be delayed and combined in the write combining buffer (WC
 * buffer) to reduce memory accesses. If the WC buffer is partially filled, the writes may be delayed until the next
 * occurrence of a serializing event; such as, an SFENCE or MFENCE instruction, CPUID execution, a read or write to
 * uncached memory, an interrupt occurrence, or a LOCK instruction execution. This type of cache-control is appropriate for
 * video frame buffers, where the order of writes is unimportant as long as the writes update memory so they can be seen on
 * the graphics display. This memory type is available in the Pentium Pro and Pentium II processors by programming the
 * MTRRs; or in processor families starting from the Pentium III processors by programming the MTRRs or by selecting it
 * through the PAT.
 *
 * @see Vol3A[11.3.1(Buffering of Write Combining Memory Locations)]
 */
#define MEMORY_TYPE_WRITE_COMBINING                                  0x00000001

/**
 * @brief Write-through (WT)
 *
 * Writes and reads to and from system memory are cached. Reads come from cache lines on cache hits; read misses cause
 * cache fills. Speculative reads are allowed. All writes are written to a cache line (when possible) and through to system
 * memory. When writing through to memory, invalid cache lines are never filled, and valid cache lines are either filled or
 * invalidated. Write combining is allowed. This type of cache-control is appropriate for frame buffers or when there are
 * devices on the system bus that access system memory, but do not perform snooping of memory accesses. It enforces
 * coherency between caches in the processors and system memory.
 */
#define MEMORY_TYPE_WRITE_THROUGH                                    0x00000004

#define MEMORY_TYPE_WRITE_PROTECTED                                  0x00000005
/**
 * @brief Write protected (WP)
 *
 * Reads come from cache lines when possible, and read misses cause cache fills. Writes are propagated to the system bus
 * and cause corresponding cache lines on all processors on the bus to be invalidated. Speculative reads are allowed. This
 * memory type is available in processor families starting from the P6 family processors by programming the MTRRs.
 */
#define MEMORY_TYPE_WRITE_BACK                                       0x00000006

#define MEMORY_TYPE_UNCACHED                                         0x00000007
#define MEMORY_TYPE_INVALID                                          0x000000FF
/**
 * @}
 */

/**
 * @}
 */


