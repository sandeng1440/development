// The bracket notation is used to access keys using strings.
const desk = {
  wood: "maple",
  width: 100,
};

console.log(desk.wood);
// prints "maple"

console.log(desk["wood"]);
// also prints "maple"

const key = "wood";
console.log(desk[key]);
// also prints "maple"
