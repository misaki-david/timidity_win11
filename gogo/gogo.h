/* -*- TABSIZE = 4 -*- */
/*
 *	for GOGO-no-coda
 *	Copyright (C) 1999, 2000, 2001 gogo develop team
 */


#ifndef GOGO_H_
#define GOGO_H_

typedef int MERET;

/* for only compatibility */
#define MUPARAM UPARAM

typedef	unsigned long			UPARAM;

#define	ME_NOERR					(0)		// return normally;����I��
#define	ME_EMPTYSTREAM				(1)		// stream becomes empty;�X�g���[�����Ō�ɒB����
#define	ME_HALTED					(2)		// stopped by user;(���[�U�[�̎�ɂ��)���f���ꂽ
#define	ME_MOREDATA					(3)	
#define	ME_INTERNALERROR			(10)	// internal error; �����G���[
#define	ME_PARAMERROR				(11)	// parameters error;�ݒ�Ńp�����[�^�[�G���[
#define	ME_NOFPU					(12)	// no FPU;FPU�𑕒����Ă��Ȃ�!!
#define	ME_INFILE_NOFOUND			(13)	// can't open input file;���̓t�@�C���𐳂����J���Ȃ�
#define	ME_OUTFILE_NOFOUND			(14)	// can't open output file;�o�̓t�@�C���𐳂����J���Ȃ�
#define	ME_FREQERROR				(15)	// frequency is not good;���o�͎��g�����������Ȃ�
#define	ME_BITRATEERROR				(16)	// bitrate is not good;�o�̓r�b�g���[�g���������Ȃ�
#define	ME_WAVETYPE_ERR				(17)	// WAV format is not good;�E�F�[�u�^�C�v���������Ȃ�
#define	ME_CANNOT_SEEK				(18)	// can't seek;�������V�[�N�o���Ȃ�
#define	ME_BITRATE_ERR				(19)	// only for compatibility;�r�b�g���[�g�ݒ肪�������Ȃ�
#define	ME_BADMODEORLAYER			(20)	// mode/layer not good;���[�h�E���C���̐ݒ�ُ�
#define	ME_NOMEMORY					(21)	// fail to allocate memory;�������A���[�P�[�V�������s
#define	ME_CANNOT_SET_SCOPE			(22)	// thread error;�X���b�h�����G���[(pthread only)
#define	ME_CANNOT_CREATE_THREAD		(23)	// fail to create thear;�X���b�h�����G���[
#define	ME_WRITEERROR				(24)	// lock of capacity of disk;�L���}�̗̂e�ʕs��


// definition of call-back function for user;���[�U�[�̃R�[���o�b�N�֐���`
typedef	MERET	(*MPGE_USERFUNC)(void *buf, unsigned long nLength );
#define MPGE_NULL_FUNC (MPGE_USERFUNC)NULL

///////////////////////////////////////////////////////////////////////////
// Configuration
///////////////////////////////////////////////////////////////////////////
// for INPUT
#define		MC_INPUTFILE			(1)
	// para1 choice of input device
	#define		MC_INPDEV_FILE		(0)	// input device is file;���̓f�o�C�X�̓t�@�C��
	#define		MC_INPDEV_STDIO		(1)	//                 stdin;���̓f�o�C�X�͕W������
	#define		MC_INPDEV_USERFUNC	(2)	//       defined by user;���̓f�o�C�X�̓��[�U�[��`
	#define		MC_INPDEV_LIBSND	(3) // input device is file via LIBSND ;���̓f�o�C�X�� LIBSND �o�R�Ńt�@�C��
	// para2 (�K�v�ł����)�t�@�C�����B�|�C���^���w�肷��
	// ���������G���R�[�h�̎��͈ȉ��̍\���̂̃|�C���^���w�肷��.
	struct MCP_INPDEV_USERFUNC {
		MPGE_USERFUNC	pUserFunc;		// pointer to user-function for call-back or MPGE_NULL_FUNC if none
											// �R�[���o�b�N�Ώۂ̃��[�U�[�֐��B����`��MPGE_NULL_FUNC����
		unsigned int	nSize;			// size of file or MC_INPDEV_MEMORY_NOSIZE if unknown
											// �t�@�C���T�C�Y�B�s��̎��� MC_INPDEV_MEMORY_NOSIZE���w��
		int				nBit;	// nBit = 8 or 16 ; PCM�r�b�g�[�x���w��
		int				nFreq;	// input frequency ; ���͎��g���̎w��
		int				nChn;	// number of channel(1 or 2) ; �`���l����
	};
	#define		MC_INPDEV_MEMORY_NOSIZE		(0xffffffff)
