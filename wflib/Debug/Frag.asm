	TITLE	C:\develop3\wavfrag\work\wflib\Frag.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
$$SYMBOLS	SEGMENT BYTE USE32 'DEBSYM'
$$SYMBOLS	ENDS
$$TYPES	SEGMENT BYTE USE32 'DEBTYP'
$$TYPES	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT ??_C@_0BB@NAAD@Magellan?5MSWHEEL?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_06FPAF@MouseZ?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0BA@CLBL@MSWHEEL_ROLLMSG?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0BF@DLPD@MSH_WHEELSUPPORT_MSG?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0BF@ODOJ@MSH_SCROLL_LINES_MSG?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0EE@LGAC@c?3?2program?5files?2microsoft?5visua@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CC@BBMP@c?3?2develop3?2common?2work?2xptrarr?4@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_04FCPF@?4wfa?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_04MPDF@?4wav?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?__LINE__Var@?1???1CFrag@@UAE@XZ@4FA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BG@FFGF@Cannot?5load?5Wave?5?$CFs?$AN?6?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CI@DEPE@Cannot?5create?5?1?5open?5frag?5file?5f@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0M@BDNF@1234567890?9?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0BG@HLAC@Cannot?5load?5file?5?$CFs?$AN?6?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CE@LGCK@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIstart@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CC@KACJ@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIend?$CJ?$AN@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CF@FNN@CFrag?3?3LoadFrag?5empty?5buffer?5on?5@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?__LINE__Var@?1??LoadFrag@CFrag@@QAEHPBDH@Z@4FA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0EE@EEFC@c?3?2program?5files?2microsoft?5visua@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
CRT$XCA	SEGMENT DWORD USE32 PUBLIC 'DATA'
CRT$XCA	ENDS
CRT$XCU	SEGMENT DWORD USE32 PUBLIC 'DATA'
CRT$XCU	ENDS
CRT$XCL	SEGMENT DWORD USE32 PUBLIC 'DATA'
CRT$XCL	ENDS
CRT$XCC	SEGMENT DWORD USE32 PUBLIC 'DATA'
CRT$XCC	ENDS
CRT$XCZ	SEGMENT DWORD USE32 PUBLIC 'DATA'
CRT$XCZ	ENDS
;	COMDAT ?GetSize@CIntArr@@QBEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CIntArr@@QBEHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CIntArr@@QAEAAHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetData@CIntArr@@QAEPAHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Add@CIntArr@@QAEHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSize@CArrIntArr@@QAEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CxPtrArr@@QBEPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CxPtrArr@@QAEAAPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E306
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E307
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E309
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E310
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E312
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E313
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E314
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _$E315
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CFrag@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCFrag@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFrag@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCString@@QAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ParseFragWav@CFrag@@SAHPBD0H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?LoadFrag@CFrag@@QAEHPBDH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?xHitPow@CFrag@@IAEHPAVCAnalRes@@HHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@ABV0@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@PAUIUnknown@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@PAUIUnknown@@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@ABU_GUID@@K@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@PAGK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEAAV0@PAUIUnknown@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEAAV0@ABV0@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEAAV0@ABU_GUID@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEAAV0@PAG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetInterfacePtr@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QBEPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?CreateObject@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEJABU_GUID@@K@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?CreateObject@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAEJPAGK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_AddRef@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@AAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetIID@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@SAABU_GUID@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_Release@?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@AAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$_CIP@UIUnknown@@$1?IID_IUnknown@@3U_GUID@@B@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCNoTrackObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CNoTrackObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CNoTrackObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CFrag@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
FLAT	GROUP _DATA, CONST, _BSS, CRT$XCA, CRT$XCU, CRT$XCL, CRT$XCC, CRT$XCZ
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	?onefraglen@CFrag@@2HA				; CFrag::onefraglen
PUBLIC	?wavext@CFrag@@2VCString@@A			; CFrag::wavext
PUBLIC	?fragext@CFrag@@2VCString@@A			; CFrag::fragext
_BSS	SEGMENT
?wavext@CFrag@@2VCString@@A DD 01H DUP (?)		; CFrag::wavext
?fragext@CFrag@@2VCString@@A DD 01H DUP (?)		; CFrag::fragext
_BSS	ENDS
_DATA	SEGMENT
_THIS_FILE DB	'C:\develop3\wavfrag\work\wflib\Frag.cpp', 00H
_DATA	ENDS
CRT$XCU	SEGMENT
_$S311	DD	FLAT:_$E310
_$S316	DD	FLAT:_$E315
CRT$XCU	ENDS
_DATA	SEGMENT
?onefraglen@CFrag@@2HA DD 0200H				; CFrag::onefraglen
_DATA	ENDS
EXTRN	__chkesp:NEAR
;	COMDAT _$E310
_TEXT	SEGMENT
_$E310	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	call	_$E306
	call	_$E309
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E310	ENDP
_TEXT	ENDS
PUBLIC	??_C@_04FCPF@?4wfa?$AA@				; `string'
EXTRN	??0CString@@QAE@PBD@Z:NEAR			; CString::CString
;	COMDAT ??_C@_04FCPF@?4wfa?$AA@
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
CONST	SEGMENT
??_C@_04FCPF@?4wfa?$AA@ DB '.wfa', 00H			; `string'
CONST	ENDS
;	COMDAT _$E306
_TEXT	SEGMENT
_$E306	PROC NEAR					; COMDAT

; 39   : CString CFrag::fragext = ".wfa";

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	push	OFFSET FLAT:??_C@_04FCPF@?4wfa?$AA@	; `string'
	mov	ecx, OFFSET FLAT:?fragext@CFrag@@2VCString@@A ; CFrag::fragext
	call	??0CString@@QAE@PBD@Z			; CString::CString
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E306	ENDP
_TEXT	ENDS
EXTRN	_atexit:NEAR
;	COMDAT _$E309
_TEXT	SEGMENT
_$E309	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	push	OFFSET FLAT:_$E307
	call	_atexit
	add	esp, 4
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E309	ENDP
_TEXT	ENDS
EXTRN	??1CString@@QAE@XZ:NEAR				; CString::~CString
_BSS	SEGMENT
_$S308	DB	01H DUP (?)
_BSS	ENDS
;	COMDAT _$E307
_TEXT	SEGMENT
_$E307	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	xor	eax, eax
	mov	al, BYTE PTR _$S308
	and	eax, 1
	test	eax, eax
	jne	SHORT $L94586
	mov	cl, BYTE PTR _$S308
	or	cl, 1
	mov	BYTE PTR _$S308, cl
	mov	ecx, OFFSET FLAT:?fragext@CFrag@@2VCString@@A ; CFrag::fragext
	call	??1CString@@QAE@XZ			; CString::~CString
$L94586:
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E307	ENDP
_TEXT	ENDS
;	COMDAT _$E315
_TEXT	SEGMENT
_$E315	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	call	_$E312
	call	_$E314
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E315	ENDP
_TEXT	ENDS
PUBLIC	??_C@_04MPDF@?4wav?$AA@				; `string'
;	COMDAT ??_C@_04MPDF@?4wav?$AA@
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
CONST	SEGMENT
??_C@_04MPDF@?4wav?$AA@ DB '.wav', 00H			; `string'
CONST	ENDS
;	COMDAT _$E312
_TEXT	SEGMENT
_$E312	PROC NEAR					; COMDAT

; 40   : CString CFrag::wavext = ".wav";

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	push	OFFSET FLAT:??_C@_04MPDF@?4wav?$AA@	; `string'
	mov	ecx, OFFSET FLAT:?wavext@CFrag@@2VCString@@A ; CFrag::wavext
	call	??0CString@@QAE@PBD@Z			; CString::CString
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E312	ENDP
_TEXT	ENDS
;	COMDAT _$E314
_TEXT	SEGMENT
_$E314	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	push	OFFSET FLAT:_$E313
	call	_atexit
	add	esp, 4
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E314	ENDP
_TEXT	ENDS
;	COMDAT _$E313
_TEXT	SEGMENT
_$E313	PROC NEAR					; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-64]
	mov	ecx, 16					; 00000010H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	xor	eax, eax
	mov	al, BYTE PTR _$S308
	and	eax, 2
	test	eax, eax
	jne	SHORT $L94602
	mov	cl, BYTE PTR _$S308
	or	cl, 2
	mov	BYTE PTR _$S308, cl
	mov	ecx, OFFSET FLAT:?wavext@CFrag@@2VCString@@A ; CFrag::wavext
	call	??1CString@@QAE@XZ			; CString::~CString
$L94602:
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 64					; 00000040H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_$E313	ENDP
_TEXT	ENDS
PUBLIC	?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA		; `CFrag::CFrag'::`2'::__LINE__Var
PUBLIC	??0CFrag@@QAE@XZ				; CFrag::CFrag
PUBLIC	??_7CFrag@@6B@					; CFrag::`vftable'
PUBLIC	??_GCFrag@@UAEPAXI@Z				; CFrag::`scalar deleting destructor'
PUBLIC	??_ECFrag@@UAEPAXI@Z				; CFrag::`vector deleting destructor'
EXTRN	??0CAnalRes@@QAE@XZ:NEAR			; CAnalRes::CAnalRes
EXTRN	??1CAnalRes@@UAE@XZ:NEAR			; CAnalRes::~CAnalRes
EXTRN	__except_list:DWORD
EXTRN	___CxxFrameHandler:NEAR
EXTRN	??0CString@@QAE@XZ:NEAR				; CString::CString
EXTRN	??2@YAPAXIPBDH@Z:NEAR				; operator new
EXTRN	??3@YAXPAXPBDH@Z:NEAR				; operator delete
;	COMDAT ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
_DATA	SEGMENT
?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA DW 031H		; `CFrag::CFrag'::`2'::__LINE__Var
_DATA	ENDS
;	COMDAT ??_7CFrag@@6B@
CONST	SEGMENT
??_7CFrag@@6B@ DD FLAT:??_ECFrag@@UAEPAXI@Z		; CFrag::`vftable'
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__ehfuncinfo$??0CFrag@@QAE@XZ DD 019930520H
	DD	04H
	DD	FLAT:__unwindtable$??0CFrag@@QAE@XZ
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
__unwindtable$??0CFrag@@QAE@XZ DD 0ffffffffH
	DD	FLAT:__unwindfunclet$??0CFrag@@QAE@XZ$0
	DD	00H
	DD	FLAT:__unwindfunclet$??0CFrag@@QAE@XZ$1
	DD	00H
	DD	FLAT:__unwindfunclet$??0CFrag@@QAE@XZ$2
	DD	00H
	DD	FLAT:__unwindfunclet$??0CFrag@@QAE@XZ$3
xdata$x	ENDS
;	COMDAT ??0CFrag@@QAE@XZ
_TEXT	SEGMENT
_this$ = -16
$T95014 = -20
$T95015 = -24
$T95018 = -28
$T95019 = -32
$T95022 = -36
$T95023 = -40
__$EHRec$ = -12
??0CFrag@@QAE@XZ PROC NEAR				; CFrag::CFrag, COMDAT

; 49   : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$??0CFrag@@QAE@XZ
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 104				; 00000068H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-116]
	mov	ecx, 26					; 0000001aH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 28					; 0000001cH
	call	??0CAnalRes@@QAE@XZ			; CAnalRes::CAnalRes
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax], OFFSET FLAT:??_7CFrag@@6B@ ; CFrag::`vftable'

; 50   : 	magic = CFrag_Magic;

	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx+8], 14935269		; 00e3e4e5H

; 51   : 	
; 52   : 
; 53   : #ifdef _DEBUG
; 54   : 	verbose = 0;

	mov	edx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [edx+24], 0

; 55   : #endif
; 56   : 	
; 57   : 	//needsave =  0;
; 58   : 
; 59   : 	idx = -1;				// Default to an invalid value

	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+4], -1

; 60   : 
; 61   : 	name = new CString;	shortname = new CString; fname = new CString;

	movsx	ecx, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	ecx, 12					; 0000000cH
	push	ecx
	push	OFFSET FLAT:_THIS_FILE
	push	4
	call	??2@YAPAXIPBDH@Z			; operator new
	add	esp, 12					; 0000000cH
	mov	DWORD PTR $T95015[ebp], eax
	mov	BYTE PTR __$EHRec$[ebp+8], 1
	cmp	DWORD PTR $T95015[ebp], 0
	je	SHORT $L95016
	mov	ecx, DWORD PTR $T95015[ebp]
	call	??0CString@@QAE@XZ			; CString::CString
	mov	DWORD PTR -44+[ebp], eax
	jmp	SHORT $L95017
$L95016:
	mov	DWORD PTR -44+[ebp], 0
$L95017:
	mov	edx, DWORD PTR -44+[ebp]
	mov	DWORD PTR $T95014[ebp], edx
	mov	BYTE PTR __$EHRec$[ebp+8], 0
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR $T95014[ebp]
	mov	DWORD PTR [eax+12], ecx
	movsx	edx, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	edx, 12					; 0000000cH
	push	edx
	push	OFFSET FLAT:_THIS_FILE
	push	4
	call	??2@YAPAXIPBDH@Z			; operator new
	add	esp, 12					; 0000000cH
	mov	DWORD PTR $T95019[ebp], eax
	mov	BYTE PTR __$EHRec$[ebp+8], 2
	cmp	DWORD PTR $T95019[ebp], 0
	je	SHORT $L95020
	mov	ecx, DWORD PTR $T95019[ebp]
	call	??0CString@@QAE@XZ			; CString::CString
	mov	DWORD PTR -48+[ebp], eax
	jmp	SHORT $L95021
