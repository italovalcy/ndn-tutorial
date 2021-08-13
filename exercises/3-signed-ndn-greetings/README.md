# NDN-Greetings: Secure/Signed NDN Application

## Introduction

In this exercise, we will be using NDN-CXX API to create an application
to mimic the way people say Greetings in English. We will build our application
on top of the same structure that you used in the 
[NDN Helloworld](../1b-ndn_helloworld) exercise. The main difference is that
now we are building a more robust NDN application and each NDN node running
our application will act as a consumer and producer at the same time.

It is important to remember the way we are modeling English Greetings between
two or more entities:

.. image:: ../../images/greetings-diagram.png

In summary, usually it starts by someone introducing herself/himself, like:
A) _Hi, I am Foobar_. Then, whoever hears from A will greet in reply: B) 
_Hey, A!_. Moving forward, A will send a greetings back to B:
_How are you doing?_.

On our NDN Greetings application, the workflow will be pretty similar to
the one previously presented. More specifically, consider two NDN nodes
A and B. The NDN Greetings application will behaves like the following
workflow diagram:

.. image:: ../../images/ndn-greetings-diagram.png

In the above diagram, NodeA will send a hello message to introduce
itself so any reachable node will know about NodeA existence. This is
done through an Interest packet. Whoever receives the hello interest
from NodeA, will send a greetings interest using the naming schema
learned from the hello interest. Finally, NodeA will reply the
greetings interest with a greetings data. Since English has many ways
to say greetings, a random answer will be chosen. It is worthy to note
that NodeB will follow the same work flow as NodeA: NodeB will send a 
hello interest; NodeA will send a greetings interest upon receiving 
the hello interest from NodeB; NodeB will answer with a greetings data.

Let's get started!

> **Spoiler alert:** There is a reference solution in the `solution`
> sub-directory. Feel free to compare your implementation to the
> reference.

## Step 1: Loading the Data Validator Config

TODO 1

## Step 2: Call validator upon receiving data packets

TODO 2

## Step 3: Enable node Key distribution

TODO 3 and 4

## Next Steps

Congratulations, your implementation works! Move onto the next assignment
[Signed NDN-Greetings](../3-signed-ndn-greetings)!
