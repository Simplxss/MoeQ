# MoeQ

It is a QQ robot based on Android QQ 8.4.1.

Because of busy school,I can't continue updata this project on my own,so I public it.


**Wish you can make it better!**


# Achieved


##Protocol

1.Log in and sign out.

2.Get friends and groups list.

2.Receive some group messages and private messages.

3.Send part of group messages and private messages.

4.Draw group message.

5.Do some friend and group actions

...


##Plugin System

1.Enadle and Disable.

2.Right control.

3.[C++ sdk](https://github.com/YuFanXing/mqcppsdk).

...


#Todo List

1.Some memory leak.

2.Support image message and voice message.

3.Fix bugs.

4.Upadta protocol version.

6.Plugin Management.

//7.Plugin store.

...


#Program Life cycle

```flow
st=>start: Program Start
op1=>operation: Initialization(Load Configure and Plugins,Draw UI)
op2=>operation: Log in
sub1=>subroutine: Connect Tencent Service
sub2=>subroutine: Send wtlogin.login
op3=>operation: Heat beat
sub3=>subroutine: Send StatSvc.Register
op4=>operation: sign out
op5=>operation: Unload Plugin
e=>end: Program Exit
st->op1->op2->sub1(right)->sub2(right)->op3->sub3(right)->op4->sub3(right)->op5>e
```