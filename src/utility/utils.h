#pragma once
#define swap_p(a, b) do {swap((void**)&(a), (void**)&(b));} while(0)
void swap(void** a, void** b);