/*
  Using userfunction input;
  ���[�U�[�֐����p���̋���
  ^^^^^^^^^^^^^^^^^^^^^^^^

  ���[�U�[���o�^�����֐� UsefFunc�ɑ΂��āADLL���ǂݍ��ݗv�����s����B
  MERET	UserFunc_input(void *buf, unsigned long nLength );

  �v������������ۂ�
     �Evoid *buf �ɂ� nLength �o�C�g���̃f�[�^���i�[�A return ME_NOERR�Ŕ�����
	 �E�t�@�C���̍Ō�ɒB���āAnLength���ǂݍ��߂Ȃ�(�����Ȃ��Ƃ�1�o�C�g�ȏ�ǂݍ��߂�)�ꍇ�A
	    memset( buf + �ǂݍ��񂾃f�[�^byte, 0, nLength - �ǂݍ��񂾃f�[�^�T�C�Y) ;
	   �Ƃ��� return ME_NOERR ����B
	 �E�P�o�C�g���ǂ߂Ȃ��ꍇ�́A�������� return ME_EMPTYSTREAM; �Ŕ�����
*/

///////////////////////////////////////////////////////////////////////////
// for OUTPUT ( now stdout is not support )
#define		MC_OUTPUTFILE			(2)
// para1 choice of output device
	#define		MC_OUTDEV_FILE		(0)	// output device is file;�o�̓f�o�C�X�̓t�@�C��
	#define		MC_OUTDEV_STDOUT	(1)	//                  stdout; �o�̓f�o�C�X�͕W���o��
	#define		MC_OUTDEV_USERFUNC	(2)	//        defined by user;�o�̓f�o�C�X�̓��[�U�[��`
	#define		MC_OUTDEV_USERFUNC_WITHVBRTAG	(3)	//       defined by user;���̓f�o�C�X�̓��[�U�[��`/VBR�^�O�����o��
// para2 pointer to file if necessary ;(�K�v�ł����)�t�@�C�����B�|�C���^�w��

/*
  Using userfunction output
  ���[�U�[�֐����p���̋���
  ^^^^^^^^^^^^^^^^^^^^^^^^

  ���[�U�[���o�^�����֐� UsefFunc�ɑ΂��āADLL��菑���ݗv�����s����B
  MERET	UserFunc_output(void *buf, unsigned long nLength );

  �v������������ۂ�
     �Evoid *buf �ɂ� nLength �o�C�g���̃f�[�^���i�[����Ă���̂� 
	   fwrite( buf, 1, nLength, fp );�̗l�ɂ��ď����o��return ME_NOERR�Ŕ�����.
	   �����o���Ɏ��s�������́Areturn ME_WRITEERROR;�Ŕ�����.
  �G���R�[�h�I���̒ʒm/������MC_OUTDEV_USERFUNC��MC_OUTDEV_USERFUNC_WITHVBRTAG�ňقȂ�
	(MC_OUTDEV_USERFUNC�̏ꍇ)
	 �E�Ō�� buf == NULL��1�x�Ăяo�����. return �l�͉��ł��ǂ��B
	(MC_OUTDEV_USERFUNC_WITHVBRTAG�̏ꍇ)
	 �Ebuf == NULL�ŌĂяo�����.���̍ۂɃt�@�C���̐擪�փV�[�N���A
	   �t�@�C���S�̂̃T�C�Y�� return�̒l�Ƃ���Bfilesize<=0�̎��͏I���B
	   (����� return ME_NOERR; �Ŕ����Ȃ��l�ɒ���!! )
	 �EXING-VBR�^�O�f�[�^�� buf�ɁAXINGVBR�^�O�̃T�C�Y�� nLength�Ɋi�[����ČĂяo�����̂�
	   �t�@�C���擪���炻�����������.
	 �E�Ō�ɂ�����xbuf == NULL�ŌĂяo�����. return �l�͉��ł��ǂ��B
*/