$L95020:
	mov	DWORD PTR -48+[ebp], 0
$L95021:
	mov	eax, DWORD PTR -48+[ebp]
	mov	DWORD PTR $T95018[ebp], eax
	mov	BYTE PTR __$EHRec$[ebp+8], 0
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR $T95018[ebp]
	mov	DWORD PTR [ecx+16], edx
	movsx	eax, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	eax, 12					; 0000000cH
	push	eax
	push	OFFSET FLAT:_THIS_FILE
	push	4
	call	??2@YAPAXIPBDH@Z			; operator new
	add	esp, 12					; 0000000cH
	mov	DWORD PTR $T95023[ebp], eax
	mov	BYTE PTR __$EHRec$[ebp+8], 3
	cmp	DWORD PTR $T95023[ebp], 0
	je	SHORT $L95024
	mov	ecx, DWORD PTR $T95023[ebp]
	call	??0CString@@QAE@XZ			; CString::CString
	mov	DWORD PTR -52+[ebp], eax
	jmp	SHORT $L95025
$L95024:
	mov	DWORD PTR -52+[ebp], 0
$L95025:
	mov	ecx, DWORD PTR -52+[ebp]
	mov	DWORD PTR $T95022[ebp], ecx
	mov	BYTE PTR __$EHRec$[ebp+8], 0
	mov	edx, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR $T95022[ebp]
	mov	DWORD PTR [edx+20], eax

; 62   : }

	mov	DWORD PTR __$EHRec$[ebp+8], -1
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:__except_list, ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 116				; 00000074H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$??0CFrag@@QAE@XZ$0:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 28					; 0000001cH
	call	??1CAnalRes@@UAE@XZ			; CAnalRes::~CAnalRes
	ret	0
__unwindfunclet$??0CFrag@@QAE@XZ$1:
	movsx	eax, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	eax, 12					; 0000000cH
	push	eax
	push	OFFSET FLAT:_THIS_FILE
	mov	ecx, DWORD PTR $T95015[ebp]
	push	ecx
	call	??3@YAXPAXPBDH@Z			; operator delete
	add	esp, 12					; 0000000cH
	ret	0
__unwindfunclet$??0CFrag@@QAE@XZ$2:
	movsx	eax, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	eax, 12					; 0000000cH
	push	eax
	push	OFFSET FLAT:_THIS_FILE
	mov	ecx, DWORD PTR $T95019[ebp]
	push	ecx
	call	??3@YAXPAXPBDH@Z			; operator delete
	add	esp, 12					; 0000000cH
	ret	0
__unwindfunclet$??0CFrag@@QAE@XZ$3:
	movsx	eax, WORD PTR ?__LINE__Var@?1???0CFrag@@QAE@XZ@4FA ; `CFrag::CFrag'::`2'::__LINE__Var
	add	eax, 12					; 0000000cH
	push	eax
	push	OFFSET FLAT:_THIS_FILE
	mov	ecx, DWORD PTR $T95023[ebp]
	push	ecx
	call	??3@YAXPAXPBDH@Z			; operator delete
	add	esp, 12					; 0000000cH
	ret	0
__ehhandler$??0CFrag@@QAE@XZ:
	mov	eax, OFFSET FLAT:__ehfuncinfo$??0CFrag@@QAE@XZ
	jmp	___CxxFrameHandler
text$x	ENDS
??0CFrag@@QAE@XZ ENDP					; CFrag::CFrag
PUBLIC	??1CFrag@@UAE@XZ				; CFrag::~CFrag
EXTRN	??3@YAXPAX@Z:NEAR				; operator delete
;	COMDAT ??_GCFrag@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
_this$ = -4
??_GCFrag@@UAEPAXI@Z PROC NEAR				; CFrag::`scalar deleting destructor', COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1CFrag@@UAE@XZ			; CFrag::~CFrag
	mov	eax, DWORD PTR ___flags$[ebp]
	and	eax, 1
	test	eax, eax
	je	SHORT $L94633
	mov	ecx, DWORD PTR _this$[ebp]
	push	ecx
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L94633:
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 68					; 00000044H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	4
??_GCFrag@@UAEPAXI@Z ENDP				; CFrag::`scalar deleting destructor'
_TEXT	ENDS
PUBLIC	??_GCString@@QAEPAXI@Z				; CString::`scalar deleting destructor'
PUBLIC	?__LINE__Var@?1???1CFrag@@UAE@XZ@4FA		; `CFrag::~CFrag'::`2'::__LINE__Var
EXTRN	?AfxAssertFailedLine@@YGHPBDH@Z:NEAR		; AfxAssertFailedLine
;	COMDAT ?__LINE__Var@?1???1CFrag@@UAE@XZ@4FA
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
_DATA	SEGMENT
?__LINE__Var@?1???1CFrag@@UAE@XZ@4FA DW 044H		; `CFrag::~CFrag'::`2'::__LINE__Var
_DATA	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__ehfuncinfo$??1CFrag@@UAE@XZ DD 019930520H
	DD	01H
	DD	FLAT:__unwindtable$??1CFrag@@UAE@XZ
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
__unwindtable$??1CFrag@@UAE@XZ DD 0ffffffffH
	DD	FLAT:__unwindfunclet$??1CFrag@@UAE@XZ$0
xdata$x	ENDS
;	COMDAT ??1CFrag@@UAE@XZ
_TEXT	SEGMENT
_this$ = -16
$T95044 = -20
$T95045 = -24
$T95048 = -28
$T95049 = -32
$T95052 = -36
$T95053 = -40
__$EHRec$ = -12
??1CFrag@@UAE@XZ PROC NEAR				; CFrag::~CFrag, COMDAT

; 68   : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$??1CFrag@@UAE@XZ
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 104				; 00000068H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-116]
	mov	ecx, 26					; 0000001aH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax], OFFSET FLAT:??_7CFrag@@6B@ ; CFrag::`vftable'
	mov	DWORD PTR __$EHRec$[ebp+8], 0
$L94638:

; 69   : 	ASSERT(magic == CFrag_Magic);

	mov	ecx, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [ecx+8], 14935269		; 00e3e4e5H
	je	SHORT $L94641
	movsx	edx, WORD PTR ?__LINE__Var@?1???1CFrag@@UAE@XZ@4FA ; `CFrag::~CFrag'::`2'::__LINE__Var
	add	edx, 1
	push	edx
	push	OFFSET FLAT:_THIS_FILE
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L94641
	int	3
$L94641:
	xor	eax, eax
	test	eax, eax
	jne	SHORT $L94638

; 70   : 
; 71   : 	delete name, delete shortname; delete fname;

	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+12]
	mov	DWORD PTR $T95045[ebp], edx
	mov	eax, DWORD PTR $T95045[ebp]
	mov	DWORD PTR $T95044[ebp], eax
	cmp	DWORD PTR $T95044[ebp], 0
	je	SHORT $L95046
	push	1
	mov	ecx, DWORD PTR $T95044[ebp]
	call	??_GCString@@QAEPAXI@Z			; CString::`scalar deleting destructor'
	mov	DWORD PTR -44+[ebp], eax
	jmp	SHORT $L95047
$L95046:
	mov	DWORD PTR -44+[ebp], 0
$L95047:
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+16]
	mov	DWORD PTR $T95049[ebp], edx
	mov	eax, DWORD PTR $T95049[ebp]
	mov	DWORD PTR $T95048[ebp], eax
	cmp	DWORD PTR $T95048[ebp], 0
	je	SHORT $L95050
	push	1
	mov	ecx, DWORD PTR $T95048[ebp]
	call	??_GCString@@QAEPAXI@Z			; CString::`scalar deleting destructor'
	mov	DWORD PTR -48+[ebp], eax
	jmp	SHORT $L95051
$L95050:
	mov	DWORD PTR -48+[ebp], 0
$L95051:
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+20]
	mov	DWORD PTR $T95053[ebp], edx
	mov	eax, DWORD PTR $T95053[ebp]
	mov	DWORD PTR $T95052[ebp], eax
	cmp	DWORD PTR $T95052[ebp], 0
	je	SHORT $L95054
	push	1
	mov	ecx, DWORD PTR $T95052[ebp]
	call	??_GCString@@QAEPAXI@Z			; CString::`scalar deleting destructor'
	mov	DWORD PTR -52+[ebp], eax
	jmp	SHORT $L95055
$L95054:
	mov	DWORD PTR -52+[ebp], 0
$L95055:

; 72   : }

	mov	DWORD PTR __$EHRec$[ebp+8], -1
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 28					; 0000001cH
	call	??1CAnalRes@@UAE@XZ			; CAnalRes::~CAnalRes
	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:__except_list, ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 116				; 00000074H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$??1CFrag@@UAE@XZ$0:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 28					; 0000001cH
	call	??1CAnalRes@@UAE@XZ			; CAnalRes::~CAnalRes
	ret	0
__ehhandler$??1CFrag@@UAE@XZ:
	mov	eax, OFFSET FLAT:__ehfuncinfo$??1CFrag@@UAE@XZ
	jmp	___CxxFrameHandler
text$x	ENDS
??1CFrag@@UAE@XZ ENDP					; CFrag::~CFrag
;	COMDAT ??_GCString@@QAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
_this$ = -4
??_GCString@@QAEPAXI@Z PROC NEAR			; CString::`scalar deleting destructor', COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	eax, DWORD PTR ___flags$[ebp]
	and	eax, 1
	test	eax, eax
	je	SHORT $L94651
	mov	ecx, DWORD PTR _this$[ebp]
	push	ecx
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L94651:
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 68					; 00000044H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	4
??_GCString@@QAEPAXI@Z ENDP				; CString::`scalar deleting destructor'
_TEXT	ENDS
PUBLIC	??_C@_0BG@FFGF@Cannot?5load?5Wave?5?$CFs?$AN?6?$AA@ ; `string'
PUBLIC	?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa ; `CFrag::ParseFragWav'::`2'::__LINE__Var
PUBLIC	??_C@_0CI@DEPE@Cannot?5create?5?1?5open?5frag?5file?5f@ ; `string'
PUBLIC	?ParseFragWav@CFrag@@SAHPBD0H@Z			; CFrag::ParseFragWav
EXTRN	?SplitWave@CDsp@@QAEXPAFH00H@Z:NEAR		; CDsp::SplitWave
EXTRN	?LoadWave@CDsp@@QAEHPBDPAPADPAHPAUtWAVEFORMATEX@@@Z:NEAR ; CDsp::LoadWave
EXTRN	?NormalizeWav@CDsp@@QAEXPADH0@Z:NEAR		; CDsp::NormalizeWav
EXTRN	?GetFilename@CSupport@@QAE?AVCString@@ABV2@@Z:NEAR ; CSupport::GetFilename
EXTRN	?dsp@@3VCDsp@@A:DWORD				; dsp
EXTRN	__imp___stat:NEAR
EXTRN	?support@@3VCSupport@@A:BYTE			; support
EXTRN	?ProcSpectra@CAnalProc@@QAEXPAVCAnalRes@@H@Z:NEAR ; CAnalProc::ProcSpectra
EXTRN	??0CIntArr@@QAE@XZ:NEAR				; CIntArr::CIntArr
EXTRN	??1CIntArr@@UAE@XZ:NEAR				; CIntArr::~CIntArr
EXTRN	?ScanSpectra@CxRecog@@QAEXPADHPAVCAnalRes@@@Z:NEAR ; CxRecog::ScanSpectra
EXTRN	__imp__free:NEAR
EXTRN	__imp__malloc:NEAR
EXTRN	?xdllrecog@@3VCxRecog@@A:BYTE			; xdllrecog
EXTRN	??0CFile@@QAE@XZ:NEAR				; CFile::CFile
EXTRN	?Open@CFile@@UAEHPBDIPAVCFileException@@@Z:NEAR	; CFile::Open
EXTRN	??0CPtrArray@@QAE@XZ:NEAR			; CPtrArray::CPtrArray
EXTRN	?Write@CFile@@UAEXPBXI@Z:NEAR			; CFile::Write
EXTRN	?ToFile@CAnalRes@@QAEHPAVCFile@@@Z:NEAR		; CAnalRes::ToFile
EXTRN	??1CFile@@UAE@XZ:NEAR				; CFile::~CFile
EXTRN	??1CPtrArray@@UAE@XZ:NEAR			; CPtrArray::~CPtrArray
EXTRN	_memset:NEAR
EXTRN	??BCString@@QBEPBDXZ:NEAR			; CString::operator char const *
EXTRN	??4CString@@QAEABV0@ABV0@@Z:NEAR		; CString::operator=
EXTRN	??YCString@@QAEABV0@ABV0@@Z:NEAR		; CString::operator+=
EXTRN	?aprintf@MxPad@@QAAHPBDZZ:NEAR			; MxPad::aprintf
EXTRN	?mxpad@@3VMxPad@@A:BYTE				; mxpad
;	COMDAT ?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
_DATA	SEGMENT
?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa DW 050H ; `CFrag::ParseFragWav'::`2'::__LINE__Var
_DATA	ENDS
;	COMDAT ??_C@_0BG@FFGF@Cannot?5load?5Wave?5?$CFs?$AN?6?$AA@
CONST	SEGMENT
??_C@_0BG@FFGF@Cannot?5load?5Wave?5?$CFs?$AN?6?$AA@ DB 'Cannot load Wave '
	DB	'%s', 0dH, 0aH, 00H				; `string'
CONST	ENDS
;	COMDAT ??_C@_0CI@DEPE@Cannot?5create?5?1?5open?5frag?5file?5f@
CONST	SEGMENT
??_C@_0CI@DEPE@Cannot?5create?5?1?5open?5frag?5file?5f@ DB 'Cannot create'
	DB	' / open frag file for %s', 0dH, 0aH, 00H	; `string'
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__ehfuncinfo$?ParseFragWav@CFrag@@SAHPBD0H@Z DD 019930520H
	DD	08H
	DD	FLAT:__unwindtable$?ParseFragWav@CFrag@@SAHPBD0H@Z
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
__unwindtable$?ParseFragWav@CFrag@@SAHPBD0H@Z DD 0ffffffffH
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$0
	DD	00H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$1
	DD	01H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$2
	DD	01H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$3
	DD	03H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$4
	DD	04H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$5
	DD	05H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$6
	DD	06H
	DD	FLAT:__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$7
