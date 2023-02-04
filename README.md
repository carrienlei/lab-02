# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- Carrie Lei
- Ishraq Rahman

## Lab Question Answers

Answer for Question 1: 
- After adding 50% loss to our local environment, we noticed a decrease in reliability of the UDP server. It did not receive all of the sequence that was sent by the client. This likely occurs due to the fact that UDP does not require connections to fully transfer information, making it less reliable. 

Answer for Question 2:
- We noticed there wasn't a change in reliability in the TCP connection since the server successfully received all the info from the client. This is because TCP has a protocol that waits and ensures all transmitted information is received by the server, making it more reliable.

Answer for Question 3:
- After adding 50% loss to our local environment, the TCP response speed was slightly slower. This may have occured because the client takes more time to retransfer the lost packages that weren't initially sent. 
