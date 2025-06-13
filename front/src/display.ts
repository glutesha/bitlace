import { writable, get } from 'svelte/store';

export const SIZE = 8;

export const currentDisplay = writable(Array.from({ length: SIZE }, () => Array.from({ length: SIZE }, () => false)));

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

export async function updateDisplay() {
    try {
        const response = await fetch('/api/display', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(get(currentDisplay))
        });
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
    } catch (error) {
        console.error('Error updating display:', error);
    }
}