xdata$x	ENDS
;	COMDAT ?ParseFragWav@CFrag@@SAHPBD0H@Z
_TEXT	SEGMENT
_pname$ = 8
_fdir$ = 12
_force$ = 16
_ret$ = -16
_buff4$ = -20
_wname$ = -24
_fragname$ = -28
_sbuff1$ = -64
_sbuff2$ = -100
_len2$94666 = -104
_len22$94667 = -108
_buff2$94668 = -112
_wfx$94669 = -132
_lptr$94674 = -136
_rptr$94681 = -140
_arr$94690 = -160
_arr2$94691 = -180
_sarr$94692 = -204
_buff3$94693 = -208
_res$94695 = -432
_fp$94696 = -448
_smagic$94700 = -452
$T95067 = -456
$T95068 = -460
$T95069 = -464
__$EHRec$ = -12
?ParseFragWav@CFrag@@SAHPBD0H@Z PROC NEAR		; CFrag::ParseFragWav, COMDAT

; 80   : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$?ParseFragWav@CFrag@@SAHPBD0H@Z
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 524				; 0000020cH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-536]
	mov	ecx, 131				; 00000083H
	mov	eax, -858993460				; ccccccccH
	rep stosd

; 81   : 	int ret = true;

	mov	DWORD PTR _ret$[ebp], 1

; 82   : 	char *buff4 = NULL;

	mov	DWORD PTR _buff4$[ebp], 0

; 83   : 
; 84   : 	//P2N("ParseFragWav pname='%s' fragdir='%s'\r\n", pname, fragdir);
; 85   : 
; 86   : 	CString wname = pname, fragname = fdir;

	mov	eax, DWORD PTR _pname$[ebp]
	push	eax
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??0CString@@QAE@PBD@Z			; CString::CString
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	mov	ecx, DWORD PTR _fdir$[ebp]
	push	ecx
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??0CString@@QAE@PBD@Z			; CString::CString
	mov	BYTE PTR __$EHRec$[ebp+8], 1

; 87   : 
; 88   : 	// Construct output name
; 89   : 	wname = support.GetFilename(wname);

	lea	edx, DWORD PTR _wname$[ebp]
	push	edx
	lea	eax, DWORD PTR $T95067[ebp]
	push	eax
	mov	ecx, OFFSET FLAT:?support@@3VCSupport@@A
	call	?GetFilename@CSupport@@QAE?AVCString@@ABV2@@Z ; CSupport::GetFilename
	mov	DWORD PTR -468+[ebp], eax
	mov	ecx, DWORD PTR -468+[ebp]
	mov	DWORD PTR -472+[ebp], ecx
	mov	BYTE PTR __$EHRec$[ebp+8], 2
	mov	edx, DWORD PTR -472+[ebp]
	push	edx
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	mov	BYTE PTR __$EHRec$[ebp+8], 1
	lea	ecx, DWORD PTR $T95067[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString

; 90   : 	wname  += CFrag::fragext;	fragname += wname;

	push	OFFSET FLAT:?fragext@CFrag@@2VCString@@A ; CFrag::fragext
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??YCString@@QAEABV0@ABV0@@Z		; CString::operator+=
	lea	eax, DWORD PTR _wname$[ebp]
	push	eax
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??YCString@@QAEABV0@ABV0@@Z		; CString::operator+=

; 91   : 
; 92   : 	//AP2N("ParseFragWav wname='%s'\r\n", wname);
; 93   : 	
; 94   : 	// See if wave is newer 
; 95   : 	struct _stat sbuff1; memset(&sbuff1, 0, sizeof(sbuff1));

	push	36					; 00000024H
	push	0
	lea	ecx, DWORD PTR _sbuff1$[ebp]
	push	ecx
	call	_memset
	add	esp, 12					; 0000000cH

; 96   : 	struct _stat sbuff2; memset(&sbuff2, 0, sizeof(sbuff2));

	push	36					; 00000024H
	push	0
	lea	edx, DWORD PTR _sbuff2$[ebp]
	push	edx
	call	_memset
	add	esp, 12					; 0000000cH

; 97   : 
; 98   : 	_stat(pname, &sbuff1); _stat(fragname, &sbuff2);

	mov	esi, esp
	lea	eax, DWORD PTR _sbuff1$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pname$[ebp]
	push	ecx
	call	DWORD PTR __imp___stat
	add	esp, 8
	cmp	esi, esp
	call	__chkesp
	mov	esi, esp
	lea	edx, DWORD PTR _sbuff2$[ebp]
	push	edx
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??BCString@@QBEPBDXZ			; CString::operator char const *
	push	eax
	call	DWORD PTR __imp___stat
	add	esp, 8
	cmp	esi, esp
	call	__chkesp

; 99   : 
; 100  : 	//P2N("sbuff1=%d sbuff2=%d\r\n", sbuff1.st_mtime, sbuff2.st_mtime);
; 101  : 
; 102  : 	if((sbuff1.st_mtime > sbuff2.st_mtime) || force)

	mov	eax, DWORD PTR _sbuff1$[ebp+28]
	cmp	eax, DWORD PTR _sbuff2$[ebp+28]
	jg	SHORT $L94665
	cmp	DWORD PTR _force$[ebp], 0
	je	$L94664
$L94665:

; 104  : 		int		len2, len22;
; 105  : 		char	*buff2;
; 106  : 
; 107  : 		WAVEFORMATEX wfx; 
; 108  : 
; 109  : 		if(dsp.LoadWave(pname, &buff2, &len2, &wfx) == 0)

	lea	ecx, DWORD PTR _wfx$94669[ebp]
	push	ecx
	lea	edx, DWORD PTR _len2$94666[ebp]
	push	edx
	lea	eax, DWORD PTR _buff2$94668[ebp]
	push	eax
	mov	ecx, DWORD PTR _pname$[ebp]
	push	ecx
	mov	ecx, OFFSET FLAT:?dsp@@3VCDsp@@A	; dsp
	call	?LoadWave@CDsp@@QAEHPBDPAPADPAHPAUtWAVEFORMATEX@@@Z ; CDsp::LoadWave
	test	eax, eax
	jne	SHORT $L94670

; 111  : 			AP2N("Cannot load Wave %s\r\n", pname);

	mov	edx, DWORD PTR _pname$[ebp]
	push	edx
	push	OFFSET FLAT:??_C@_0BG@FFGF@Cannot?5load?5Wave?5?$CFs?$AN?6?$AA@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 12					; 0000000cH

; 112  : 			return false;

	mov	DWORD PTR $T95068[ebp], 0
	mov	BYTE PTR __$EHRec$[ebp+8], 0
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	eax, DWORD PTR $T95068[ebp]
	jmp	$L94656
$L94670:

; 114  : 		
; 115  : 		if(wfx.nChannels == 2)

	mov	eax, DWORD PTR _wfx$94669[ebp+2]
	and	eax, 65535				; 0000ffffH
	cmp	eax, 2
	jne	$L94673

; 117  : 			//AP2N("CFrag::Load Convering to mono %d bytes\r\n", len2);
; 118  : 		
; 119  : 			len22 = len2 / 2;

	mov	eax, DWORD PTR _len2$94666[ebp]
	cdq
	sub	eax, edx
	sar	eax, 1
	mov	DWORD PTR _len22$94667[ebp], eax

; 120  : 			short *lptr = (short*)malloc(len22); ASSERT(lptr);

	mov	esi, esp
	mov	ecx, DWORD PTR _len22$94667[ebp]
	push	ecx
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__chkesp
	mov	DWORD PTR _lptr$94674[ebp], eax
$L94677:
	cmp	DWORD PTR _lptr$94674[ebp], 0
	jne	SHORT $L94680
	movsx	edx, WORD PTR ?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa ; `CFrag::ParseFragWav'::`2'::__LINE__Var
	add	edx, 40					; 00000028H
	push	edx
	push	OFFSET FLAT:_THIS_FILE
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L94680
	int	3
$L94680:
	xor	eax, eax
	test	eax, eax
	jne	SHORT $L94677

; 121  : 			short *rptr = (short*)malloc(len22); ASSERT(rptr);

	mov	esi, esp
	mov	ecx, DWORD PTR _len22$94667[ebp]
	push	ecx
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__chkesp
	mov	DWORD PTR _rptr$94681[ebp], eax
$L94683:
	cmp	DWORD PTR _rptr$94681[ebp], 0
	jne	SHORT $L94686
	movsx	edx, WORD PTR ?__LINE__Var@?1??ParseFragWav@CFrag@@SAHPBD0H@Z@4FA@c97f9caa ; `CFrag::ParseFragWav'::`2'::__LINE__Var
	add	edx, 41					; 00000029H
	push	edx
	push	OFFSET FLAT:_THIS_FILE
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L94686
	int	3
$L94686:
	xor	eax, eax
	test	eax, eax
	jne	SHORT $L94683

; 122  : 
; 123  : 			buff4 = (char*)lptr;

	mov	ecx, DWORD PTR _lptr$94674[ebp]
	mov	DWORD PTR _buff4$[ebp], ecx

; 124  : 			
; 125  : 			dsp.SplitWave((short*)buff2, len2, lptr, rptr, len22);

	mov	edx, DWORD PTR _len22$94667[ebp]
	push	edx
	mov	eax, DWORD PTR _rptr$94681[ebp]
	push	eax
	mov	ecx, DWORD PTR _lptr$94674[ebp]
	push	ecx
	mov	edx, DWORD PTR _len2$94666[ebp]
	push	edx
	mov	eax, DWORD PTR _buff2$94668[ebp]
	push	eax
	mov	ecx, OFFSET FLAT:?dsp@@3VCDsp@@A	; dsp
	call	?SplitWave@CDsp@@QAEXPAFH00H@Z		; CDsp::SplitWave

; 126  : 			free(rptr); free(buff2);

	mov	esi, esp
	mov	ecx, DWORD PTR _rptr$94681[ebp]
	push	ecx
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__chkesp
	mov	esi, esp
	mov	edx, DWORD PTR _buff2$94668[ebp]
	push	edx
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__chkesp

; 128  : 		else

	jmp	SHORT $L94689
$L94673:

; 130  : 			len22 = len2;

	mov	eax, DWORD PTR _len2$94666[ebp]
	mov	DWORD PTR _len22$94667[ebp], eax

; 131  : 			buff4 = buff2;

	mov	ecx, DWORD PTR _buff2$94668[ebp]
	mov	DWORD PTR _buff4$[ebp], ecx
$L94689:

; 133  : 
; 134  : 		CPtrArray arr, arr2; CIntArr sarr;

	lea	ecx, DWORD PTR _arr$94690[ebp]
	call	??0CPtrArray@@QAE@XZ			; CPtrArray::CPtrArray
	mov	BYTE PTR __$EHRec$[ebp+8], 3
	lea	ecx, DWORD PTR _arr2$94691[ebp]
	call	??0CPtrArray@@QAE@XZ			; CPtrArray::CPtrArray
	mov	BYTE PTR __$EHRec$[ebp+8], 4
	lea	ecx, DWORD PTR _sarr$94692[ebp]
	call	??0CIntArr@@QAE@XZ			; CIntArr::CIntArr
	mov	BYTE PTR __$EHRec$[ebp+8], 5

; 135  : 
; 136  : 		char *buff3 = (char*)malloc(len22);

	mov	esi, esp
	mov	edx, DWORD PTR _len22$94667[ebp]
	push	edx
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__chkesp
	mov	DWORD PTR _buff3$94693[ebp], eax

; 137  : 		dsp.NormalizeWav(buff4, len22, buff3);

	mov	eax, DWORD PTR _buff3$94693[ebp]
	push	eax
	mov	ecx, DWORD PTR _len22$94667[ebp]
	push	ecx
	mov	edx, DWORD PTR _buff4$[ebp]
	push	edx
	mov	ecx, OFFSET FLAT:?dsp@@3VCDsp@@A	; dsp
	call	?NormalizeWav@CDsp@@QAEXPADH0@Z		; CDsp::NormalizeWav

; 145  : 	
; 146  : 		//////////////////////////////////////////////////////////////////
; 147  : 		// Fxresh start for arrays
; 148  : 	
; 149  : 		CAnalRes res;

	lea	ecx, DWORD PTR _res$94695[ebp]
	call	??0CAnalRes@@QAE@XZ			; CAnalRes::CAnalRes
	mov	BYTE PTR __$EHRec$[ebp+8], 6

; 150  : 		xdllrecog.ScanSpectra(buff3, len22, &res);

	lea	eax, DWORD PTR _res$94695[ebp]
	push	eax
	mov	ecx, DWORD PTR _len22$94667[ebp]
	push	ecx
	mov	edx, DWORD PTR _buff3$94693[ebp]
	push	edx
	mov	ecx, OFFSET FLAT:?xdllrecog@@3VCxRecog@@A
	call	?ScanSpectra@CxRecog@@QAEXPADHPAVCAnalRes@@@Z ; CxRecog::ScanSpectra

; 151  : 				
; 152  : 		free(buff3); free(buff4);

	mov	esi, esp
	mov	eax, DWORD PTR _buff3$94693[ebp]
	push	eax
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__chkesp
	mov	esi, esp
	mov	ecx, DWORD PTR _buff4$[ebp]
	push	ecx
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__chkesp

; 153  : 
; 154  : 		xdllrecog.analproc.ProcSpectra(&res, xdllrecog.FreqCompCnt);

	mov	edx, DWORD PTR ?xdllrecog@@3VCxRecog@@A+52
	push	edx
	lea	eax, DWORD PTR _res$94695[ebp]
	push	eax
	mov	ecx, OFFSET FLAT:?xdllrecog@@3VCxRecog@@A+44
	call	?ProcSpectra@CAnalProc@@QAEXPAVCAnalRes@@H@Z ; CAnalProc::ProcSpectra

; 155  : 
; 156  : 		//int cnt = 0, pcnt = 0, mcnt = 0;
; 157  : 
; 158  : 		CFile fp;

	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	??0CFile@@QAE@XZ			; CFile::CFile
	mov	BYTE PTR __$EHRec$[ebp+8], 7

; 159  : 		
; 160  : 		if(!fp.Open(fragname, CFile::modeCreate | CFile::modeWrite))

	push	0
	push	4097					; 00001001H
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??BCString@@QBEPBDXZ			; CString::operator char const *
	push	eax
	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	?Open@CFile@@UAEHPBDIPAVCFileException@@@Z ; CFile::Open
	test	eax, eax
	jne	SHORT $L94697

; 162  : 			AP2N("Cannot create / open frag file for %s\r\n", fragname);

	mov	ecx, DWORD PTR _fragname$[ebp]
	push	ecx
	push	OFFSET FLAT:??_C@_0CI@DEPE@Cannot?5create?5?1?5open?5frag?5file?5f@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 12					; 0000000cH

; 163  : 			ret = false;		

	mov	DWORD PTR _ret$[ebp], 0

; 165  : 		else

	jmp	SHORT $L94699
$L94697:

; 167  : 			int smagic = CFrag_Magic;

	mov	DWORD PTR _smagic$94700[ebp], 14935269	; 00e3e4e5H

; 168  : 
; 169  : 			fp.Write(&smagic, sizeof(int));

	push	4
	lea	edx, DWORD PTR _smagic$94700[ebp]
	push	edx
	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	?Write@CFile@@UAEXPBXI@Z		; CFile::Write

; 170  : 
; 171  : 			res.ToFile(&fp);

	lea	eax, DWORD PTR _fp$94696[ebp]
	push	eax
	lea	ecx, DWORD PTR _res$94695[ebp]
	call	?ToFile@CAnalRes@@QAEHPAVCFile@@@Z	; CAnalRes::ToFile

; 172  : 
; 173  : 			// Final magic for checking 
; 174  : 			fp.Write(&smagic, sizeof(int));	

	push	4
	lea	ecx, DWORD PTR _smagic$94700[ebp]
	push	ecx
	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	?Write@CFile@@UAEXPBXI@Z		; CFile::Write
$L94699:

; 176  : 
; 177  : 		//AP2N("Wrote '%s' %d (%d) scan units \r\n", pname, cnt, pcnt);	
; 178  : 		//AP2N("Wrote %s %d buffers\r\n", pname, cnt);
; 179  : 		}

	mov	BYTE PTR __$EHRec$[ebp+8], 6
	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	??1CFile@@UAE@XZ			; CFile::~CFile
	mov	BYTE PTR __$EHRec$[ebp+8], 5
	lea	ecx, DWORD PTR _res$94695[ebp]
	call	??1CAnalRes@@UAE@XZ			; CAnalRes::~CAnalRes
	mov	BYTE PTR __$EHRec$[ebp+8], 4
	lea	ecx, DWORD PTR _sarr$94692[ebp]
	call	??1CIntArr@@UAE@XZ			; CIntArr::~CIntArr
	mov	BYTE PTR __$EHRec$[ebp+8], 3
	lea	ecx, DWORD PTR _arr2$94691[ebp]
	call	??1CPtrArray@@UAE@XZ			; CPtrArray::~CPtrArray
	mov	BYTE PTR __$EHRec$[ebp+8], 1
	lea	ecx, DWORD PTR _arr$94690[ebp]
	call	??1CPtrArray@@UAE@XZ			; CPtrArray::~CPtrArray
