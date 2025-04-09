function createUserMap(users) {
  let m = new Map();
  for (let i = 0; i < users.length; ++i) {
    const user = users[i];
    const key = `${user["fname"]} ${user["lname"]}`;
    m.set(key, user);
  }
  return m;
}

export { createUserMap };
