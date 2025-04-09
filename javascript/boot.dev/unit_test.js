
// unit_test.js

export const assert = {
  strictEqual(actual, expected, message) {
    if (actual !== expected) {
      throw new Error(`Assertion Failed: ${message}`);
    }
  },
  deepEqual(actual, expected, message) {
    if (actual.length != expected.length) {
      throw new Error(`Assertion Failed: ${message}`);
    }
    let a = [...actual];
    let b = [...expected];
    if (Array.isArray(a[0]) || Array.isArray(b[0])) {
      for (let i = 0; i < a.length; ++i) {
        for (let j = 0; j < a[i].length; ++j) {
          if (a[i][j] != b[i][j]) {
            throw new Error(`Assertion Failed: ${message}`)
          }
        }
      }
    } else {
      a.sort();
      b.sort();
      for (let i = 0; i < a.length; ++i) {
        if (a[i] != b[i]) {
          throw new Error(`Assertion Failed: ${message}`);
        }
      }
    }
  },
};

export function describe(name, fn) {
  console.log(`\n[TEST SUITE] ${name}`);
  try {
    fn();
  } catch (error) {
    console.error(error);
  }
}

export function it(name, fn) {
  try {
    fn();
    console.log(`✔ PASS: ${name}`);
  } catch (error) {
    console.error(`✖ FAIL: ${name}`);
    console.error(error.message);
  }
}

// Simulating the 'withSubmit' feature
export const withSubmit = true;
