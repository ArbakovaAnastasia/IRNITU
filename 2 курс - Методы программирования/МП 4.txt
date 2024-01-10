function createFib(a, b) {
  let [x, y] = [a, b];
  return function () {
    y = x + y;
    x = y - x;
    console.log(y);
  }
}
function createRandom() {
  const uniqArr = [];
  return function () {
    let elem = false;
    if (uniqArr.length < 11) {
      do {
        elem = Math.floor(Math.random() * (10 + 1));
      } while (uniqArr.includes(elem));
      uniqArr.push(elem);
    }
    console.log(elem);
  }
}
console.log("Задание 1:");
fibA = createFib(1, 1)
fibA() // = 2
fibA() // = 3
fibB = createFib(0, 2)
fibB() // = 2
fibB() // = 4
fibB() // = 6
console.log("Задание 2:");
rnd = createRandom()
rnd() // = 1
rnd() // = 2
rnd() // = 3
rnd() // = 4
rnd() // = 5
rnd() // = 6
rnd() // = 7
rnd() // = 8
rnd() // = 9
rnd() // = 10
rnd() // =  – это был 11-й вызов
rnd() // = false