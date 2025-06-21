import { writable, get } from "svelte/store";

export let tool = writable(1);
export let tools = 2;

export function changeTool(){
    tool.set((get(tool) + 1) % tools)
}