///////////////////////////////////////////////////////////////////////////
// mode of encoding ;�G���R�[�h�^�C�v
#define		MC_ENCODEMODE			(3)
// para1 mode;���[�h�ݒ�
	#define		MC_MODE_MONO		(0)		// mono;���m����
	#define		MC_MODE_STEREO		(1)		// stereo;�X�e���I
	#define		MC_MODE_JOINT		(2)		// joint-stereo;�W���C���g
	#define		MC_MODE_MSSTEREO	(3)		// mid/side stereo;�~�b�h�T�C�h
	#define		MC_MODE_DUALCHANNEL	(4)		// dual channel;�f���A���`���l��

///////////////////////////////////////////////////////////////////////////
// bitrate;�r�b�g���[�g�ݒ�
#define		MC_BITRATE				(4)
// para1 bitrate;�r�b�g���[�g ���l�w��


///////////////////////////////////////////////////////////////////////////
// frequency of input file (force);���͂ŗp����T���v�����g���̋����w��
#define		MC_INPFREQ				(5)
// para1 frequency;���o�͂ŗp����f�[�^

///////////////////////////////////////////////////////////////////////////
// frequency of output mp3 (force);�o�͂ŗp����T���v�����g���̋����w��
#define		MC_OUTFREQ				(6)
// para1 frequency;���o�͂ŗp����f�[�^

///////////////////////////////////////////////////////////////////////////
// size ofheader if you ignore WAV-header (for example cda);�G���R�[�h�J�n�ʒu�̋����w��(�w�b�_�𖳎����鎞)
#define		MC_STARTOFFSET			(7)

///////////////////////////////////////////////////////////////////////////
// psycho-acoustics ON/OFF;�S����� ON/OFF
#define		MC_USEPSY				(8)
// PARA1 boolean(TRUE/FALSE)

///////////////////////////////////////////////////////////////////////////
// 16kHz low-pass filter ON/OFF;16KHz��ш�t�B���^ ON/OFF
#define		MC_USELPF16				(9)
// PARA1 boolean(TRUE/FALSE)

///////////////////////////////////////////////////////////////////////////
// use special UNIT, para1:boolean; ���j�b�g�w�� para1:BOOL�l
#define		MC_USEMMX				(10)	// MMX
#define		MC_USE3DNOW				(11)	// 3DNow!
#define		MC_USESSE				(12)	// SSE(KNI)
#define		MC_USEKNI				MC_USESSE	// �ߌ�2�Ƃ̌݊���
#define		MC_USEE3DNOW			(13)	// Enhanced 3D Now!
#define		MC_USECMOV				(38)	// CMOV
#define		MC_USEEMMX				(39)	// EMMX
#define		MC_USESSE2				(40)	// SSE2
/* #define 	MC_USECLFLUSH				(43)	// CLFLUSH */
#define 	MC_USEALTIVEC				(44)	// ALTIVEC
#define		MC_USESPC1				(14)	// special switch for debug
#define		MC_USESPC2				(15)	// special switch for debug

///////////////////////////////////////////////////////////////////////////
// addition of TAG; �t�@�C���^�O���t��
#define		MC_ADDTAG				(16)
// dwPara1  length of TAG;�^�O��  
// dwPara2  pointer to TAG;�^�O�f�[�^�̃|�C���^

