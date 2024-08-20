
test:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64
  401004:	48 83 ec 08          	sub    $0x8,%rsp
  401008:	48 8b 05 d1 2f 00 00 	mov    0x2fd1(%rip),%rax        # 403fe0 <__gmon_start__@Base>
  40100f:	48 85 c0             	test   %rax,%rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	call   *%rax
  401016:	48 83 c4 08          	add    $0x8,%rsp
  40101a:	c3                   	ret

Disassembly of section .text:

0000000000401020 <_start>:
  401020:	f3 0f 1e fa          	endbr64
  401024:	31 ed                	xor    %ebp,%ebp
  401026:	49 89 d1             	mov    %rdx,%r9
  401029:	5e                   	pop    %rsi
  40102a:	48 89 e2             	mov    %rsp,%rdx
  40102d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  401031:	50                   	push   %rax
  401032:	54                   	push   %rsp
  401033:	45 31 c0             	xor    %r8d,%r8d
  401036:	31 c9                	xor    %ecx,%ecx
  401038:	48 c7 c7 06 11 40 00 	mov    $0x401106,%rdi
  40103f:	ff 15 93 2f 00 00    	call   *0x2f93(%rip)        # 403fd8 <__libc_start_main@GLIBC_2.34>
  401045:	f4                   	hlt
  401046:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40104d:	00 00 00 

0000000000401050 <_dl_relocate_static_pie>:
  401050:	f3 0f 1e fa          	endbr64
  401054:	c3                   	ret
  401055:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40105c:	00 00 00 
  40105f:	90                   	nop

0000000000401060 <deregister_tm_clones>:
  401060:	b8 08 40 40 00       	mov    $0x404008,%eax
  401065:	48 3d 08 40 40 00    	cmp    $0x404008,%rax
  40106b:	74 13                	je     401080 <deregister_tm_clones+0x20>
  40106d:	b8 00 00 00 00       	mov    $0x0,%eax
  401072:	48 85 c0             	test   %rax,%rax
  401075:	74 09                	je     401080 <deregister_tm_clones+0x20>
  401077:	bf 08 40 40 00       	mov    $0x404008,%edi
  40107c:	ff e0                	jmp    *%rax
  40107e:	66 90                	xchg   %ax,%ax
  401080:	c3                   	ret
  401081:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401088:	00 00 00 00 
  40108c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401090 <register_tm_clones>:
  401090:	be 08 40 40 00       	mov    $0x404008,%esi
  401095:	48 81 ee 08 40 40 00 	sub    $0x404008,%rsi
  40109c:	48 89 f0             	mov    %rsi,%rax
  40109f:	48 c1 ee 3f          	shr    $0x3f,%rsi
  4010a3:	48 c1 f8 03          	sar    $0x3,%rax
  4010a7:	48 01 c6             	add    %rax,%rsi
  4010aa:	48 d1 fe             	sar    $1,%rsi
  4010ad:	74 11                	je     4010c0 <register_tm_clones+0x30>
  4010af:	b8 00 00 00 00       	mov    $0x0,%eax
  4010b4:	48 85 c0             	test   %rax,%rax
  4010b7:	74 07                	je     4010c0 <register_tm_clones+0x30>
  4010b9:	bf 08 40 40 00       	mov    $0x404008,%edi
  4010be:	ff e0                	jmp    *%rax
  4010c0:	c3                   	ret
  4010c1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010c8:	00 00 00 00 
  4010cc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004010d0 <__do_global_dtors_aux>:
  4010d0:	f3 0f 1e fa          	endbr64
  4010d4:	80 3d 29 2f 00 00 00 	cmpb   $0x0,0x2f29(%rip)        # 404004 <completed.0>
  4010db:	75 13                	jne    4010f0 <__do_global_dtors_aux+0x20>
  4010dd:	55                   	push   %rbp
  4010de:	48 89 e5             	mov    %rsp,%rbp
  4010e1:	e8 7a ff ff ff       	call   401060 <deregister_tm_clones>
  4010e6:	c6 05 17 2f 00 00 01 	movb   $0x1,0x2f17(%rip)        # 404004 <completed.0>
  4010ed:	5d                   	pop    %rbp
  4010ee:	c3                   	ret
  4010ef:	90                   	nop
  4010f0:	c3                   	ret
  4010f1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010f8:	00 00 00 00 
  4010fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401100 <frame_dummy>:
  401100:	f3 0f 1e fa          	endbr64
  401104:	eb 8a                	jmp    401090 <register_tm_clones>

0000000000401106 <main>:
  401106:	55                   	push   %rbp
  401107:	48 89 e5             	mov    %rsp,%rbp
  40110a:	c7 45 fc 04 00 00 00 	movl   $0x4,-0x4(%rbp)
  401111:	b8 00 00 00 00       	mov    $0x0,%eax
  401116:	5d                   	pop    %rbp
  401117:	c3                   	ret

Disassembly of section .fini:

0000000000401118 <_fini>:
  401118:	f3 0f 1e fa          	endbr64
  40111c:	48 83 ec 08          	sub    $0x8,%rsp
  401120:	48 83 c4 08          	add    $0x8,%rsp
  401124:	c3                   	ret
