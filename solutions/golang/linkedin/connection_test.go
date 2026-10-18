package linkedin
import ("testing"; "sync"; "fmt")
func TestDemonstratedConnectionFlow(t *testing.T) {
 s:=GetLinkedInService(); a:=NewUser("a","A","a@example.com","p");b:=NewUser("b","B","b@example.com","p")
 s.RegisterUser(a);s.RegisterUser(b);s.SendConnectionRequest(a,b)
 if len(a.connections)!=0 || len(b.connections)!=0 {t.Fatal("request exposed as connection")}
 s.AcceptConnectionRequest(b,a)
 if len(a.connections)!=1 || len(b.connections)!=1 {t.Fatal("acceptance not symmetric")}
}
func TestConcurrentRegistrationAndJobListing(t *testing.T) {
 s:=GetLinkedInService(); var wg sync.WaitGroup
 for i:=0;i<100;i++ {wg.Add(2); go func(i int){defer wg.Done();s.RegisterUser(NewUser(fmt.Sprint(i),"User","u@example.com","p"))}(i);go func(i int){defer wg.Done();s.PostJobListing(&JobPosting{ID:fmt.Sprint(i),Title:"Job"})}(i)}
 wg.Wait()
}
