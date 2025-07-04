import { writable } from 'svelte/store';

let themes = [
    {name: "red", color: 'bg-red-500', shadow: 'shadow-red-500/70'},
    {name: "green", color: 'bg-green-500', shadow: 'shadow-green-500/70'},
    {name: "blue", color: 'bg-blue-500', shadow: 'shadow-blue-500/70'},
    {name: "purple", color: 'bg-purple-500', shadow: 'shadow-purple-500/70'},
    {name: "orange", color: 'bg-orange-500', shadow: 'shadow-orange-600/70'},
    {name: "white", color: 'bg-white', shadow: 'shadow-white/70'},
];

export let currentTheme = writable(themes[0]);

export async function fetchTheme() {
    try {
        const response = await fetch('/api/display_color')
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const data = await response.text();
        
        const newTheme = themes.find(theme => theme.name === data);

        if (newTheme) {
            currentTheme.set(newTheme); 
        } 
    } catch (error) {
        console.error('Error fetching theme:', error);
    }
}
