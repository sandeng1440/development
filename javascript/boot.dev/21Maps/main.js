function addToPhonebook(phoneNumber, name, phoneBook) {
  const pb = new Map(phoneBook);
  pb.set(phoneNumber, name);
  return pb;
}

// don't touch below this line

export { addToPhonebook };
