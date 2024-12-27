import {renderOrderSummary} from "./checkout/orderSummary.js";
import {renderPaymentSummary} from "./checkout/paymentSummary.js";
import {loadProducts, loadProductsFetch} from "../data/products.js";
import {loadCart} from "../data/cart.js";
//import '../data/cart-class.js';
//import '../data/backend-practice.js';

//"async" wraps the function in a promise
async function loadPage() {
    try {
        //throw 'error1'; <-- this is making a manually created error that skips straight to the catch code

        await loadProductsFetch(); //"await" lets us wait for this function to end before continuing

        await new Promise((resolve, reject) => {
            //throw 'error2'; <-- another manually created error
            loadCart(() => {
                //reject('error3'); <-- manually created error that occurs in the future
                resolve();
            });
        });

    } catch (error) {
        console.log('Unexpected error. Please try again later.');
    }
    
    renderOrderSummary();
    renderPaymentSummary();
}
loadPage();

/*
Promise.all([
    loadProductsFetch(),
    new Promise((resolve) => {
        loadCart(() => {
            resolve();
        });
    })
]).then(() => {
    renderOrderSummary();
    renderPaymentSummary();
});
*/

/*
new Promise((resolve) => {
    loadProducts(() => {
        resolve('value1'); //We are sending this value to "then" as a parameter
    });

}).then((value) => {
    return new Promise((resolve) => {
        loadCart(() => {
            resolve();
        });
    });

}).then(() => {
    renderOrderSummary();
    renderPaymentSummary();
});
*/

/* This is the callback version of the promise above:
loadProducts(() => {
    renderOrderSummary();
    renderPaymentSummary();
});
*/