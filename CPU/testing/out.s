
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

Disassembly of section .plt:

0000000000401020 <write@plt-0x10>:
  401020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 403ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 403ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <write@plt>:
  401030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 404000 <write@GLIBC_2.2.5>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .text:

0000000000401040 <_start>:
  401040:	f3 0f 1e fa          	endbr64
  401044:	31 ed                	xor    %ebp,%ebp
  401046:	49 89 d1             	mov    %rdx,%r9
  401049:	5e                   	pop    %rsi
  40104a:	48 89 e2             	mov    %rsp,%rdx
  40104d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  401051:	50                   	push   %rax
  401052:	54                   	push   %rsp
  401053:	45 31 c0             	xor    %r8d,%r8d
  401056:	31 c9                	xor    %ecx,%ecx
  401058:	48 c7 c7 26 11 40 00 	mov    $0x401126,%rdi
  40105f:	ff 15 73 2f 00 00    	call   *0x2f73(%rip)        # 403fd8 <__libc_start_main@GLIBC_2.34>
  401065:	f4                   	hlt
  401066:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40106d:	00 00 00 

0000000000401070 <_dl_relocate_static_pie>:
  401070:	f3 0f 1e fa          	endbr64
  401074:	c3                   	ret
  401075:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40107c:	00 00 00 
  40107f:	90                   	nop

0000000000401080 <deregister_tm_clones>:
  401080:	b8 10 40 40 00       	mov    $0x404010,%eax
  401085:	48 3d 10 40 40 00    	cmp    $0x404010,%rax
  40108b:	74 13                	je     4010a0 <deregister_tm_clones+0x20>
  40108d:	b8 00 00 00 00       	mov    $0x0,%eax
  401092:	48 85 c0             	test   %rax,%rax
  401095:	74 09                	je     4010a0 <deregister_tm_clones+0x20>
  401097:	bf 10 40 40 00       	mov    $0x404010,%edi
  40109c:	ff e0                	jmp    *%rax
  40109e:	66 90                	xchg   %ax,%ax
  4010a0:	c3                   	ret
  4010a1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010a8:	00 00 00 00 
  4010ac:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004010b0 <register_tm_clones>:
  4010b0:	be 10 40 40 00       	mov    $0x404010,%esi
  4010b5:	48 81 ee 10 40 40 00 	sub    $0x404010,%rsi
  4010bc:	48 89 f0             	mov    %rsi,%rax
  4010bf:	48 c1 ee 3f          	shr    $0x3f,%rsi
  4010c3:	48 c1 f8 03          	sar    $0x3,%rax
  4010c7:	48 01 c6             	add    %rax,%rsi
  4010ca:	48 d1 fe             	sar    $1,%rsi
  4010cd:	74 11                	je     4010e0 <register_tm_clones+0x30>
  4010cf:	b8 00 00 00 00       	mov    $0x0,%eax
  4010d4:	48 85 c0             	test   %rax,%rax
  4010d7:	74 07                	je     4010e0 <register_tm_clones+0x30>
  4010d9:	bf 10 40 40 00       	mov    $0x404010,%edi
  4010de:	ff e0                	jmp    *%rax
  4010e0:	c3                   	ret
  4010e1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010e8:	00 00 00 00 
  4010ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004010f0 <__do_global_dtors_aux>:
  4010f0:	f3 0f 1e fa          	endbr64
  4010f4:	80 3d 11 2f 00 00 00 	cmpb   $0x0,0x2f11(%rip)        # 40400c <completed.0>
  4010fb:	75 13                	jne    401110 <__do_global_dtors_aux+0x20>
  4010fd:	55                   	push   %rbp
  4010fe:	48 89 e5             	mov    %rsp,%rbp
  401101:	e8 7a ff ff ff       	call   401080 <deregister_tm_clones>
  401106:	c6 05 ff 2e 00 00 01 	movb   $0x1,0x2eff(%rip)        # 40400c <completed.0>
  40110d:	5d                   	pop    %rbp
  40110e:	c3                   	ret
  40110f:	90                   	nop
  401110:	c3                   	ret
  401111:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401118:	00 00 00 00 
  40111c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401120 <frame_dummy>:
  401120:	f3 0f 1e fa          	endbr64
  401124:	eb 8a                	jmp    4010b0 <register_tm_clones>

0000000000401126 <main>:
  401126:	55                   	push   %rbp
  401127:	48 89 e5             	mov    %rsp,%rbp
  40112a:	48 83 ec 10          	sub    $0x10,%rsp
  40112e:	c7 45 fc 0a 00 00 00 	movl   $0xa,-0x4(%rbp)
  401135:	83 7d fc 0a          	cmpl   $0xa,-0x4(%rbp)
  401139:	75 04                	jne    40113f <main+0x19>
  40113b:	83 45 fc 05          	addl   $0x5,-0x4(%rbp)
  40113f:	48 c7 45 f0 10 20 40 	movq   $0x402010,-0x10(%rbp)
  401146:	00 
  401147:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  40114b:	ba 08 00 00 00       	mov    $0x8,%edx
  401150:	48 89 c6             	mov    %rax,%rsi
  401153:	bf 01 00 00 00       	mov    $0x1,%edi
  401158:	e8 d3 fe ff ff       	call   401030 <write@plt>
  40115d:	b8 00 00 00 00       	mov    $0x0,%eax
  401162:	c9                   	leave
  401163:	c3                   	ret

Disassembly of section .fini:

0000000000401164 <_fini>:
  401164:	f3 0f 1e fa          	endbr64
  401168:	48 83 ec 08          	sub    $0x8,%rsp
  40116c:	48 83 c4 08          	add    $0x8,%rsp
  401170:	c3                   	ret