$L94664:

; 180  : 
; 181  : 	return ret;

	mov	edx, DWORD PTR _ret$[ebp]
	mov	DWORD PTR $T95069[ebp], edx
	mov	BYTE PTR __$EHRec$[ebp+8], 0
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	eax, DWORD PTR $T95069[ebp]
$L94656:

; 182  : }

	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:__except_list, ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 536				; 00000218H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$0:
	lea	ecx, DWORD PTR _wname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$1:
	lea	ecx, DWORD PTR _fragname$[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$2:
	lea	ecx, DWORD PTR $T95067[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$3:
	lea	ecx, DWORD PTR _arr$94690[ebp]
	call	??1CPtrArray@@UAE@XZ			; CPtrArray::~CPtrArray
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$4:
	lea	ecx, DWORD PTR _arr2$94691[ebp]
	call	??1CPtrArray@@UAE@XZ			; CPtrArray::~CPtrArray
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$5:
	lea	ecx, DWORD PTR _sarr$94692[ebp]
	call	??1CIntArr@@UAE@XZ			; CIntArr::~CIntArr
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$6:
	lea	ecx, DWORD PTR _res$94695[ebp]
	call	??1CAnalRes@@UAE@XZ			; CAnalRes::~CAnalRes
	ret	0
__unwindfunclet$?ParseFragWav@CFrag@@SAHPBD0H@Z$7:
	lea	ecx, DWORD PTR _fp$94696[ebp]
	call	??1CFile@@UAE@XZ			; CFile::~CFile
	ret	0
__ehhandler$?ParseFragWav@CFrag@@SAHPBD0H@Z:
	mov	eax, OFFSET FLAT:__ehfuncinfo$?ParseFragWav@CFrag@@SAHPBD0H@Z
	jmp	___CxxFrameHandler
text$x	ENDS
?ParseFragWav@CFrag@@SAHPBD0H@Z ENDP			; CFrag::ParseFragWav
PUBLIC	?GetSize@CArrIntArr@@QAEHXZ			; CArrIntArr::GetSize
PUBLIC	?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ	; CArrIntArr::GetData
PUBLIC	?__LINE__Var@?1??LoadFrag@CFrag@@QAEHPBDH@Z@4FA	; `CFrag::LoadFrag'::`2'::__LINE__Var
PUBLIC	??_C@_0M@BDNF@1234567890?9?$AA@			; `string'
PUBLIC	??_C@_0BG@HLAC@Cannot?5load?5file?5?$CFs?$AN?6?$AA@ ; `string'
PUBLIC	??_C@_0CE@LGCK@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIstart@ ; `string'
PUBLIC	??_C@_0CC@KACJ@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIend?$CJ?$AN@ ; `string'
PUBLIC	??_C@_0CF@FNN@CFrag?3?3LoadFrag?5empty?5buffer?5on?5@ ; `string'
PUBLIC	?LoadFrag@CFrag@@QAEHPBDH@Z			; CFrag::LoadFrag
EXTRN	?PathToFname@CSupport@@QAEXAAVCString@@@Z:NEAR	; CSupport::PathToFname
EXTRN	?Vis@CAnalProc@@QAEXPAVCPtrArray@@0@Z:NEAR	; CAnalProc::Vis
EXTRN	?VisRaw@CAnalProc@@QAEXPAVCPtrArray@@@Z:NEAR	; CAnalProc::VisRaw
EXTRN	?Read@CFile@@UAEIPAXI@Z:NEAR			; CFile::Read
EXTRN	?FromFile@CAnalRes@@QAEHPAVCFile@@@Z:NEAR	; CAnalRes::FromFile
EXTRN	?Close@CFile@@UAEXXZ:NEAR			; CFile::Close
EXTRN	??4CString@@QAEABV0@PBD@Z:NEAR			; CString::operator=
EXTRN	?Left@CString@@QBE?AV1@H@Z:NEAR			; CString::Left
EXTRN	?MakeLower@CString@@QAEXXZ:NEAR			; CString::MakeLower
EXTRN	?FindOneOf@CString@@QBEHPBD@Z:NEAR		; CString::FindOneOf
;	COMDAT ?__LINE__Var@?1??LoadFrag@CFrag@@QAEHPBDH@Z@4FA
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
_DATA	SEGMENT
?__LINE__Var@?1??LoadFrag@CFrag@@QAEHPBDH@Z@4FA DW 0beH	; `CFrag::LoadFrag'::`2'::__LINE__Var
_DATA	ENDS
;	COMDAT ??_C@_0M@BDNF@1234567890?9?$AA@
CONST	SEGMENT
??_C@_0M@BDNF@1234567890?9?$AA@ DB '1234567890-', 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_0BG@HLAC@Cannot?5load?5file?5?$CFs?$AN?6?$AA@
CONST	SEGMENT
??_C@_0BG@HLAC@Cannot?5load?5file?5?$CFs?$AN?6?$AA@ DB 'Cannot load file '
	DB	'%s', 0dH, 0aH, 00H				; `string'
CONST	ENDS
;	COMDAT ??_C@_0CE@LGCK@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIstart@
CONST	SEGMENT
??_C@_0CE@LGCK@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIstart@ DB 'CFrag::LoadF'
	DB	'rag BAD magic (start)', 0dH, 0aH, 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_0CC@KACJ@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIend?$CJ?$AN@
CONST	SEGMENT
??_C@_0CC@KACJ@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIend?$CJ?$AN@ DB 'CFrag:'
	DB	':LoadFrag BAD magic (end)', 0dH, 0aH, 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_0CF@FNN@CFrag?3?3LoadFrag?5empty?5buffer?5on?5@
CONST	SEGMENT
??_C@_0CF@FNN@CFrag?3?3LoadFrag?5empty?5buffer?5on?5@ DB 'CFrag::LoadFrag'
	DB	' empty buffer on %s', 0dH, 0aH, 00H		; `string'
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__ehfuncinfo$?LoadFrag@CFrag@@QAEHPBDH@Z DD 019930520H
	DD	03H
	DD	FLAT:__unwindtable$?LoadFrag@CFrag@@QAEHPBDH@Z
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
__unwindtable$?LoadFrag@CFrag@@QAEHPBDH@Z DD 0ffffffffH
	DD	FLAT:__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$0
	DD	0ffffffffH
	DD	FLAT:__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$1
	DD	0ffffffffH
	DD	FLAT:__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$2
xdata$x	ENDS
;	COMDAT ?LoadFrag@CFrag@@QAEHPBDH@Z
_TEXT	SEGMENT
_str$ = 8
_this$ = -16
_idxx$ = -20
_fp$ = -36
_sss$ = -40
_ppp$ = -44
_vvv$ = -48
_xmagic$ = -52
$T95086 = -56
$T95087 = -60
$T95088 = -64
$T95089 = -68
__$EHRec$ = -12
?LoadFrag@CFrag@@QAEHPBDH@Z PROC NEAR			; CFrag::LoadFrag, COMDAT

; 190  : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$?LoadFrag@CFrag@@QAEHPBDH@Z
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 136				; 00000088H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-148]
	mov	ecx, 34					; 00000022H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
$L94710:

; 191  : 	ASSERT(magic == CFrag_Magic);

	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax+8], 14935269		; 00e3e4e5H
	je	SHORT $L94713
	movsx	ecx, WORD PTR ?__LINE__Var@?1??LoadFrag@CFrag@@QAEHPBDH@Z@4FA ; `CFrag::LoadFrag'::`2'::__LINE__Var
	add	ecx, 1
	push	ecx
	push	OFFSET FLAT:_THIS_FILE
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L94713
	int	3
