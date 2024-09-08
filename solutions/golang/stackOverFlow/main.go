package main

import "fmt"

func main() {
	system := NewStackOverFlow()

	u1 := NewUser("mukul", "mukul@example.com")
	u2 := NewUser("harsh", "harsh@example.com")
	u3 := NewUser("shivam", "shivam@example.com")
	u4 := NewUser("apoorv", "apoorv@example.com")

	// mukul is asking a question
	ques := system.PostQuestion(u1, "Java vs Golang", "in case of low latency which language is better java or golang",
		[]string{"golang", "java"})

	//harsh answers the question
	ans := ques.PostAnswer(u2, "Golang is better than java", "When it comes to low latency golang is the better choice as it is lightweight.")

	//shivam adds a comment on the question
	ques.PostComment(u3, "Also which is more developer friendly?")

	//harsh comments on his answer to address shivam's comment
	ans.PostComment(u2, "In terms of the code footprint, golang is a little more complex as it does not have native library support like Java")

	//shivam up votes mukul's question
	ques.AddVote(u3, 1)

	//mukul up votes harsh's answer
	ans.AddVote(u1, 1)

	//apoorv down votes harsh's answer
	ans.AddVote(u4, -1)

	// apoorv asks a question
	ques2 := system.PostQuestion(u4, "How to implement singleton in golang", "In golang how to make use of the sync package to implement singleton",
		[]string{"golang", "singleton"})

	ques2.AddVote(u1, 1)

	//get questions by tag
	result := system.GetQuestionsByTags([]string{"singleton", "golang"})

	fmt.Printf("%d\n", len(result))

}
