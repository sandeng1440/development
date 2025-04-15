function fixUserMap(brokenMap) {
  const newMap = new Map();
  for (const [_, v] of brokenMap) {
    newMap.set(`${v.fname} ${v.lname}`, v);
  }
  return newMap;
}

export { fixUserMap };