$L94713:
	xor	edx, edx
	test	edx, edx
	jne	SHORT $L94710

; 192  : 
; 193  : 	//AP2N("CFrag::LoadFrag '%s'\r\n", str);
; 194  : 
; 195  : 	*fname = str; *name = str;

	mov	eax, DWORD PTR _str$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [ecx+20]
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=
	mov	edx, DWORD PTR _str$[ebp]
	push	edx
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 196  : 	
; 197  : 	support.PathToFname(*name); *name = support.GetFilename(*name);

	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+12]
	push	edx
	mov	ecx, OFFSET FLAT:?support@@3VCSupport@@A
	call	?PathToFname@CSupport@@QAEXAAVCString@@@Z ; CSupport::PathToFname
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	push	ecx
	lea	edx, DWORD PTR $T95086[ebp]
	push	edx
	mov	ecx, OFFSET FLAT:?support@@3VCSupport@@A
	call	?GetFilename@CSupport@@QAE?AVCString@@ABV2@@Z ; CSupport::GetFilename
	mov	DWORD PTR -72+[ebp], eax
	mov	eax, DWORD PTR -72+[ebp]
	mov	DWORD PTR -76+[ebp], eax
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	mov	ecx, DWORD PTR -76+[ebp]
	push	ecx
	mov	edx, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [edx+12]
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR $T95086[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString

; 198  : 
; 199  : 	int idxx = name->FindOneOf("1234567890-");

	push	OFFSET FLAT:??_C@_0M@BDNF@1234567890?9?$AA@ ; `string'
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	call	?FindOneOf@CString@@QBEHPBD@Z		; CString::FindOneOf
	mov	DWORD PTR _idxx$[ebp], eax

; 200  : 	
; 201  : 	if(idxx >= 0)

	cmp	DWORD PTR _idxx$[ebp], 0
	jl	SHORT $L94717

; 202  : 		*shortname = name->Left(idxx);

	mov	ecx, DWORD PTR _idxx$[ebp]
	push	ecx
	lea	edx, DWORD PTR $T95087[ebp]
	push	edx
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	call	?Left@CString@@QBE?AV1@H@Z		; CString::Left
	mov	DWORD PTR -80+[ebp], eax
	mov	ecx, DWORD PTR -80+[ebp]
	mov	DWORD PTR -84+[ebp], ecx
	mov	DWORD PTR __$EHRec$[ebp+8], 1
	mov	edx, DWORD PTR -84+[ebp]
	push	edx
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+16]
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR $T95087[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString

; 203  : 	else

	jmp	SHORT $L94719
$L94717:

; 204  : 		*shortname = *name;

	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+12]
	push	edx
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+16]
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
$L94719:

; 205  : 
; 206  : 	shortname->MakeLower();

	mov	ecx, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [ecx+16]
	call	?MakeLower@CString@@QAEXXZ		; CString::MakeLower

; 207  : 	name->MakeLower();

	mov	edx, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [edx+12]
	call	?MakeLower@CString@@QAEXXZ		; CString::MakeLower

; 208  : 
; 209  : 	//AP2N("CFrag::LoadFrag for '%s'\r\n", *name);
; 210  : 
; 211  : 	CFile fp;		

	lea	ecx, DWORD PTR _fp$[ebp]
	call	??0CFile@@QAE@XZ			; CFile::CFile
	mov	DWORD PTR __$EHRec$[ebp+8], 2

; 212  : 	if(!fp.Open(str, CFile::modeRead))

	push	0
	push	0
	mov	eax, DWORD PTR _str$[ebp]
	push	eax
	lea	ecx, DWORD PTR _fp$[ebp]
	call	?Open@CFile@@UAEHPBDIPAVCFileException@@@Z ; CFile::Open
	test	eax, eax
	jne	SHORT $L94721

; 214  : 		AP2N("Cannot load file %s\r\n", str);

	mov	ecx, DWORD PTR _str$[ebp]
	push	ecx
	push	OFFSET FLAT:??_C@_0BG@HLAC@Cannot?5load?5file?5?$CFs?$AN?6?$AA@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 12					; 0000000cH

; 215  : 		return false;

	mov	DWORD PTR $T95088[ebp], 0
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR _fp$[ebp]
	call	??1CFile@@UAE@XZ			; CFile::~CFile
	mov	eax, DWORD PTR $T95088[ebp]
	jmp	$L94708
$L94721:

; 217  : 
; 218  : 	// Get saved entries
; 219  : 	//int cnt = 0, pcnt = 0, vcnt = 0;
; 220  : 	int sss = 0, ppp = 0, vvv = 0, xmagic = 0; 

	mov	DWORD PTR _sss$[ebp], 0
	mov	DWORD PTR _ppp$[ebp], 0
	mov	DWORD PTR _vvv$[ebp], 0
	mov	DWORD PTR _xmagic$[ebp], 0

; 221  : 	
; 222  : 	fp.Read(&xmagic, sizeof(int));

	push	4
	lea	edx, DWORD PTR _xmagic$[ebp]
	push	edx
	lea	ecx, DWORD PTR _fp$[ebp]
	call	?Read@CFile@@UAEIPAXI@Z			; CFile::Read

; 223  : 	if(xmagic != magic)

	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR _xmagic$[ebp]
	cmp	ecx, DWORD PTR [eax+8]
	je	SHORT $L94729

; 225  : 		AP2N("CFrag::LoadFrag BAD magic (start)\r\n");

	push	OFFSET FLAT:??_C@_0CE@LGCK@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIstart@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 8
$L94729:

; 227  : 
; 228  : 	xres.FromFile(&fp);

	lea	edx, DWORD PTR _fp$[ebp]
	push	edx
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 28					; 0000001cH
	call	?FromFile@CAnalRes@@QAEHPAVCFile@@@Z	; CAnalRes::FromFile

; 229  : 	
; 230  : 	fp.Read(&xmagic, sizeof(int));

	push	4
	lea	eax, DWORD PTR _xmagic$[ebp]
	push	eax
	lea	ecx, DWORD PTR _fp$[ebp]
	call	?Read@CFile@@UAEIPAXI@Z			; CFile::Read

; 231  : 	if(xmagic != magic)

	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR _xmagic$[ebp]
	cmp	edx, DWORD PTR [ecx+8]
	je	SHORT $L94732

; 233  : 		AP2N("CFrag::LoadFrag BAD magic (end)\r\n");

	push	OFFSET FLAT:??_C@_0CC@KACJ@CFrag?3?3LoadFrag?5BAD?5magic?5?$CIend?$CJ?$AN@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 8
$L94732:

; 235  : 			
; 236  : 	fp.Close();

	lea	ecx, DWORD PTR _fp$[ebp]
	call	?Close@CFile@@UAEXXZ			; CFile::Close

; 237  : 
; 238  : 	if(xres.raw.GetSize() == 0)

	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 64					; 00000040H
	call	?GetSize@CArrIntArr@@QAEHXZ		; CArrIntArr::GetSize
	test	eax, eax
	jne	SHORT $L94734

; 240  : 		AP2N("CFrag::LoadFrag empty buffer on %s\r\n", *name);

	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	edx, DWORD PTR [ecx]
	push	edx
	push	OFFSET FLAT:??_C@_0CF@FNN@CFrag?3?3LoadFrag?5empty?5buffer?5on?5@ ; `string'
	push	OFFSET FLAT:?mxpad@@3VMxPad@@A
	call	?aprintf@MxPad@@QAAHPBDZZ		; MxPad::aprintf
	add	esp, 12					; 0000000cH
$L94734:

; 246  : 
; 247  : 	//AP2N("Loaded '%s' %d buffers %d entries each\r\n", *name, cnt, sss);
; 248  : 
; 249  : 	// Dumper for loads
; 250  : #if 0
; 251  : 	AP2N("CFrag::LoadFrag  Dump: '%s'\r\n", *name);
; 252  : 
; 253  : 	for(int loopd = 0; loopd < xres.all.GetSize(); loopd++)
; 254  : 		{
; 255  : 		CIntArr *ptmp = xres.all.GetAt(loopd);		
; 256  : 		CIntArr *vtmp = xres.vall.GetAt(loopd);		
; 257  : 	
; 258  : 		int alen3 = ptmp->GetSize();
; 259  : 				
; 260  : 		for(int loopd3 = 0; loopd3 < alen3; loopd3++)
; 261  : 			{
; 262  : 			AP2N("%3d-%3d  ", ptmp->GetAt(loopd3),
; 263  : 						vtmp->GetAt(loopd3));
; 264  : 			}
; 265  : 	
; 266  : 		if(alen3)
; 267  : 			AP2N("\r\n");
; 268  : 		}
; 269  : #endif
; 270  : 
; 271  : #if 0
; 272  : 	int powlen = xres.pow.GetSize();
; 273  : 	AP2N("CFrag::LoadFrag  Power Dump: '%s' (%d)\r\n", *name, powlen);
; 274  : 	for(int loopd2 = 0; loopd2 < powlen; loopd2++)
; 275  : 		{		
; 276  : 		CIntArr *ptmp = xres.pow.GetAt(loopd2);
; 277  : 
; 278  : 		for(int loopd3 = 0; loopd3 < ptmp->GetSize(); loopd3++)
; 279  : 			AP2N("%3d ", ptmp->GetAt(loopd3));							
; 280  : 
; 281  : 		AP2N("\r\n");
; 282  : 		}
; 283  : #endif
; 284  : 
; 285  : #if 1
; 286  : 	// Visualizer for loads
; 287  : 	xdllrecog.analproc.VisRaw(xres.raw.GetData());

	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 64					; 00000040H
	call	?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ ; CArrIntArr::GetData
	push	eax
	mov	ecx, OFFSET FLAT:?xdllrecog@@3VCxRecog@@A+44
	call	?VisRaw@CAnalProc@@QAEXPAVCPtrArray@@@Z	; CAnalProc::VisRaw

; 288  : 	xdllrecog.analproc.Vis(xres.all.GetData(), xres.vall.GetData());

	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 148				; 00000094H
	call	?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ ; CArrIntArr::GetData
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 120				; 00000078H
	call	?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ ; CArrIntArr::GetData
	push	eax
	mov	ecx, OFFSET FLAT:?xdllrecog@@3VCxRecog@@A+44
	call	?Vis@CAnalProc@@QAEXPAVCPtrArray@@0@Z	; CAnalProc::Vis

; 289  : #endif
; 290  : 
; 291  : 	return true;

	mov	DWORD PTR $T95089[ebp], 1
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR _fp$[ebp]
	call	??1CFile@@UAE@XZ			; CFile::~CFile
	mov	eax, DWORD PTR $T95089[ebp]
$L94708:

; 292  : }

	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:__except_list, ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 148				; 00000094H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	8
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$0:
	lea	ecx, DWORD PTR $T95086[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	ret	0
__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$1:
	lea	ecx, DWORD PTR $T95087[ebp]
	call	??1CString@@QAE@XZ			; CString::~CString
	ret	0
__unwindfunclet$?LoadFrag@CFrag@@QAEHPBDH@Z$2:
	lea	ecx, DWORD PTR _fp$[ebp]
	call	??1CFile@@UAE@XZ			; CFile::~CFile
	ret	0
__ehhandler$?LoadFrag@CFrag@@QAEHPBDH@Z:
	mov	eax, OFFSET FLAT:__ehfuncinfo$?LoadFrag@CFrag@@QAEHPBDH@Z
	jmp	___CxxFrameHandler
text$x	ENDS
?LoadFrag@CFrag@@QAEHPBDH@Z ENDP			; CFrag::LoadFrag
EXTRN	?GetSize@CPtrArray@@QBEHXZ:NEAR			; CPtrArray::GetSize
;	COMDAT ?GetSize@CArrIntArr@@QAEHXZ
_TEXT	SEGMENT
_this$ = -4
?GetSize@CArrIntArr@@QAEHXZ PROC NEAR			; CArrIntArr::GetSize, COMDAT

; 52   : 	inline int			GetSize() { return arrdata.GetSize(); }

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 8
	call	?GetSize@CPtrArray@@QBEHXZ		; CPtrArray::GetSize
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 68					; 00000044H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
?GetSize@CArrIntArr@@QAEHXZ ENDP			; CArrIntArr::GetSize
_TEXT	ENDS
;	COMDAT ?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ
_TEXT	SEGMENT
_this$ = -4
?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ PROC NEAR	; CArrIntArr::GetData, COMDAT

; 53   : 	inline CPtrArray*	GetData() { return &arrdata; }

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	eax, DWORD PTR _this$[ebp]
	add	eax, 8
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?GetData@CArrIntArr@@QAEPAVCPtrArray@@XZ ENDP		; CArrIntArr::GetData
_TEXT	ENDS
PUBLIC	?Add@CIntArr@@QAEHH@Z				; CIntArr::Add
PUBLIC	?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z ; CFrag::CmpFrags
PUBLIC	?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z	; CFrag::xHitFrags
EXTRN	??0CIntArrRec@@QAE@XZ:NEAR			; CIntArrRec::CIntArrRec
EXTRN	??1CIntArrRec@@UAE@XZ:NEAR			; CIntArrRec::~CIntArrRec
EXTRN	?Sum@CIntArrRec@@QAEHXZ:NEAR			; CIntArrRec::Sum
;	COMDAT xdata$x
; File C:\develop3\wavfrag\work\wflib\Frag.cpp
xdata$x	SEGMENT
__ehfuncinfo$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z DD 019930520H
	DD	01H
	DD	FLAT:__unwindtable$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
__unwindtable$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z DD 0ffffffffH
	DD	FLAT:__unwindfunclet$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z$0
xdata$x	ENDS
;	COMDAT ?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z
_TEXT	SEGMENT
_parr$ = 8
_offs$ = 12
_pxres$ = 16
_this$ = -16
_ret$ = -20
_arrlen$ = -24
_reflen$ = -28
_sum$ = -32
_wobble$ = -36
_arr$ = -60
_loopr$ = -64
_diff$94756 = -68
_offs2$94757 = -72
_ss$94758 = -76
_ee$94759 = -80
_loopw$94760 = -84
_hit$94764 = -88
$T95111 = -92
__$EHRec$ = -12
?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z PROC NEAR ; CFrag::CmpFrags, COMDAT

; 301  : {	

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 156				; 0000009cH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-168]
	mov	ecx, 39					; 00000027H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx

; 302  : 	//AP2N("CFrag::CmpFrags %s:  ", *name);
; 303  : 
; 304  : 	int ret = 0;		// Maximizers default to small returns

	mov	DWORD PTR _ret$[ebp], 0

; 305  : 		
; 306  : 	// xreset xresult output
; 307  : 	pxres->nfund = pxres->nharm = pxres->nhiss = 0;

	mov	eax, DWORD PTR _pxres$[ebp]
	mov	DWORD PTR [eax+16], 0
	mov	ecx, DWORD PTR _pxres$[ebp]
	mov	DWORD PTR [ecx+12], 0
	mov	edx, DWORD PTR _pxres$[ebp]
	mov	DWORD PTR [edx+8], 0

; 308  : 
; 309  : 	int arrlen = parr->all.GetSize(), reflen = xres.all.GetSize();

	mov	ecx, DWORD PTR _parr$[ebp]
	add	ecx, 92					; 0000005cH
	call	?GetSize@CArrIntArr@@QAEHXZ		; CArrIntArr::GetSize
	mov	DWORD PTR _arrlen$[ebp], eax
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 120				; 00000078H
	call	?GetSize@CArrIntArr@@QAEHXZ		; CArrIntArr::GetSize
	mov	DWORD PTR _reflen$[ebp], eax

; 310  : 	
; 311  : 	// No array ... bail out
; 312  : 	if(reflen == 0)

	cmp	DWORD PTR _reflen$[ebp], 0
	jne	SHORT $L94747

; 314  : 		//AP2N("CFrag::CmpFrags zero length ref array in %s\r\n", *fname);
; 315  : 		return ret;

	mov	eax, DWORD PTR _ret$[ebp]
	jmp	$L94743
$L94747:

; 317  : 
; 318  : 	// Passes the end ... shorten scan
; 319  : 	if(arrlen <= offs + reflen)

	mov	eax, DWORD PTR _offs$[ebp]
	add	eax, DWORD PTR _reflen$[ebp]
	cmp	DWORD PTR _arrlen$[ebp], eax
	jg	SHORT $L94748

; 321  : 		//AP2N("CFrag::CmpFrags passes the end at %s\r\n", *fname);
; 322  : 		reflen = arrlen - offs;

	mov	ecx, DWORD PTR _arrlen$[ebp]
	sub	ecx, DWORD PTR _offs$[ebp]
	mov	DWORD PTR _reflen$[ebp], ecx
$L94748:

; 325  : 
; 326  : #ifdef _DEBUG
; 327  : 
; 328  : 	// Visualizer, only print some of the data
; 329  : 	//if(offs == 15)
; 330  : 	//	verbose = true;
; 331  : 	//else
; 332  : 	//	verbose = false;
; 333  : 
; 334  : #endif
; 335  : 
; 336  : 	int sum = 0, wobble = 1;

	mov	DWORD PTR _sum$[ebp], 0
	mov	DWORD PTR _wobble$[ebp], 1

; 337  : 
; 338  : 	CIntArrRec	arr;

	lea	ecx, DWORD PTR _arr$[ebp]
	call	??0CIntArrRec@@QAE@XZ			; CIntArrRec::CIntArrRec
	mov	DWORD PTR __$EHRec$[ebp+8], 0

; 339  : 
; 340  : 	// Walk reference
; 341  : 	for(int loopr = 0; loopr < reflen; loopr++)

	mov	DWORD PTR _loopr$[ebp], 0
	jmp	SHORT $L94753
$L94754:
	mov	edx, DWORD PTR _loopr$[ebp]
	add	edx, 1
	mov	DWORD PTR _loopr$[ebp], edx
$L94753:
	mov	eax, DWORD PTR _loopr$[ebp]
	cmp	eax, DWORD PTR _reflen$[ebp]
	jge	$L94755

; 343  : 		int diff = 0, offs2 = loopr + offs;		

	mov	DWORD PTR _diff$94756[ebp], 0
	mov	ecx, DWORD PTR _loopr$[ebp]
	add	ecx, DWORD PTR _offs$[ebp]
	mov	DWORD PTR _offs2$94757[ebp], ecx

; 344  : 		
; 345  : 		// Contain offsets
; 346  : 		int ss = MAX(0, offs2 - wobble), ee = MIN(arrlen, offs2 + wobble + 1);

	mov	edx, DWORD PTR _offs2$94757[ebp]
	sub	edx, DWORD PTR _wobble$[ebp]
	test	edx, edx
	jge	SHORT $L95105
	mov	DWORD PTR -96+[ebp], 0
	jmp	SHORT $L95106
$L95105:
	mov	eax, DWORD PTR _offs2$94757[ebp]
	sub	eax, DWORD PTR _wobble$[ebp]
	mov	DWORD PTR -96+[ebp], eax
$L95106:
	mov	ecx, DWORD PTR -96+[ebp]
	mov	DWORD PTR _ss$94758[ebp], ecx
	mov	edx, DWORD PTR _wobble$[ebp]
	mov	eax, DWORD PTR _offs2$94757[ebp]
	lea	ecx, DWORD PTR [eax+edx+1]
	cmp	DWORD PTR _arrlen$[ebp], ecx
	jge	SHORT $L95107
	mov	edx, DWORD PTR _arrlen$[ebp]
	mov	DWORD PTR -100+[ebp], edx
	jmp	SHORT $L95108
$L95107:
	mov	eax, DWORD PTR _wobble$[ebp]
	mov	ecx, DWORD PTR _offs2$94757[ebp]
	lea	edx, DWORD PTR [ecx+eax+1]
	mov	DWORD PTR -100+[ebp], edx
$L95108:
	mov	eax, DWORD PTR -100+[ebp]
	mov	DWORD PTR _ee$94759[ebp], eax

; 347  : 			
; 348  : 		// Wobble into array
; 349  : 		for(int loopw = ss; loopw < ee; loopw++)

	mov	ecx, DWORD PTR _ss$94758[ebp]
	mov	DWORD PTR _loopw$94760[ebp], ecx
	jmp	SHORT $L94761
$L94762:
	mov	edx, DWORD PTR _loopw$94760[ebp]
	add	edx, 1
	mov	DWORD PTR _loopw$94760[ebp], edx
$L94761:
	mov	eax, DWORD PTR _loopw$94760[ebp]
	cmp	eax, DWORD PTR _ee$94759[ebp]
	jge	SHORT $L94763

; 351  : 			int hit = xHitFrags(parr, loopw, loopr, xdllrecog.Strictness);

	mov	ecx, DWORD PTR ?xdllrecog@@3VCxRecog@@A+72
	push	ecx
	mov	edx, DWORD PTR _loopr$[ebp]
	push	edx
	mov	eax, DWORD PTR _loopw$94760[ebp]
	push	eax
	mov	ecx, DWORD PTR _parr$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z ; CFrag::xHitFrags
	mov	DWORD PTR _hit$94764[ebp], eax

; 352  : 			//int hit = xHitPow(parr, loopw, loopr, xdllrecog.Strictness);
; 353  : 			
; 354  : 			// What to propagate over to the compare		
; 355  : 			diff = MAX(hit, diff);

	mov	edx, DWORD PTR _hit$94764[ebp]
	cmp	edx, DWORD PTR _diff$94756[ebp]
	jle	SHORT $L95109
	mov	eax, DWORD PTR _hit$94764[ebp]
	mov	DWORD PTR -104+[ebp], eax
	jmp	SHORT $L95110
$L95109:
	mov	ecx, DWORD PTR _diff$94756[ebp]
	mov	DWORD PTR -104+[ebp], ecx
$L95110:
	mov	edx, DWORD PTR -104+[ebp]
	mov	DWORD PTR _diff$94756[ebp], edx

; 356  : 			}		

	jmp	SHORT $L94762
