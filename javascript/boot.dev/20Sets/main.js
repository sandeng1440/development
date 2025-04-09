function deduplicateEmails(emails) {
  return [...(new Set(emails))];
}

// don't touch below this line

export { deduplicateEmails };
