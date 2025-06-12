<script lang="ts">
    import Pixel from './Pixel.svelte'
    import {currentDisplay, fetchDisplay} from '../display'
    import { onMount } from 'svelte';

    function togglePixel(x: number, y: number) {
        display[x][y] = !display[x][y];
        display = [...display.map(row => [...row])];
        updateDisplay();
    }

    onMount(async () => {
        await fetchDisplay();  
        display = $currentDisplay;
    });

    let display = $currentDisplay;

    async function updateDisplay() {
        try {
            const response = await fetch('/api/display', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(display)
            });
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
        } catch (error) {
            console.error('Error updating display:', error);
        }
    }
</script>

<div class="flex flex-col items-center bg-black gap-3 p-2 rounded-xl">
{#each display as row, rowIndex}
    <div class="flex flex-row gap-3">
        {#each row as pixel, pixelIndex}
            <Pixel lit={pixel} onClick={() => togglePixel(rowIndex, pixelIndex)}/>
        {/each}
    </div>
{/each}
</div>