$L94763:

; 357  : 		arr.Add(diff);

	mov	eax, DWORD PTR _diff$94756[ebp]
	push	eax
	lea	ecx, DWORD PTR _arr$[ebp]
	call	?Add@CIntArr@@QAEHH@Z			; CIntArr::Add

; 358  : 		}

	jmp	$L94754
$L94755:

; 359  : 
; 360  : 	// Calculate the sum of hits, calc length neutral 
; 361  : 	ret = arr.Sum(); ret /= reflen;

	lea	ecx, DWORD PTR _arr$[ebp]
	call	?Sum@CIntArrRec@@QAEHXZ			; CIntArrRec::Sum
	mov	DWORD PTR _ret$[ebp], eax
	mov	eax, DWORD PTR _ret$[ebp]
	cdq
	idiv	DWORD PTR _reflen$[ebp]
	mov	DWORD PTR _ret$[ebp], eax

; 362  : 	
; 363  : #ifdef _DEBUG
; 364  : 
; 365  : 	//if(verbose)
; 366  : 	//	{
; 367  : 	//	xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 0);cfr
; 368  : 	//	xdllrecog._plotrec(NULL, 0, 0);
; 369  : 	//	}
; 370  : 
; 371  : 	// Animate for observation
; 372  : 	//Sleep(2);
; 373  : 
; 374  : #endif
; 375  : 
; 376  : 	return (ret);

	mov	ecx, DWORD PTR _ret$[ebp]
	mov	DWORD PTR $T95111[ebp], ecx
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	lea	ecx, DWORD PTR _arr$[ebp]
	call	??1CIntArrRec@@UAE@XZ			; CIntArrRec::~CIntArrRec
	mov	eax, DWORD PTR $T95111[ebp]
$L94743:

; 377  : }

	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:__except_list, ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 168				; 000000a8H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	12					; 0000000cH
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z$0:
	lea	ecx, DWORD PTR _arr$[ebp]
	call	??1CIntArrRec@@UAE@XZ			; CIntArrRec::~CIntArrRec
	ret	0
__ehhandler$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z:
	mov	eax, OFFSET FLAT:__ehfuncinfo$?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z
	jmp	___CxxFrameHandler
text$x	ENDS
?CmpFrags@CFrag@@QAEHPAVCAnalRes@@HPAVCCmpRes@@@Z ENDP	; CFrag::CmpFrags
EXTRN	?SetAtGrow@CIntArr@@QAEXHH@Z:NEAR		; CIntArr::SetAtGrow
;	COMDAT ?Add@CIntArr@@QAEHH@Z
_TEXT	SEGMENT
_newElement$ = 8
_this$ = -4
_nIndex$ = -8
?Add@CIntArr@@QAEHH@Z PROC NEAR				; CIntArr::Add, COMDAT

; 214  : 		{ int nIndex = m_nSize;

	push	ebp
	mov	ebp, esp
	sub	esp, 72					; 00000048H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-72]
	mov	ecx, 18					; 00000012H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	DWORD PTR _nIndex$[ebp], ecx

; 215  : 			SetAtGrow(nIndex, newElement);

	mov	edx, DWORD PTR _newElement$[ebp]
	push	edx
	mov	eax, DWORD PTR _nIndex$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	call	?SetAtGrow@CIntArr@@QAEXHH@Z		; CIntArr::SetAtGrow

; 216  : 			return nIndex; }

	mov	eax, DWORD PTR _nIndex$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 72					; 00000048H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	4
?Add@CIntArr@@QAEHH@Z ENDP				; CIntArr::Add
_TEXT	ENDS
PUBLIC	?GetSize@CIntArr@@QBEHXZ			; CIntArr::GetSize
PUBLIC	?GetData@CIntArr@@QAEPAHXZ			; CIntArr::GetData
EXTRN	?GetAt@CArrIntArr@@QAEPAVCIntArrRec@@H@Z:NEAR	; CArrIntArr::GetAt
;	COMDAT ?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z
_TEXT	SEGMENT
_parr$ = 8
_offs$ = 12
_loopr$ = 16
_this$ = -4
_ret$ = -8
_ref$ = -12
_tmp$ = -16
_tlen$ = -20
_rlen$ = -24
_adder$ = -28
_wobble$ = -32
_decrem$ = -36
_ddd$ = -40
_ttt$ = -44
_rloop$ = -48
_rfreq$94791 = -52
_match$94793 = -56
_lim$94794 = -60
_ss$94795 = -64
_ee$94796 = -68
_tloop$94797 = -72
_tfreq$94801 = -76
?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z PROC NEAR	; CFrag::xHitFrags, COMDAT

