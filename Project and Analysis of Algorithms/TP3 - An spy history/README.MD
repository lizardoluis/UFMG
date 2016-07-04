# TP3 - An spy history

You are a spy and your job is to intercept communications within the network of the center of operations. Your objective is to detect the control commands that enable and disable the devices that control oil production in the country.

You possess the ability to place an attack of the type ’man in the middle’ in which you will have access to the direct transmission of bits (0 and 1). However, you will have the hard task of decoding the captured flow of bits to discover the content of the messages. Fortunately, you have the collaboration of a great team of spies and they have already discovered that there are 2 control commands in the flow of bits. They are the sequence of bits "000" and "11111". This
information is important because you will focus on decoding the bits that appear between these control commands.

By analyzing the first captured data, you observed the occurrence of many transmission errors, despite the high quality of the spying devices that you used to capture the messages. Those errors prevent you from identifying if some bits are ’0’ or ’1’. Thus, your problem now is to construct a program that receives a string of bits and returns if it has a control command, it does not have a control command or it is impossible to define if the string has a control command. 

This problem must be solved using three different programming paradigms: brute force strategy (bf ), dynamic programming (db) and greedy algorithm (ga).
