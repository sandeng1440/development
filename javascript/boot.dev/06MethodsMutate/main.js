
const campaign = {
  name: "Welcome Campaign",
  maxMessages: 100,
  sentMessages: 30,
  sendMessage() {
    this.sentMessages += 1;
  },
};

// don't touch below this line

export { campaign };
