package non_thread_safe

import "testing"

func TestCounterInstanceNotNull(t *testing.T) {
	counter1 := GetInstance()

	if counter1 == nil {
		t.Error("expeceted non-nil counter after calling GetInstance()")
	}
}

func TestCounterOnlySingleInstance(t *testing.T) {
	counter1 := GetInstance()
	if counter1 == nil {
		t.Error("expeceted nil counter after calling GetInstance()")
	}
	counter2 := GetInstance()
	if counter2 != counter1 {
		t.Error("expeceted only one instance to get created but there are more than 2")
	}
}
