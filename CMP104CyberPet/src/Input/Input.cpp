#include "Input.h"

// instantiate the input api object
// even though this is the only line of code in this cpp file,
// it's essential this is in its own file to guarentee that it only
// ever gets executed once
InputAPI* Input::s_InputAPI = new InputAPI();
