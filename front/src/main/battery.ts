import { writable } from 'svelte/store';

export const battery = writable(100);

export async function get_battery() {
    try {
        const response = await fetch('/api/battery')
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const data = await response.text();
        if(Number.isNaN(parseInt(data))){
            battery.set(100);
        }
        else{
            battery.set(parseInt(data));
        }
        
    } catch (error) {
        console.error('Error fetching battery:', error);
    }   
}