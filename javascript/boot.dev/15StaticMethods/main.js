class Message {
  static totalMessages = 0;
  static totalMessageLengths = 0;
  static getAverageMessageLength() {
    const avg = this.totalMessageLengths / this.totalMessages;
    return Math.round(avg * 100) / 100;
  }
  constructor(recipient, sender, body) {
    this.recipient = recipient;
    this.sender = sender;
    this.body = body;
    Message.totalMessages++;
    Message.totalMessageLengths += body.length;
  }
}

// don't touch below this line

export { Message };
