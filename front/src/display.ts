import { writable } from 'svelte/store';

const SIZE = 8;

export let currentDisplay = writable(Array.from({ length: SIZE }, () => Array.from({ length: SIZE }, () => false)));

export async function fetchDisplay() {
    try {
        const response = await fetch('/api/display');
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const data = await response.json();
        currentDisplay.set(data);

    } catch (error) {
        console.error('Error getting display state:', error);
    }
}