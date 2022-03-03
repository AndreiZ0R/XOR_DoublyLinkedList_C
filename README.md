<h1 align="center">XOR Doubly Linked list</h1>
<br>

- Okay, so what exactly is an XOR Doubly Linked List?

<h3 align = "left"> Well, first let's understand what a Doubly Linked List is, and what is XOR </h3>
<br>

- A doubly linked list is a list with references both to the next and the previous element, making it easier to insert at the beggining and at the end of the list in **O(1)**

- Bitwise XOR(exclusive-or) operation is one of the fundamental ones, also usually called the **odd ones detector**. Let's figure out why: <br>
0 XOR 0 = 0<br>
0 XOR 1 = 1<br>
1 XOR 0 = 1<br>
1 XOR 1 = 0<br>
And that's all you need to know about it for now. <br>

<h3 align = "left"> So how does this work? </h3>
- Well, this list has a special property:<pre>previous XOR next = stocked value
stocked value XOR previous = next
stocked value XOR next = previous 
</pre>

- So, keeping this in mind, we now understand how to create the links between the elements.

<h2 align = "left"> How to run the file </h2>
- Download the repository to your local machine, then open it with your favorite text editor/ IDE<br> 
- Then, the main file is named "DLLxorTester.c" <<-- _that's the file you want to run_ <br>
- The rest is up to you!
