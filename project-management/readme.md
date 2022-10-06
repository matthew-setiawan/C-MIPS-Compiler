Project Organization Introduction

Pre-Development Research

Research a series of MIPS flags (necessary for developing software and debug purposes, inserting hashtags are good as comments etc) https://dev.to/omaremaradev/guide-to-writing-compiling-and-running-mips-binaries-on-linux-55n1
Research the grammar and lexer format that we need to incorporate when building and overall C->MIPS compiler.
Use godbolt as a reference compiler to test basic instructions.
CONFIGURE MATTHEW's work environment
Based on the specific workflow requirements and needs when developing technical projects we decided to adopt a more Agile-Scrum approach for completing the project as opposed to setting rigid targets and deadlines defined by GANTT charts or in other WATERFALL developments. As Matthew and I were already acquainted before the project the primary form of communication was through Whatsapp (and occasionally teams) where which we would use to update each other and progress and merge and sync our changes. Having solid communication is key for the project and we sometimes needed to message each other and update each other when working past midnight and it is good that we could do this. We chose not to define a GANTT chart for this project as it would hinder our adaptability and changes rather than being fully helping us.

A diagram summarizing our workflow and series of sprints is provided as well as pictures included (showing how we communicated over the course of the project).

First Sprint: Build a Basic Compiler only Working for Integers (02/03) Targets: (1 week aim and objective) - if time permits complete sprint 2.

1.Make the relevant bash scripts and make files necessary to implement testing of the compiler

2.Implement the relevant necessary ANSI C grammar and develop a lexer and parser according to the structure of ANSI C grammar.

3.Develop relevant header files to enable stack assignment and frame assigment on the compiler side implementation.

4.Develop function opening and close for simple functions w/o call operations.

5 Implement the subsection of code needed for basic integer operands such as ADD,SUBTRAC, DIVIDE and MULTIPLY.

6 Test the implementation using bash scripts.

Second Sprint: Developing Default testcases and Expanding the Scope of Integer Operations

In this phase the primary objective was to expand the scope of the compiler enabling us to handle default testcases as well as other operands. (09/03) Targets and objectives:

Implement features to complete the integer folders, excluding logical AND as well as logical OR operation.

Implement function returns for default operations as well as sequence operations.

Expand the grammar to work with the given set of functions.

Update Matthew (11/03) this works now, after severe amount of debugging and figuring out the relevant stacks.

Third Sprint: Develop the feature set for doubles and control flow logic new plan

Here, James was assigned the control flow folder to debug and develop logic for the set of operands while Matthew went to work on expanding the scope of the compiler for float and doubles (13/03)

Develop logic for hadnling conditional operands using as a base reference what had previously been learnt during lab3 of the codegen phase. -Target: Develop If, Else If Logic prior to working on the development of While loop Operands.
Develop for loop logic from here, as no base reference.
Expand the scope of the structure to enable float and double operations to be included in the compiler. Expand gerammar to work with these features.

Merge and sync changes.

Here, we noticed how there were also deadlines for our course including;

a. Communications Laboratory.

b. Control Laboratory

c. Information Processing Coursework

Hence, we decided to only work on developing these features and not plan the next sprint for implementation until the week later. (19/22) James reporting for both Me+Matthew. This segment has been succesfully implemented and now phase 4 and sprint 4-5 can be planned.

Fourth Sprint: Develop Function Calls as well as Debug / Implement other test cases (19/03)

Note: Scheduled flight on 27/03 so need to complete tasks before then evening. Deadlines for work are communications - 25/03 (James), 24/03 (Matthew), info-processing 28/03, control -25.03 in addition to James flying on 27/03. Hence, we set an aim to accomplish most tasks prior to 27/03.

Matthew here set out to develop function calls and this logic while James Worked on Arrays

Achieve function call statements and work on developing testcases for all function calls
First develop the function call operations without recursion
Develop function call operands with recursion.
Develop a working testcase folder for arrrays
First worked on developing a way and method to define arrays as well as call operands on arrays
Work on developing the miscellaneous folder and debugging previously unsolved testcases.
First implement ENUM then develop switch, enum etc.
Work on devleoping the pointer and stack operations.
Update (24/03/22) Arrays work, Regex defined for single string which passes.
