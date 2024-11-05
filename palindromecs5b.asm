data SEGMENT
    msg1 db 10,13,'enter the string:$'
    msg2 db 10,13,'string is palindrome$'
    msg3 db 10,13,'string is not palindrome$'
    str1 db 50 dup(0)
data ENDS
code SEGMENT
ASSUME CS:code,ds:data
start:
    mov ax,data
    mov ds,ax
    lea dx,msg1
    mov ah,09h
    int 21h
    
    lea si,str1
    lea di,str1
    mov ah,01h
    
next:
    int 21h
    cmp al,0Dh
    je terminate
    mov [di],al
    inc di
    jmp next
terminate:
    mov al,'$'
    mov [di],al
dothis:
    dec di
    mov al,[si] 
    cmp [di],al
    jne notpalindrome
    inc si
    cmp si,di
    jl dothis
palindrome:   
    mov ah,09h   
    lea dx,msg2
    int 21h
    jmp xx
notpalindrome:
    mov ah,09h
    lea dx,msg3
    int 21h
xx:
    mov ah,4ch
    int 21h   
    
code ENDS 
end START