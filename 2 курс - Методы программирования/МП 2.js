var massive = [54, 62, 7, 33, 28, 22, 1, 678, 234, 9];
console.log('Массив до сортировки: ', massive);
function partition(massive, left, right) {
    var pivot = massive[Math.floor((right + left) / 2)],
        i = left,
        j = right;
    while (i <= j) {
        while (massive[i] < pivot) {
            i++;
        }
        while (massive[j] > pivot) {
            j--;
        }
        if (i <= j) {
	    const temp = massive[i];
  	    massive[i] = massive[j];
   	    massive[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
function sort(massive, left, right) {
    var i;
    if (massive.length > 1) {
        left = typeof left != "number" ? 0 : left;
        right = typeof right != "number" ? massive.length - 1 : right;
        i = partition(massive, left, right);
        if (left < i - 1) {
            sort(massive, left, i - 1);
        }
        if (i < right) {
            sort(massive, i, right);
        }
    }
    return massive;
}
var result = sort(massive);
console.log('Массив после сортировки: ',result);






console.log('Сортировка Шелла')
let countShell = 0,
notSorted = [3,2,5,1,44,13,55,1,0,48,54,3,99,47,13,101];
console.log('Неотсортированный массив:  ', notSorted)
function shellSort(array)
{
  for (let step = Math.floor(array.length / 2); step>0; step=Math.floor(step / 2))
  {
    for(let pass = step; pass< array.length; pass++)
    {
      for(let replacment = pass - step; replacment >= 0 &&  array[replacment] > array[replacment + step]; replacment -= step)
      {
        let tmp = array[replacment];
        array[replacment] = array[replacment + step];   
        array[replacment + step] = tmp;
        countShell++;
      }
    }
  }
  return array;
}
console.log('Отсортированный массив:  ', shellSort(notSorted))