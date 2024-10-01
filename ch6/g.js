const VPN_MASK = 0xfffffffffffff000;

const x = 10;
const VPN = (x & VPN_MASK) >> 12;
console.log("hello");
console.log(VPN);
