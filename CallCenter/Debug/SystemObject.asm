; Listing generated by Microsoft (R) Optimizing Compiler Version 19.13.26131.1 

	TITLE	C:\Users\smith\Projects\CallCenter\SystemObject.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMTD
INCLUDELIB OLDNAMES

PUBLIC	?SystemKernel@CSystemObject@@1PAVCSystemKernel@@A ; CSystemObject::SystemKernel
_BSS	SEGMENT
?SystemKernel@CSystemObject@@1PAVCSystemKernel@@A DD 01H DUP (?) ; CSystemObject::SystemKernel
_BSS	ENDS
PUBLIC	?__empty_global_delete@@YAXPAX@Z		; __empty_global_delete
PUBLIC	?__empty_global_delete@@YAXPAXI@Z		; __empty_global_delete
PUBLIC	?PostSysMessage@CSystemObject@@IAEXEEGI@Z	; CSystemObject::PostSysMessage
PUBLIC	?PostSysMessageWI@CSystemObject@@IAEXKEEGI@Z	; CSystemObject::PostSysMessageWI
EXTRN	?PostSysMessage@CSystemKernel@@QAEXEEGI@Z:PROC	; CSystemKernel::PostSysMessage
EXTRN	?PostSysMessageWI@CSystemKernel@@QAEXKEEGI@Z:PROC ; CSystemKernel::PostSysMessageWI
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\systemobject.cpp
;	COMDAT ?PostSysMessageWI@CSystemObject@@IAEXKEEGI@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
_Interval$ = 8						; size = 4
_Command$ = 12						; size = 1
_SubCommand$ = 16					; size = 1
_data1$ = 20						; size = 2
_data2$ = 24						; size = 4
?PostSysMessageWI@CSystemObject@@IAEXKEEGI@Z PROC	; CSystemObject::PostSysMessageWI, COMDAT
; _this$ = ecx

; 21   : {

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

; 22   : 	SystemKernel->PostSysMessageWI(Interval, Command, SubCommand, data1, data2);

	mov	eax, DWORD PTR _data2$[ebp]
	push	eax
	movzx	ecx, WORD PTR _data1$[ebp]
	push	ecx
	movzx	edx, BYTE PTR _SubCommand$[ebp]
	push	edx
	movzx	eax, BYTE PTR _Command$[ebp]
	push	eax
	mov	ecx, DWORD PTR _Interval$[ebp]
	push	ecx
	mov	ecx, DWORD PTR ?SystemKernel@CSystemObject@@1PAVCSystemKernel@@A ; CSystemObject::SystemKernel
	call	?PostSysMessageWI@CSystemKernel@@QAEXKEEGI@Z ; CSystemKernel::PostSysMessageWI

; 23   : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	20					; 00000014H
?PostSysMessageWI@CSystemObject@@IAEXKEEGI@Z ENDP	; CSystemObject::PostSysMessageWI
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\systemobject.cpp
;	COMDAT ?PostSysMessage@CSystemObject@@IAEXEEGI@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
_Command$ = 8						; size = 1
_SubCommand$ = 12					; size = 1
_data1$ = 16						; size = 2
_data2$ = 20						; size = 4
?PostSysMessage@CSystemObject@@IAEXEEGI@Z PROC		; CSystemObject::PostSysMessage, COMDAT
; _this$ = ecx

; 16   : {

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

; 17   : 	SystemKernel->PostSysMessage(Command, SubCommand, data1, data2);

	mov	eax, DWORD PTR _data2$[ebp]
	push	eax
	movzx	ecx, WORD PTR _data1$[ebp]
	push	ecx
	movzx	edx, BYTE PTR _SubCommand$[ebp]
	push	edx
	movzx	eax, BYTE PTR _Command$[ebp]
	push	eax
	mov	ecx, DWORD PTR ?SystemKernel@CSystemObject@@1PAVCSystemKernel@@A ; CSystemObject::SystemKernel
	call	?PostSysMessage@CSystemKernel@@QAEXEEGI@Z ; CSystemKernel::PostSysMessage

; 18   : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	16					; 00000010H
?PostSysMessage@CSystemObject@@IAEXEEGI@Z ENDP		; CSystemObject::PostSysMessage
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\smith\projects\callcenter\systemobject.cpp
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
; File c:\users\smith\projects\callcenter\systemobject.cpp
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