///////////////////////////////////////////////////////////////////////////
// emphasis;�G���t�@�V�X�^�C�v�̐ݒ�
#define		MC_EMPHASIS				(17)	
// para1 type of emphasis;�G���t�@�V�X�^�C�v�̐ݒ�
	#define		MC_EMP_NONE			(0)		// no empahsis;�G���t�@�V�X�Ȃ�(dflt)
	#define		MC_EMP_5015MS		(1)		// 50/15ms    ;�G���t�@�V�X50/15ms
	#define		MC_EMP_CCITT		(3)		// CCITT      ;�G���t�@�V�XCCITT

///////////////////////////////////////////////////////////////////////////
// use VBR;VBR�^�C�v�̐ݒ�
#define		MC_VBR					(18)

///////////////////////////////////////////////////////////////////////////
// SMP support para1: interger
#define		MC_CPU					(19)

///////////////////////////////////////////////////////////////////////////
// for RAW-PCM; �ȉ�4��RAW-PCM�̐ݒ�̂���
// byte swapping for 16bitPCM; PCM���͎���low, high bit �ϊ�
#define		MC_BYTE_SWAP			(20)

///////////////////////////////////////////////////////////////////////////
// for 8bit PCM
#define		MC_8BIT_PCM				(21)

///////////////////////////////////////////////////////////////////////////
// for mono PCM
#define		MC_MONO_PCM				(22)

///////////////////////////////////////////////////////////////////////////
// for Towns SND
#define		MC_TOWNS_SND			(23)

///////////////////////////////////////////////////////////////////////////
// BeOS & Win32 Encode thread priority
#define		MC_THREAD_PRIORITY		(24)
// (WIN32) dwPara1 MULTITHREAD Priority (THREAD_PRIORITY_**** at WinBASE.h )

///////////////////////////////////////////////////////////////////////////
// BeOS Read thread priority
//#if	defined(USE_BTHREAD)
#define		MC_READTHREAD_PRIORITY	(25)
//#endif

///////////////////////////////////////////////////////////////////////////
// output format 
#define		MC_OUTPUT_FORMAT		(26)
// para1 
	#define		MC_OUTPUT_NORMAL	(0)		// mp3+TAG(see MC_ADDTAG)
	#define		MC_OUTPUT_RIFF_WAVE	(1)		// RIFF/WAVE
	#define		MC_OUTPUT_RIFF_RMP	(2)		// RIFF/RMP

///////////////////////////////////////////////////////////////////////////
// LIST/INFO chunk of RIFF/WAVE or RIFF/RMP 
#define		MC_RIFF_INFO			(27)
// para1 size of info(include info name)
// para2 pointer to info
//   byte offset       contents
//   0..3              info name
//   4..size of info-1 info

///////////////////////////////////////////////////////////////////////////
// verify and overwrite
#define		MC_VERIFY				(28)

///////////////////////////////////////////////////////////////////////////
// output directory
#define		MC_OUTPUTDIR			(29)

///////////////////////////////////////////////////////////////////////////
// VBR�̍Œ�/�ō��r�b�g���[�g�̐ݒ�
#define		MC_VBRBITRATE			(30)
// para1 �Œ�r�b�g���[�g (kbps)
// para2 �ō��r�b�g���[�g (kbps)


///////////////////////////////////////////////////////////////////////////
// �g���t�B���^�̎g�p LPF1, LPF2
#define		MC_ENHANCEDFILTER		(31)
// para1 LPF1 (0-100)	, dflt=auto setting by outfreq
// para2 LPF2 (0-100)	, dflt=auto setting by outfreq


///////////////////////////////////////////////////////////////////////////
// Joint-stereo�ɂ�����A�X�e���I/MS�X�e���I�̐؂�ւ���臒l
#define		MC_MSTHRESHOLD	 		(32)
// para1 threshold  (0-100)	, dflt=auto setting by outfreq
// para2 mspower    (0-100) , dflt=auto setting by outfreq

///////////////////////////////////////////////////////////////////////////
// Language
#define		MC_LANG					(33)
// t_lang defined in message.h

