; Listing generated by Microsoft (R) Optimizing Compiler Version 19.13.26131.1 

	TITLE	C:\Users\smith\Projects\CallCenter\CallCenter.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMTD
INCLUDELIB OLDNAMES

PUBLIC	?CSK@@3PAVCSystemKernel@@A			; CSK
_BSS	SEGMENT
?CSK@@3PAVCSystemKernel@@A DD 01H DUP (?)		; CSK
_BSS	ENDS
PUBLIC	?__empty_global_delete@@YAXPAX@Z		; __empty_global_delete
PUBLIC	?__empty_global_delete@@YAXPAXI@Z		; __empty_global_delete
PUBLIC	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z		; CSysOut::operator<<
PUBLIC	??6CSysOut@@QAEAAV0@D@Z				; CSysOut::operator<<
PUBLIC	?flush@@YAAAVCSysOut@@AAV1@@Z			; flush
PUBLIC	?endl@@YAAAVCSysOut@@AAV1@@Z			; endl
PUBLIC	_main
PUBLIC	??_C@_0BD@DPIPMION@?$FL?$CK?$CK?$FN?5START?5service?$AA@ ; `string'
PUBLIC	??_C@_0BB@GFNMN@?$FL?$CK?$CK?$FN?5END?5service?$AA@ ; `string'
EXTRN	??2@YAPAXI@Z:PROC				; operator new
EXTRN	??3@YAXPAXI@Z:PROC				; operator delete
EXTRN	__imp__Sleep@4:PROC
EXTRN	?flush@CSysOut@@QAEAAV1@XZ:PROC			; CSysOut::flush
EXTRN	??6CSysOut@@QAEAAV0@PBD@Z:PROC			; CSysOut::operator<<
EXTRN	??6CSysOut@@QAEAAV0@E@Z:PROC			; CSysOut::operator<<
EXTRN	?time@@YAAAVCSysOut@@AAV1@@Z:PROC		; time
EXTRN	?Resume@CThread@@QAEXXZ:PROC			; CThread::Resume
EXTRN	??0CSystemKernel@@QAE@_N@Z:PROC			; CSystemKernel::CSystemKernel
EXTRN	@__security_check_cookie@4:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	___CxxFrameHandler3:PROC
EXTRN	?FLOG@@3VCSysOut@@A:BYTE			; FLOG
EXTRN	___security_cookie:DWORD
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
;	COMDAT ??_C@_0BB@GFNMN@?$FL?$CK?$CK?$FN?5END?5service?$AA@
CONST	SEGMENT
??_C@_0BB@GFNMN@?$FL?$CK?$CK?$FN?5END?5service?$AA@ DB '[**] END service', 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0BD@DPIPMION@?$FL?$CK?$CK?$FN?5START?5service?$AA@
CONST	SEGMENT
??_C@_0BD@DPIPMION@?$FL?$CK?$CK?$FN?5START?5service?$AA@ DB '[**] START s'
	DB	'ervice', 00H				; `string'
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__unwindtable$_main DD 0ffffffffH
	DD	FLAT:__unwindfunclet$_main$0
__ehfuncinfo$_main DD 019930522H
	DD	01H
	DD	FLAT:__unwindtable$_main
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	DD	00H
	DD	01H
xdata$x	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\callcenter.cpp
;	COMDAT _main
_TEXT	SEGMENT
tv84 = -232						; size = 4
$T2 = -224						; size = 4
$T3 = -212						; size = 4
__$EHRec$ = -12						; size = 12
_argc$ = 8						; size = 4
_argv$ = 12						; size = 4
_main	PROC						; COMDAT

; 13   : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$_main
	mov	eax, DWORD PTR fs:0
	push	eax
	sub	esp, 220				; 000000dcH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-232]
	mov	ecx, 55					; 00000037H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	push	eax
	lea	eax, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, eax

; 14   : 	FLOG << time << "[**] START service" << endl;

	push	OFFSET ?endl@@YAAAVCSysOut@@AAV1@@Z	; endl
	push	OFFSET ??_C@_0BD@DPIPMION@?$FL?$CK?$CK?$FN?5START?5service?$AA@
	push	OFFSET ?time@@YAAAVCSysOut@@AAV1@@Z	; time
	mov	ecx, OFFSET ?FLOG@@3VCSysOut@@A		; FLOG
	call	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z	; CSysOut::operator<<
	mov	ecx, eax
	call	??6CSysOut@@QAEAAV0@PBD@Z		; CSysOut::operator<<
	mov	ecx, eax
	call	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z	; CSysOut::operator<<

; 15   : 
; 16   : 	CSK = new CSystemKernel(true);

	push	69184					; 00010e40H
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2[ebp], eax
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	cmp	DWORD PTR $T2[ebp], 0
	je	SHORT $LN6@main
	push	1
	mov	ecx, DWORD PTR $T2[ebp]
	call	??0CSystemKernel@@QAE@_N@Z		; CSystemKernel::CSystemKernel
	mov	DWORD PTR tv84[ebp], eax
	jmp	SHORT $LN7@main
$LN6@main:
	mov	DWORD PTR tv84[ebp], 0
$LN7@main:
	mov	eax, DWORD PTR tv84[ebp]
	mov	DWORD PTR $T3[ebp], eax
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	mov	ecx, DWORD PTR $T3[ebp]
	mov	DWORD PTR ?CSK@@3PAVCSystemKernel@@A, ecx ; CSK

; 17   : 	
; 18   : 	Sleep(500);

	mov	esi, esp
	push	500					; 000001f4H
	call	DWORD PTR __imp__Sleep@4
	cmp	esi, esp
	call	__RTC_CheckEsp

; 19   : 	CSK->Resume();

	mov	ecx, DWORD PTR ?CSK@@3PAVCSystemKernel@@A ; CSK
	call	?Resume@CThread@@QAEXXZ			; CThread::Resume
$LN4@main:

; 20   : 
; 21   : 	for (;/*!kbhit()*/;) Sleep(10000);

	mov	esi, esp
	push	10000					; 00002710H
	call	DWORD PTR __imp__Sleep@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	jmp	SHORT $LN4@main

; 22   : 
; 23   : 	FLOG << time << "[**] END service" << endl;

	push	OFFSET ?endl@@YAAAVCSysOut@@AAV1@@Z	; endl
	push	OFFSET ??_C@_0BB@GFNMN@?$FL?$CK?$CK?$FN?5END?5service?$AA@
	push	OFFSET ?time@@YAAAVCSysOut@@AAV1@@Z	; time
	mov	ecx, OFFSET ?FLOG@@3VCSysOut@@A		; FLOG
	call	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z	; CSysOut::operator<<
	mov	ecx, eax
	call	??6CSysOut@@QAEAAV0@PBD@Z		; CSysOut::operator<<
	mov	ecx, eax
	call	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z	; CSysOut::operator<<

; 24   : 
; 25   : 	return 0;

	xor	eax, eax

; 26   : }

	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, ecx
	pop	ecx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 232				; 000000e8H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$_main$0:
	push	69184					; 00010e40H
	mov	eax, DWORD PTR $T2[ebp]
	push	eax
	call	??3@YAXPAXI@Z				; operator delete
	add	esp, 8
	ret	0
__ehhandler$_main:
	mov	edx, DWORD PTR [esp+8]
	lea	eax, DWORD PTR [edx+12]
	mov	ecx, DWORD PTR [edx-236]
	xor	ecx, eax
	call	@__security_check_cookie@4
	mov	eax, OFFSET __ehfuncinfo$_main
	jmp	___CxxFrameHandler3
text$x	ENDS
_main	ENDP
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\sysout.h
;	COMDAT ?endl@@YAAAVCSysOut@@AAV1@@Z
_TEXT	SEGMENT
__outs$ = 8						; size = 4
?endl@@YAAAVCSysOut@@AAV1@@Z PROC			; endl, COMDAT

; 59   : inline CSysOut& __cdecl endl(CSysOut& _outs) { return _outs << '\n' << flush; }

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	push	OFFSET ?flush@@YAAAVCSysOut@@AAV1@@Z	; flush
	push	10					; 0000000aH
	mov	ecx, DWORD PTR __outs$[ebp]
	call	??6CSysOut@@QAEAAV0@D@Z			; CSysOut::operator<<
	mov	ecx, eax
	call	??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z	; CSysOut::operator<<
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?endl@@YAAAVCSysOut@@AAV1@@Z ENDP			; endl
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\sysout.h
;	COMDAT ?flush@@YAAAVCSysOut@@AAV1@@Z
_TEXT	SEGMENT
__outs$ = 8						; size = 4
?flush@@YAAAVCSysOut@@AAV1@@Z PROC			; flush, COMDAT

; 58   : inline CSysOut& __cdecl flush(CSysOut& _outs) { return _outs.flush(); }

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, DWORD PTR __outs$[ebp]
	call	?flush@CSysOut@@QAEAAV1@XZ		; CSysOut::flush
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?flush@@YAAAVCSysOut@@AAV1@@Z ENDP			; flush
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\sysout.h
;	COMDAT ??6CSysOut@@QAEAAV0@D@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
__c$ = 8						; size = 1
??6CSysOut@@QAEAAV0@D@Z PROC				; CSysOut::operator<<, COMDAT
; _this$ = ecx

; 52   : inline  CSysOut& CSysOut::operator<<(char _c) { return operator<<((unsigned char) _c); }

	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	movzx	eax, BYTE PTR __c$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	call	??6CSysOut@@QAEAAV0@E@Z			; CSysOut::operator<<
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
??6CSysOut@@QAEAAV0@D@Z ENDP				; CSysOut::operator<<
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\sysout.h
;	COMDAT ??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
__f$ = 8						; size = 4
??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z PROC		; CSysOut::operator<<, COMDAT
; _this$ = ecx

; 49   : inline CSysOut& CSysOut::operator<<(CSysOut& (__cdecl * _f)(CSysOut&)) { (*_f)(*this); return *this; }

	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	push	eax
	call	DWORD PTR __f$[ebp]
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
??6CSysOut@@QAEAAV0@P6AAAV0@AAV0@@Z@Z ENDP		; CSysOut::operator<<
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\callcenter.cpp
;	COMDAT ?__empty_global_delete@@YAXPAXI@Z
_TEXT	SEGMENT
___formal$ = 8						; size = 4
___formal$ = 12						; size = 4
?__empty_global_delete@@YAXPAXI@Z PROC			; __empty_global_delete, COMDAT

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?__empty_global_delete@@YAXPAXI@Z ENDP			; __empty_global_delete
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\callcenter.cpp
;	COMDAT ?__empty_global_delete@@YAXPAX@Z
_TEXT	SEGMENT
___formal$ = 8						; size = 4
?__empty_global_delete@@YAXPAX@Z PROC			; __empty_global_delete, COMDAT

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?__empty_global_delete@@YAXPAX@Z ENDP			; __empty_global_delete
_TEXT	ENDS
END
