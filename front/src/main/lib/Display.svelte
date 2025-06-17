<script lang="ts">
    import Pixel from './Pixel.svelte'
    import { currentDisplay, fetchDisplay, updateDisplay } from '../display'
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';

    function togglePixel(x: number, y: number) {
        $currentDisplay[x][y] = !$currentDisplay[x][y];
        $currentDisplay = [...$currentDisplay.map(row => [...row])];
        updateDisplay();
    }

    onMount(async () => {
        await fetchDisplay();  
        await fetchTheme();  
    });
</script>

<div class="flex flex-col items-center bg-black gap-3 p-1 rounded-xl shadow-2xl shadow-black">
{#each $currentDisplay as row, rowIndex}
    <div class="flex flex-row gap-3">
        {#each row as pixel, pixelIndex}
            <Pixel lit={pixel} onClick={() => togglePixel(rowIndex, pixelIndex)}/>
        {/each}
    </div>
{/each}
</div>