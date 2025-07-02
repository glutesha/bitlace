import { writable } from 'svelte/store';

export let pics = writable<{ [id: number]: Array<Array<boolean>> }>({});

export async function fetchSaves() {
    try {
        const response = await fetch("/api/saves");
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const saves: { [id: number]: Array<Array<boolean>> } = await response.json();
        pics.set(saves);
    } catch(error) {
        console.log(error);
    }
    
}