; 393  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 148				; 00000094H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-148]
	mov	ecx, 37					; 00000025H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx

; 394  : 	int ret = 0;

	mov	DWORD PTR _ret$[ebp], 0

; 395  : 	
; 396  : 	// Estabilish current arrays
; 397  : 	CIntArr *ref = (CIntArr *)xres.all.GetAt(loopr);	

	mov	eax, DWORD PTR _loopr$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 120				; 00000078H
	call	?GetAt@CArrIntArr@@QAEPAVCIntArrRec@@H@Z ; CArrIntArr::GetAt
	mov	DWORD PTR _ref$[ebp], eax

; 398  : 	CIntArr *tmp = (CIntArr *)parr->all.GetAt(offs);

	mov	ecx, DWORD PTR _offs$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _parr$[ebp]
	add	ecx, 92					; 0000005cH
	call	?GetAt@CArrIntArr@@QAEPAVCIntArrRec@@H@Z ; CArrIntArr::GetAt
	mov	DWORD PTR _tmp$[ebp], eax

; 399  : 	
; 400  : 	int tlen = tmp->GetSize(), rlen = ref->GetSize();

	mov	ecx, DWORD PTR _tmp$[ebp]
	call	?GetSize@CIntArr@@QBEHXZ		; CIntArr::GetSize
	mov	DWORD PTR _tlen$[ebp], eax
	mov	ecx, DWORD PTR _ref$[ebp]
	call	?GetSize@CIntArr@@QBEHXZ		; CIntArr::GetSize
	mov	DWORD PTR _rlen$[ebp], eax

; 401  : 	
; 402  : 	// Safety measuxres for index 0 access or overmach by low count
; 403  : 	if(tlen < 2)

	cmp	DWORD PTR _tlen$[ebp], 2
	jge	SHORT $L94780

; 405  : 		//AP2N("CFrag::xHitFrags zero tlen\r\n");
; 406  : 		return ret;

	mov	eax, DWORD PTR _ret$[ebp]
	jmp	$L94772
$L94780:

; 408  : 	if(rlen < 2)

	cmp	DWORD PTR _rlen$[ebp], 2
	jge	SHORT $L94781

; 410  : 		//AP2N("CFrag::xHitFrags zero rlen\r\n");
; 411  : 		return ret;

	mov	eax, DWORD PTR _ret$[ebp]
	jmp	$L94772
$L94781:

; 413  : 
; 414  : 	// Estabilish compare parameters. Determined experimentally.
; 415  : 	
; 416  : 	int adder = 100, wobble = 2;

	mov	DWORD PTR _adder$[ebp], 100		; 00000064H
	mov	DWORD PTR _wobble$[ebp], 2

; 417  : 	int decrem  = adder / (rlen * 2);

	mov	ecx, DWORD PTR _rlen$[ebp]
	shl	ecx, 1
	mov	eax, DWORD PTR _adder$[ebp]
	cdq
	idiv	ecx
	mov	DWORD PTR _decrem$[ebp], eax

; 418  : 
; 419  : 	//////////////////////////////////////////////////////////////////////
; 420  : 	// Compare with vertical wobble
; 421  : 
; 422  : 	// Aliases into data
; 423  : 	int *ddd = ref->GetData();	int *ttt = tmp->GetData();

	mov	ecx, DWORD PTR _ref$[ebp]
	call	?GetData@CIntArr@@QAEPAHXZ		; CIntArr::GetData
	mov	DWORD PTR _ddd$[ebp], eax
	mov	ecx, DWORD PTR _tmp$[ebp]
	call	?GetData@CIntArr@@QAEPAHXZ		; CIntArr::GetData
	mov	DWORD PTR _ttt$[ebp], eax

; 424  : 
; 425  : 	for(int rloop = 0; rloop < rlen; rloop++)

	mov	DWORD PTR _rloop$[ebp], 0
	jmp	SHORT $L94788
$L94789:
	mov	edx, DWORD PTR _rloop$[ebp]
	add	edx, 1
	mov	DWORD PTR _rloop$[ebp], edx
$L94788:
	mov	eax, DWORD PTR _rloop$[ebp]
	cmp	eax, DWORD PTR _rlen$[ebp]
	jge	$L94790

; 427  : 		//int rfreq	= ref->GetAt(rloop);
; 428  : 		int rfreq	= ddd[rloop];		// Direct access

	mov	ecx, DWORD PTR _rloop$[ebp]
	mov	edx, DWORD PTR _ddd$[ebp]
	mov	eax, DWORD PTR [edx+ecx*4]
	mov	DWORD PTR _rfreq$94791[ebp], eax

; 429  : 	
; 430  : 		if(rfreq == 0)		// Empty 

	cmp	DWORD PTR _rfreq$94791[ebp], 0
	jne	SHORT $L94792

; 431  : 			continue;

	jmp	SHORT $L94789
$L94792:

; 432  : 
; 433  : 		int match = false;

	mov	DWORD PTR _match$94793[ebp], 0

; 434  : 		
; 435  : 		// Tolerances to the frequency difference
; 436  : 		int lim  = rfreq / 20;

	mov	eax, DWORD PTR _rfreq$94791[ebp]
	cdq
	mov	ecx, 20					; 00000014H
	idiv	ecx
	mov	DWORD PTR _lim$94794[ebp], eax

; 437  : 		
; 438  : 		// Fetch offsets into vertical wobble, contain them
; 439  : 		int ss = rloop - wobble; ss = MAX(0, ss);

	mov	edx, DWORD PTR _rloop$[ebp]
	sub	edx, DWORD PTR _wobble$[ebp]
	mov	DWORD PTR _ss$94795[ebp], edx
	xor	eax, eax
	cmp	DWORD PTR _ss$94795[ebp], 0
	setl	al
	dec	eax
	and	eax, DWORD PTR _ss$94795[ebp]
	mov	DWORD PTR _ss$94795[ebp], eax

; 440  : 		int ee = rloop + wobble + 1; ee = MIN(tlen, ee);

	mov	ecx, DWORD PTR _wobble$[ebp]
	mov	edx, DWORD PTR _rloop$[ebp]
	lea	eax, DWORD PTR [edx+ecx+1]
	mov	DWORD PTR _ee$94796[ebp], eax
	mov	ecx, DWORD PTR _tlen$[ebp]
	cmp	ecx, DWORD PTR _ee$94796[ebp]
	jge	SHORT $L95123
	mov	edx, DWORD PTR _tlen$[ebp]
	mov	DWORD PTR -80+[ebp], edx
	jmp	SHORT $L95124
$L95123:
	mov	eax, DWORD PTR _ee$94796[ebp]
	mov	DWORD PTR -80+[ebp], eax
$L95124:
	mov	ecx, DWORD PTR -80+[ebp]
	mov	DWORD PTR _ee$94796[ebp], ecx

; 441  : 
; 442  : 		// Actual search
; 443  : 		for(int tloop = ss; tloop < ee; tloop++)

	mov	edx, DWORD PTR _ss$94795[ebp]
	mov	DWORD PTR _tloop$94797[ebp], edx
	jmp	SHORT $L94798
$L94799:
	mov	eax, DWORD PTR _tloop$94797[ebp]
	add	eax, 1
	mov	DWORD PTR _tloop$94797[ebp], eax
$L94798:
	mov	ecx, DWORD PTR _tloop$94797[ebp]
	cmp	ecx, DWORD PTR _ee$94796[ebp]
	jge	SHORT $L94800

; 445  : 			//int tfreq = tmp->GetAt(tloop);
; 446  : 			int tfreq = ttt[tloop]; // Direct access

	mov	edx, DWORD PTR _tloop$94797[ebp]
	mov	eax, DWORD PTR _ttt$[ebp]
	mov	ecx, DWORD PTR [eax+edx*4]
	mov	DWORD PTR _tfreq$94801[ebp], ecx

; 447  : 				
; 448  : 			// Compare freq indexes
; 449  : 			if(ABS(tfreq - rfreq) <= lim)			

	mov	edx, DWORD PTR _tfreq$94801[ebp]
	sub	edx, DWORD PTR _rfreq$94791[ebp]
	test	edx, edx
	jge	SHORT $L95125
	mov	eax, DWORD PTR _tfreq$94801[ebp]
	sub	eax, DWORD PTR _rfreq$94791[ebp]
	neg	eax
	mov	DWORD PTR -84+[ebp], eax
	jmp	SHORT $L95126
$L95125:
	mov	ecx, DWORD PTR _tfreq$94801[ebp]
	sub	ecx, DWORD PTR _rfreq$94791[ebp]
	mov	DWORD PTR -84+[ebp], ecx
$L95126:
	mov	edx, DWORD PTR -84+[ebp]
	cmp	edx, DWORD PTR _lim$94794[ebp]
	jg	SHORT $L94802

; 451  : 				match = true;				

	mov	DWORD PTR _match$94793[ebp], 1

; 452  : 				break;

	jmp	SHORT $L94800
$L94802:

; 454  : 			}

	jmp	SHORT $L94799
$L94800:

; 455  :  
; 456  : 		if(match)

	cmp	DWORD PTR _match$94793[ebp], 0
	je	SHORT $L94803

; 458  : 			ret += adder;			// Reward for match

	mov	eax, DWORD PTR _ret$[ebp]
	add	eax, DWORD PTR _adder$[ebp]
	mov	DWORD PTR _ret$[ebp], eax
$L94803:

; 460  : 		
; 461  : 		// Diminish count as we head towards the end
; 462  : 		adder -= decrem; 

	mov	ecx, DWORD PTR _adder$[ebp]
	sub	ecx, DWORD PTR _decrem$[ebp]
	mov	DWORD PTR _adder$[ebp], ecx

; 463  : 		}

	jmp	$L94789
$L94790:

; 464  : 
; 465  : 	//////////////////////////////////////////////////////////////////////	
; 466  : 	// Kill negatives, square function would create false positive
; 467  : 	ret = MAX(ret, 0); 	

	xor	edx, edx
	cmp	DWORD PTR _ret$[ebp], 0
	setle	dl
	dec	edx
	and	edx, DWORD PTR _ret$[ebp]
	mov	DWORD PTR _ret$[ebp], edx

; 468  : 		
; 469  : 	//if(verbose)
; 470  : 	//	AP2N("   xHitFrags tlen=%d rlen=%d ret=%d\r\n", tlen, rlen, ret);
; 471  : 
; 472  : 	return ret; 

	mov	eax, DWORD PTR _ret$[ebp]
$L94772:

; 473  : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 148				; 00000094H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	16					; 00000010H
?xHitFrags@CFrag@@IAEHPAVCAnalRes@@HHH@Z ENDP		; CFrag::xHitFrags
_TEXT	ENDS
PUBLIC	??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@ ; `string'
;	COMDAT ??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@
; File c:\develop3\common\work\intarr.h
CONST	SEGMENT
??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@ DB 'c:\develop3\co'
	DB	'mmon\work\intarr.h', 00H			; `string'
CONST	ENDS
;	COMDAT ?GetSize@CIntArr@@QBEHXZ
_TEXT	SEGMENT
_this$ = -4
?GetSize@CIntArr@@QBEHXZ PROC NEAR			; CIntArr::GetSize, COMDAT

