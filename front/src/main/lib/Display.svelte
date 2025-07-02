<script lang="ts">
    import Pixel from './Pixel.svelte'
    import { currentDisplay, fetchDisplay, updateDisplay } from '../display'
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';
    import { tool } from '../tool';
    
    function togglePixel(buttons: number, x: number, y: number) {
        if(buttons == 2){
            $currentDisplay[x][y] = false;
        }
        else{
            $currentDisplay[x][y] = $tool == 1;
        }
        $currentDisplay = [...$currentDisplay.map(row => [...row])];
        updateDisplay();
    }

    onMount(async () => {
        await fetchDisplay();  
        await fetchTheme();  
    });
</script>

<div role="banner" oncontextmenu={e => e.preventDefault()} class="flex touch-none select-none flex-col items-center bg-black gap-3 p-1 rounded-xl shadow-2xl shadow-black">
{#each $currentDisplay as row, rowIndex}
    <div class="flex flex-row gap-3" >
        {#each row as pixel, pixelIndex}
            <Pixel
                lit={pixel} 
                onClick={(buttons) => togglePixel(buttons, rowIndex, pixelIndex)} 
            />
        {/each}
    </div>
{/each}
</div>