import { writable, get } from 'svelte/store';
import { currentDisplay } from './display';

export let pics = writable<Array<Array<Array<boolean>>>>([]);

export async function fetchSaves() {
    try {
        const response = await fetch("/api/saves");
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        
        const saves: Array<Array<Array<boolean>>> = await response.json();
        pics.set(saves);
    } catch(error) {
        console.log(error);
    }
}

export function load(id: number){
    currentDisplay.set(get(pics)[id]);
}

export async function save(){
    pics.update(old => [...old, get(currentDisplay)]);
}

export async function pushSaves() {
    try {
        const response = await fetch("/api/saves",{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(get(pics))
        });

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

    } catch(error) {
        console.log(error);
    }
}