///////////////////////////////////////////////////////////////////////////
// �ǂݍ��݃f�[�^�̍ő�T�C�Y�ݒ� / max data length ( byte )
#define		MC_MAXFILELENGTH		(34)
// para1 maxfilesize (PCM body length, not include wave heaher size.)
//       (0-0xfffffffd)		// as byte
		#define		MC_MAXFLEN_IGNORE		(ULONG_MAX)		// DEFAULT
		#define		MC_MAXFLEN_WAVEHEADER	(ULONG_MAX-1)	// WAVE�w�b�_�̒l���g�p


///////////////////////////////////////////////////////////////////////////
// �o�̓X�g���[���̃o�b�t�@�����O�t���O
#define		MC_OUTSTREAM_BUFFERD	(35)
// para1  enable(=1) or disable(=0), dflt=enable
		#define		MC_OBUFFER_ENABLE		1				// DEFAULT
		#define		MC_OBUFFER_DISABLE		0

// �ȉ��͂Ղ��ߌ�V��

///////////////////////////////////////////////////////////////////////////
// quality (same as lame-option `-q')
#define		MC_ENCODE_QUALITY		(36)
// 1(high quality) <= para1 <= 9(low quality)
// 2:-h
// 5:default
// 7:-f



///////////////////////////////////////////////////////////////////////////
// use ABR;ABR�^�C�v�̐ݒ�
#define		MC_ABR					(37)

///////////////////////////////////////////////////////////////////////////
// ���݂��ꂽCPU�^�C�v�̐ݒ�
// defined in `use special UNIT'
//#define		MC_USECMOV				(38)	// CMOV ��Œ�`�ς�
//#define		MC_USEEMMX				(39)	// EMMX ��Œ�`�ς�
//#define		MC_USESSE2				(40)	// SSE2 ��Œ�`�ς�

///////////////////////////////////////////////////////////////////////////
// LAME�^�O�̏o�͐ݒ� (������VBR�^�O�̏����o����L���ɂ��Ă�������)
#define		MC_WRITELAMETAG					(41)
/// para1: 0 = disable (default)
///        1 = enable

///////////////////////////////////////////////////////////////////////////
// VBR�^�O�̏o�͐ݒ� (CBR�łȂ�����lametag�������͐ݒ���e�Ɋ֌W�Ȃ������ł�)
#define		MC_WRITEVBRTAG					(42)
/// para1: 0 = disable 
///        1 = enable (default)


///////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////
#ifdef GOGO_DLL_EXPORTS
#define		EXPORT				__declspec(dllexport) __cdecl	
#define		EXPORT_VB			__declspec(dllexport) __stdcall	
#else
#define		EXPORT
#define		EXPORT_VB
#endif

MERET	EXPORT	MPGE_initializeWork(void);
MERET	EXPORT	MPGE_setConfigure(UPARAM mode, UPARAM dwPara1, UPARAM dwPara2);
MERET	EXPORT	MPGE_getConfigure(UPARAM mode, void *para1);
MERET	EXPORT	MPGE_detectConfigure(void);
MERET	EXPORT	MPGE_processFrame(void);
MERET	EXPORT	MPGE_closeCoder(void);
MERET	EXPORT	MPGE_endCoder(void);
MERET	EXPORT	MPGE_getUnitStates( unsigned long *unit );
MERET	EXPORT	MPGE_processTrack(void);

// This function is effective for gogo.dll;���̃t�@���N�V������DLL�o�[�W�����̂ݗL��
MERET	EXPORT	MPGE_getVersion( unsigned long *vercode,  char *verstring );
#define MGV_BUFLENGTH 260
// vercode = 0x125 ->  version 1.25
// verstring       ->  "ver 1.25 1999/09/25" (allocate abobe 260bytes buffer)


////////////////////////////////////////////////////////////////////////////
// for getting configuration
////////////////////////////////////////////////////////////////////////////

