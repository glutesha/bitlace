import { writable, get } from "svelte/store";

export let deletetool = writable(false);

export function toggleDelete(){
    deletetool.set(!get(deletetool));
}