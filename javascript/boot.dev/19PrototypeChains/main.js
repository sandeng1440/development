const user = {
  name: "Default User",
  type: "user",
};

const adminUser = Object.create(user);
adminUser.type = "admin";

function isAdmin(obj) {
  return obj.__proto__ === adminUser;
}

// don't touch below this line

export { user, adminUser, isAdmin };
