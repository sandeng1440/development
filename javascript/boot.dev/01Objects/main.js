function createMessage(phoneNumber, message) {
  return {phoneNumber, message, messageLength: message.length};
}

export { createMessage };