#define		MG_INPUTFILE			(1)		// name of input file ;���̓t�@�C�����擾
#define		MG_OUTPUTFILE			(2)		// name of output file;�o�̓t�@�C�����擾
#define		MG_ENCODEMODE			(3)		// type of encoding   ;�G���R�[�h���[�h
#define		MG_BITRATE				(4)		// bitrate            ;�r�b�g���[�g
#define		MG_INPFREQ				(5)		// input frequency    ;���͎��g��
#define		MG_OUTFREQ				(6)		// output frequency   ;�o�͎��g��
#define		MG_STARTOFFSET			(7)		// offset of input PCM;�X�^�[�g�I�t�Z�b�g
#define		MG_USEPSY				(8)		// psycho-acoustics   ;�S����͂��g�p����/���Ȃ�
#define		MG_USEMMX				(9)		// MMX
#define		MG_USE3DNOW				(10)	// 3DNow!
#define		MG_USESSE				(11)	// SSE(KNI)
#define		MG_USEKNI				MG_USESSE	// �ߌ�2�Ƃ̌݊���
#define		MG_USEE3DNOW			(12)	// Enhanced 3DNow!
#define		MG_USECMOV				(20)	// CMOV
#define		MG_USEEMMX				(21)	// EMMX
#define		MG_USESSE2				(22)	// SSE2
#define 	MG_CLFLUSH				(23)	// CLFLUSH
#define 	MG_USEALTIVEC				(24)	// ALTIVEC
#define		MG_USESPC1				(13)	// special switch for debug
#define		MG_USESPC2				(14)	// special switch for debug
#define		MG_COUNT_FRAME			(15)	// amount of frame
#define		MG_NUM_OF_SAMPLES		(16)	// number of sample for 1 frame;1�t���[��������̃T���v����
#define		MG_MPEG_VERSION			(17)	// MPEG VERSION
#define		MG_READTHREAD_PRIORITY	(18)	// thread priority to read for BeOS
#define		MG_FRAME				(19)	// frame number
//#define		MG_USECMOV				(20)	// CMOV ��Œ�`�ς�
//#define		MG_USEEMMX				(21)	// EMMX ��Œ�`�ς�
//#define		MG_USESSE2				(22)	// SSE2 ��Œ�`�ς�



////////////////////////////////////////////////////////////////////////////
//  for MPGE_getUnitStates()
////////////////////////////////////////////////////////////////////////////
// x86 - Spec
#define		MU_tFPU					(1<<0)
#define		MU_tMMX					(1<<1)
#define		MU_t3DN					(1<<2)
#define		MU_tSSE					(1<<3)
#define		MU_tCMOV				(1<<4)
#define		MU_tE3DN				(1<<5)	/* for Athlon(Externd 3D Now!) */
#define 	MU_tEMMX				(1<<6)  /* EMMX = E3DNow!_INT = SSE_INT  */
#define		MU_tSSE2				(1<<7)
#define 	MU_tCLFLUSH				(1<<18)
#define 	MU_tMULTI				(1<<12)	/* for Multi-threaded encoder. Never set on UP or in the binary linked w/o multithread lib. */

// x86 - Vendor
#define 	MU_tINTEL				(1<<8)
#define 	MU_tAMD					(1<<9)
#define 	MU_tCYRIX				(1<<10)
#define 	MU_tIDT					(1<<11)
#define 	MU_tUNKNOWN				(1<<15)	/* unknown vendor */

// x86 - Special
#define 	MU_tSPC1 				(1<<16)	/* special flag */
#define 	MU_tSPC2 				(1<<17)	/* freely available */
// x86 - CPU TYPES
#define 	MU_tFAMILY4				(1<<20)	/* 486 vendor maybe isn't correct */
#define 	MU_tFAMILY5				(1<<21)	/* 586 (P5, P5-MMX, K6, K6-2, K6-III) */
#define 	MU_tFAMILY6				(1<<22)	/* 686 above P-Pro, P-II, P-III, Athlon */
#define 	MU_tFAMILY7				(1<<23) /* Pentium IV ? */

// for PPC arc
#define 	MU_tPPC					(1<<0)
#define 	MU_tGRAP				(1<<1)	/* fres, frsqrte, fsel */
#define 	MU_tFSQRT				(1<<2)	/* fsqrt, fsqrts */
#define 	MU_tALTIVEC				(1<<3)	/* AltiVec */


#endif /* GOGO_H_ */