; 164  : 		{ ASSERT(magic == CIntArr_Magic); return m_nSize; }

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
$L89444:
	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax+4], 89273140		; 05523334H
	je	SHORT $L89447
	push	164					; 000000a4H
	push	OFFSET FLAT:??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@ ; `string'
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L89447
	int	3
$L89447:
	xor	ecx, ecx
	test	ecx, ecx
	jne	SHORT $L89444
	mov	edx, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR [edx+12]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 68					; 00000044H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	0
?GetSize@CIntArr@@QBEHXZ ENDP				; CIntArr::GetSize
_TEXT	ENDS
;	COMDAT ?GetData@CIntArr@@QAEPAHXZ
_TEXT	SEGMENT
_this$ = -4
?GetData@CIntArr@@QAEPAHXZ PROC NEAR			; CIntArr::GetData, COMDAT

; 210  : 		{ return (int*)m_pData; }

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	eax, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR [eax+8]
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?GetData@CIntArr@@QAEPAHXZ ENDP				; CIntArr::GetData
_TEXT	ENDS
PUBLIC	?GetAt@CIntArr@@QBEHH@Z				; CIntArr::GetAt
PUBLIC	?xHitPow@CFrag@@IAEHPAVCAnalRes@@HHH@Z		; CFrag::xHitPow
;	COMDAT ?xHitPow@CFrag@@IAEHPAVCAnalRes@@HHH@Z
_TEXT	SEGMENT
_parr$ = 8
_offs$ = 12
_loopr$ = 16
_this$ = -4
_ret$ = -8
_ref$ = -12
_tmp$ = -16
_tlen$ = -20
_rlen$ = -24
_adder$ = -28
_wobble$ = -32
_decrem$ = -36
_ddd$ = -40
_ttt$ = -44
_rloop$ = -48
_rfreq$94829 = -52
_match$94831 = -56
_lim$94832 = -60
_ss$94833 = -64
_ee$94834 = -68
_tloop$94835 = -72
_tfreq$94839 = -76
?xHitPow@CFrag@@IAEHPAVCAnalRes@@HHH@Z PROC NEAR	; CFrag::xHitPow, COMDAT

; 479  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 148				; 00000094H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-148]
	mov	ecx, 37					; 00000025H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx

; 480  : 	int ret = 0;

	mov	DWORD PTR _ret$[ebp], 0

; 481  : 	
; 482  : 	// Estabilish current arrays
; 483  : 	CIntArr *ref = (CIntArr *)xres.pow.GetAt(loopr);	

	mov	eax, DWORD PTR _loopr$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 176				; 000000b0H
	call	?GetAt@CArrIntArr@@QAEPAVCIntArrRec@@H@Z ; CArrIntArr::GetAt
	mov	DWORD PTR _ref$[ebp], eax

; 484  : 	CIntArr *tmp = (CIntArr *)parr->pow.GetAt(offs);

	mov	ecx, DWORD PTR _offs$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _parr$[ebp]
	add	ecx, 148				; 00000094H
	call	?GetAt@CArrIntArr@@QAEPAVCIntArrRec@@H@Z ; CArrIntArr::GetAt
	mov	DWORD PTR _tmp$[ebp], eax

; 485  : 	
; 486  : 	int tlen = tmp->GetSize(), rlen = ref->GetSize();

	mov	ecx, DWORD PTR _tmp$[ebp]
	call	?GetSize@CIntArr@@QBEHXZ		; CIntArr::GetSize
	mov	DWORD PTR _tlen$[ebp], eax
	mov	ecx, DWORD PTR _ref$[ebp]
	call	?GetSize@CIntArr@@QBEHXZ		; CIntArr::GetSize
	mov	DWORD PTR _rlen$[ebp], eax

; 487  : 	
; 488  : 	// Safety measuxres for index 0 access or overmach by low count
; 489  : 	if(tlen < 2)

	cmp	DWORD PTR _tlen$[ebp], 2
	jge	SHORT $L94818

; 491  : 		//AP2N("CFrag::xHitFrags zero tlen\r\n");
; 492  : 		return ret;

	mov	eax, DWORD PTR _ret$[ebp]
	jmp	$L94810
$L94818:

; 494  : 	if(rlen < 2)

	cmp	DWORD PTR _rlen$[ebp], 2
	jge	SHORT $L94819

; 496  : 		//AP2N("CFrag::xHitFrags zero rlen\r\n");
; 497  : 		return ret;

	mov	eax, DWORD PTR _ret$[ebp]
	jmp	$L94810
$L94819:

; 499  : 
; 500  : 	// Estabilish compare parameters. Determined experimentally.
; 501  : 	
; 502  : 	int adder = 100, wobble = 2;

	mov	DWORD PTR _adder$[ebp], 100		; 00000064H
	mov	DWORD PTR _wobble$[ebp], 2

; 503  : 	int decrem  = adder / (rlen * 2);

	mov	ecx, DWORD PTR _rlen$[ebp]
	shl	ecx, 1
	mov	eax, DWORD PTR _adder$[ebp]
	cdq
	idiv	ecx
	mov	DWORD PTR _decrem$[ebp], eax

; 504  : 
; 505  : 	//////////////////////////////////////////////////////////////////////
; 506  : 	// Compare with vertical wobble
; 507  : 
; 508  : 	// Aliases into data
; 509  : 	int *ddd = ref->GetData();	int *ttt = tmp->GetData();

	mov	ecx, DWORD PTR _ref$[ebp]
	call	?GetData@CIntArr@@QAEPAHXZ		; CIntArr::GetData
	mov	DWORD PTR _ddd$[ebp], eax
	mov	ecx, DWORD PTR _tmp$[ebp]
	call	?GetData@CIntArr@@QAEPAHXZ		; CIntArr::GetData
	mov	DWORD PTR _ttt$[ebp], eax

; 510  : 
; 511  : 	for(int rloop = 0; rloop < rlen; rloop++)

	mov	DWORD PTR _rloop$[ebp], 0
	jmp	SHORT $L94826
$L94827:
	mov	edx, DWORD PTR _rloop$[ebp]
	add	edx, 1
	mov	DWORD PTR _rloop$[ebp], edx
$L94826:
	mov	eax, DWORD PTR _rloop$[ebp]
	cmp	eax, DWORD PTR _rlen$[ebp]
	jge	$L94828

; 513  : 		int rfreq	= ref->GetAt(rloop);

	mov	ecx, DWORD PTR _rloop$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _ref$[ebp]
	call	?GetAt@CIntArr@@QBEHH@Z			; CIntArr::GetAt
	mov	DWORD PTR _rfreq$94829[ebp], eax

; 514  : 		//int rfreq	= ddd[rloop];		// Direct access
; 515  : 	
; 516  : 		if(rfreq == 0)		// Empty 

	cmp	DWORD PTR _rfreq$94829[ebp], 0
	jne	SHORT $L94830

; 517  : 			continue;

	jmp	SHORT $L94827
$L94830:

; 518  : 
; 519  : 		int match = false;

	mov	DWORD PTR _match$94831[ebp], 0

; 520  : 		
; 521  : 		// Tolerances to the frequency difference
; 522  : 		int lim  = rfreq / 20;

	mov	eax, DWORD PTR _rfreq$94829[ebp]
	cdq
	mov	ecx, 20					; 00000014H
	idiv	ecx
	mov	DWORD PTR _lim$94832[ebp], eax

; 523  : 		//int lim = 1;
; 524  : 		
; 525  : 		// Fetch offsets into vertical wobble, contain them
; 526  : 		int ss = rloop - wobble; ss = MAX(0, ss);

	mov	edx, DWORD PTR _rloop$[ebp]
	sub	edx, DWORD PTR _wobble$[ebp]
	mov	DWORD PTR _ss$94833[ebp], edx
	xor	eax, eax
	cmp	DWORD PTR _ss$94833[ebp], 0
	setl	al
	dec	eax
	and	eax, DWORD PTR _ss$94833[ebp]
	mov	DWORD PTR _ss$94833[ebp], eax

; 527  : 		int ee = rloop + wobble + 1; ee = MIN(tlen, ee);

	mov	ecx, DWORD PTR _wobble$[ebp]
	mov	edx, DWORD PTR _rloop$[ebp]
	lea	eax, DWORD PTR [edx+ecx+1]
	mov	DWORD PTR _ee$94834[ebp], eax
	mov	ecx, DWORD PTR _tlen$[ebp]
	cmp	ecx, DWORD PTR _ee$94834[ebp]
	jge	SHORT $L95133
	mov	edx, DWORD PTR _tlen$[ebp]
	mov	DWORD PTR -80+[ebp], edx
	jmp	SHORT $L95134
$L95133:
	mov	eax, DWORD PTR _ee$94834[ebp]
	mov	DWORD PTR -80+[ebp], eax
$L95134:
	mov	ecx, DWORD PTR -80+[ebp]
	mov	DWORD PTR _ee$94834[ebp], ecx

; 528  : 
; 529  : 		// Actual search
; 530  : 		for(int tloop = ss; tloop < ee; tloop++)

	mov	edx, DWORD PTR _ss$94833[ebp]
	mov	DWORD PTR _tloop$94835[ebp], edx
	jmp	SHORT $L94836
$L94837:
	mov	eax, DWORD PTR _tloop$94835[ebp]
	add	eax, 1
	mov	DWORD PTR _tloop$94835[ebp], eax
$L94836:
	mov	ecx, DWORD PTR _tloop$94835[ebp]
	cmp	ecx, DWORD PTR _ee$94834[ebp]
	jge	SHORT $L94838

; 532  : 			int tfreq = tmp->GetAt(tloop);

	mov	edx, DWORD PTR _tloop$94835[ebp]
	push	edx
	mov	ecx, DWORD PTR _tmp$[ebp]
	call	?GetAt@CIntArr@@QBEHH@Z			; CIntArr::GetAt
	mov	DWORD PTR _tfreq$94839[ebp], eax

; 533  : 			//int tfreq = ttt[tloop]; // Direct access
; 534  : 				
; 535  : 			// Compare freq indexes
; 536  : 			if(ABS(tfreq - rfreq) <= lim)			

	mov	eax, DWORD PTR _tfreq$94839[ebp]
	sub	eax, DWORD PTR _rfreq$94829[ebp]
	test	eax, eax
	jge	SHORT $L95135
	mov	ecx, DWORD PTR _tfreq$94839[ebp]
	sub	ecx, DWORD PTR _rfreq$94829[ebp]
	neg	ecx
	mov	DWORD PTR -84+[ebp], ecx
	jmp	SHORT $L95136
$L95135:
	mov	edx, DWORD PTR _tfreq$94839[ebp]
	sub	edx, DWORD PTR _rfreq$94829[ebp]
	mov	DWORD PTR -84+[ebp], edx
$L95136:
	mov	eax, DWORD PTR -84+[ebp]
	cmp	eax, DWORD PTR _lim$94832[ebp]
	jg	SHORT $L94840

; 539  : 				match = true;				

	mov	DWORD PTR _match$94831[ebp], 1

; 540  : 				break;

	jmp	SHORT $L94838
$L94840:

; 542  : 			}

	jmp	SHORT $L94837
$L94838:

; 543  :  
; 544  : 		if(match)

	cmp	DWORD PTR _match$94831[ebp], 0
	je	SHORT $L94841

; 546  : 			ret += adder;			// Reward for match

	mov	ecx, DWORD PTR _ret$[ebp]
	add	ecx, DWORD PTR _adder$[ebp]
	mov	DWORD PTR _ret$[ebp], ecx
$L94841:

; 548  : 		
; 549  : 		// Diminish count as we head towards the end
; 550  : 		adder -= decrem; 

	mov	edx, DWORD PTR _adder$[ebp]
	sub	edx, DWORD PTR _decrem$[ebp]
	mov	DWORD PTR _adder$[ebp], edx

; 551  : 		}

	jmp	$L94827
$L94828:

; 552  : 
; 553  : 	//////////////////////////////////////////////////////////////////////	
; 554  : 	// Kill negatives, square function would create false positive
; 555  : 	ret = MAX(ret, 0); 	

	xor	eax, eax
	cmp	DWORD PTR _ret$[ebp], 0
	setle	al
	dec	eax
	and	eax, DWORD PTR _ret$[ebp]
	mov	DWORD PTR _ret$[ebp], eax

; 556  : 		
; 557  : 	//if(verbose)
; 558  : 	//	AP2N("   xHitFrags tlen=%d rlen=%d ret=%d\r\n", tlen, rlen, ret);
; 559  : 
; 560  : 	return ret; 

	mov	eax, DWORD PTR _ret$[ebp]
$L94810:

; 561  : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 148				; 00000094H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	16					; 00000010H
?xHitPow@CFrag@@IAEHPAVCAnalRes@@HHH@Z ENDP		; CFrag::xHitPow
_TEXT	ENDS
;	COMDAT ?GetAt@CIntArr@@QBEHH@Z
_TEXT	SEGMENT
_nIndex$ = 8
_this$ = -4
?GetAt@CIntArr@@QBEHH@Z PROC NEAR			; CIntArr::GetAt, COMDAT

; 189  : 		{	

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-68]
	mov	ecx, 17					; 00000011H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
$L89455:

; 190  : 			ASSERT(magic == CIntArr_Magic);

	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax+4], 89273140		; 05523334H
	je	SHORT $L89458
	push	190					; 000000beH
	push	OFFSET FLAT:??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@ ; `string'
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L89458
	int	3
$L89458:
	xor	ecx, ecx
	test	ecx, ecx
	jne	SHORT $L89455
$L89457:

; 191  : 			ASSERT(nIndex >= 0 && nIndex < m_nSize);

	cmp	DWORD PTR _nIndex$[ebp], 0
	jl	SHORT $L89463
	mov	edx, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR _nIndex$[ebp]
	cmp	eax, DWORD PTR [edx+12]
	jl	SHORT $L89462
$L89463:
	push	191					; 000000bfH
	push	OFFSET FLAT:??_C@_0CB@EKNB@c?3?2develop3?2common?2work?2intarr?4h@ ; `string'
	call	?AfxAssertFailedLine@@YGHPBDH@Z		; AfxAssertFailedLine
	test	eax, eax
	je	SHORT $L89462
	int	3
$L89462:
	xor	ecx, ecx
	test	ecx, ecx
	jne	SHORT $L89457

; 192  :  			return m_pData[nIndex]; }

	mov	edx, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR [edx+8]
	mov	ecx, DWORD PTR _nIndex$[ebp]
	mov	eax, DWORD PTR [eax+ecx*4]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 68					; 00000044H
	cmp	ebp, esp
	call	__chkesp
	mov	esp, ebp
	pop	ebp
	ret	4
?GetAt@CIntArr@@QBEHH@Z ENDP				; CIntArr::GetAt
_TEXT	ENDS
END
